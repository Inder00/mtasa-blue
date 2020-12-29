/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/CLuaManager.cpp
 *  PURPOSE:     Lua virtual machine manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

extern CGame* g_pGame;

CLuaManager::CLuaManager(CObjectManager* pObjectManager, CPlayerManager* pPlayerManager, CVehicleManager* pVehicleManager, CBlipManager* pBlipManager,
                         CRadarAreaManager* pRadarAreaManager, CRegisteredCommands* pRegisteredCommands, CMapManager* pMapManager, CEvents* pEvents)
{
    m_pObjectManager = pObjectManager;
    m_pPlayerManager = pPlayerManager;
    m_pVehicleManager = pVehicleManager;
    m_pBlipManager = pBlipManager;
    m_pRadarAreaManager = pRadarAreaManager;
    m_pRegisteredCommands = pRegisteredCommands;
    m_pMapManager = pMapManager;
    m_pEvents = pEvents;

    // Create our lua dynamic module manager
    m_pLuaModuleManager = new CLuaModuleManager(this);
    m_pLuaModuleManager->SetScriptDebugging(g_pGame->GetScriptDebugging());

    // Load our C Functions into Lua and hook callback
    LoadCFunctions();
    lua_registerPreCallHook(CLuaDefs::CanUseFunction);
    lua_registerUndumpHook(CLuaMain::OnUndump);

#ifdef MTA_DEBUG
    // Check rounding in case json is updated
    json_object* obj = json_object_new_double(5.1);
    SString      strResult = json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PLAIN);
    assert(strResult == "5.1");
    json_object_put(obj);
#endif
}

CLuaManager::~CLuaManager()
{
    CLuaCFunctions::RemoveAllFunctions();
    list<CLuaMain*>::iterator iter;
    for (iter = m_virtualMachines.begin(); iter != m_virtualMachines.end(); ++iter)
    {
        delete (*iter);
    }

    // Destroy the module manager
    delete m_pLuaModuleManager;
}

CLuaMain* CLuaManager::CreateVirtualMachine(CResource* pResourceOwner, bool bEnableOOP)
{
    // Create it and add it to the list over VM's
    CLuaMain* pLuaMain = new CLuaMain(this, m_pObjectManager, m_pPlayerManager, m_pVehicleManager, m_pBlipManager, m_pRadarAreaManager, m_pMapManager,
                                      pResourceOwner, bEnableOOP, pResourceOwner->IsMultithreadingEnabledInMetaXml());
    m_virtualMachines.push_back(pLuaMain);
    pLuaMain->InitVM();

    m_pLuaModuleManager->RegisterFunctions(pLuaMain->GetVirtualMachine());

    return pLuaMain;
}

bool CLuaManager::RemoveVirtualMachine(CLuaMain* pLuaMain)
{
    if (pLuaMain)
    {
        // Remove all events registered by it and all commands added
        m_pEvents->RemoveAllEvents(pLuaMain);
        m_pRegisteredCommands->CleanUpForVM(pLuaMain);

        // Delete it unless it is already
        if (!pLuaMain->BeingDeleted())
        {
            delete pLuaMain;
        }

        // Remove it from our list
        m_virtualMachines.remove(pLuaMain);
        return true;
    }

    return false;
}

void CLuaManager::OnLuaMainOpenVM(CLuaMain* pLuaMain, lua_State* luaVM)
{
    MapSet(m_VirtualMachineMap, pLuaMain->GetVirtualMachine(), pLuaMain);
}

void CLuaManager::OnLuaMainCloseVM(CLuaMain* pLuaMain, lua_State* luaVM)
{
    MapRemove(m_VirtualMachineMap, pLuaMain->GetVirtualMachine());
}

void CLuaManager::DoPulse()
{
    list<CLuaMain*>::iterator iter;
    for (iter = m_virtualMachines.begin(); iter != m_virtualMachines.end(); ++iter)
    {
        (*iter)->DoPulse();
    }
    m_pLuaModuleManager->DoPulse();
}

CLuaMain* CLuaManager::GetVirtualMachine(lua_State* luaVM)
{
    if (!luaVM)
        return NULL;

    // Grab the main virtual state because the one we've got passed might be a coroutine state
    // and only the main state is in our list.
    lua_State* main = lua_getmainstate(luaVM);
    if (main)
    {
        luaVM = main;
    }

    // Find a matching VM in our map
    CLuaMain* pLuaMain = MapFindRef(m_VirtualMachineMap, luaVM);
    if (pLuaMain)
        return pLuaMain;

    // Find a matching VM in our list
    list<CLuaMain*>::const_iterator iter = m_virtualMachines.begin();
    for (; iter != m_virtualMachines.end(); ++iter)
    {
        if (luaVM == (*iter)->GetVirtualMachine())
        {
            dassert(0);            // Why not in map?
            return *iter;
        }
    }

    // Doesn't exist
    return NULL;
}

// Return resource associated with a lua state
CResource* CLuaManager::GetVirtualMachineResource(lua_State* luaVM)
{
    CLuaMain* pLuaMain = GetVirtualMachine(luaVM);
    if (pLuaMain)
        return pLuaMain->GetResource();
    return NULL;
}

void CLuaManager::LoadCFunctions()
{
    constexpr static const std::tuple<const char*, lua_CFunction, bool> functions[]
    {
        {"addEvent", CLuaFunctionDefs::AddEvent, false},
        {"addEventHandler", CLuaFunctionDefs::AddEventHandler, false},
        {"removeEventHandler", CLuaFunctionDefs::RemoveEventHandler, false},
        {"getEventHandlers", CLuaFunctionDefs::GetEventHandlers, false},
        {"triggerEvent", CLuaFunctionDefs::TriggerEvent, true},
        {"triggerClientEvent", CLuaFunctionDefs::TriggerClientEvent, true},
        {"cancelEvent", CLuaFunctionDefs::CancelEvent, false},
        {"wasEventCancelled", CLuaFunctionDefs::WasEventCancelled, false},
        {"getCancelReason", CLuaFunctionDefs::GetCancelReason, false},
        {"triggerLatentClientEvent", CLuaFunctionDefs::TriggerLatentClientEvent, false},
        {"getLatentEventHandles", CLuaFunctionDefs::GetLatentEventHandles, false},
        {"getLatentEventStatus", CLuaFunctionDefs::GetLatentEventStatus, false},
        {"cancelLatentEvent", CLuaFunctionDefs::CancelLatentEvent, false},
        {"addDebugHook", CLuaFunctionDefs::AddDebugHook, false},
        {"removeDebugHook", CLuaFunctionDefs::RemoveDebugHook, false},

        // Explosion create funcs
        {"createExplosion", CLuaFunctionDefs::CreateExplosion, false},

        // Fire create funcs
        // CLuaCFunctions::AddFunction ( "createFire", CLuaFunctionDefinitions::CreateFire );

        // Path(node) funcs
        // CLuaCFunctions::AddFunction ( "createNode", CLuaFunctionDefinitions::CreateNode );

        // Ped body funcs?
        {"getBodyPartName", CLuaFunctionDefs::GetBodyPartName, true},
        {"getClothesByTypeIndex", CLuaFunctionDefs::GetClothesByTypeIndex, true},
        {"getTypeIndexFromClothes", CLuaFunctionDefs::GetTypeIndexFromClothes, true},
        {"getClothesTypeName", CLuaFunctionDefs::GetClothesTypeName, true},

        // Weapon funcs
        {"getWeaponNameFromID", CLuaFunctionDefs::GetWeaponNameFromID, true},
        {"getWeaponIDFromName", CLuaFunctionDefs::GetWeaponIDFromName, true},
        {"getWeaponProperty", CLuaFunctionDefs::GetWeaponProperty, false},
        {"getOriginalWeaponProperty", CLuaFunctionDefs::GetOriginalWeaponProperty, true},
        {"setWeaponProperty", CLuaFunctionDefs::SetWeaponProperty, false},
        {"setWeaponAmmo", CLuaFunctionDefs::SetWeaponAmmo, false},
        {"getSlotFromWeapon", CLuaFunctionDefs::GetSlotFromWeapon, false},

        #if MTASA_VERSION_TYPE < VERSION_TYPE_RELEASE
        {"createWeapon", CLuaFunctionDefs::CreateWeapon, false},
        {"fireWeapon", CLuaFunctionDefs::FireWeapon, false},
        {"setWeaponState", CLuaFunctionDefs::SetWeaponState, false},
        {"getWeaponState", CLuaFunctionDefs::GetWeaponState, false},
        {"setWeaponTarget", CLuaFunctionDefs::SetWeaponTarget, false},
        {"getWeaponTarget", CLuaFunctionDefs::GetWeaponTarget, false},
        {"setWeaponOwner", CLuaFunctionDefs::SetWeaponOwner, false},
        {"getWeaponOwner", CLuaFunctionDefs::GetWeaponOwner, false},
        {"setWeaponFlags", CLuaFunctionDefs::SetWeaponFlags, false},
        {"getWeaponFlags", CLuaFunctionDefs::GetWeaponFlags, false},
        {"setWeaponFiringRate", CLuaFunctionDefs::SetWeaponFiringRate, false},
        {"getWeaponFiringRate", CLuaFunctionDefs::GetWeaponFiringRate, false},
        {"resetWeaponFiringRate", CLuaFunctionDefs::ResetWeaponFiringRate, false},
        {"getWeaponAmmo", CLuaFunctionDefs::GetWeaponAmmo, false},
        {"getWeaponClipAmmo", CLuaFunctionDefs::GetWeaponClipAmmo, false},
        {"setWeaponClipAmmo", CLuaFunctionDefs::SetWeaponClipAmmo, false},
        #endif

        // Console funcs
        {"addCommandHandler", CLuaFunctionDefs::AddCommandHandler, false},
        {"removeCommandHandler", CLuaFunctionDefs::RemoveCommandHandler, false},
        {"executeCommandHandler", CLuaFunctionDefs::ExecuteCommandHandler, false},
        {"getCommandHandlers", CLuaFunctionDefs::GetCommandHandlers, false},

        // Server standard funcs
        {"getMaxPlayers", CLuaFunctionDefs::GetMaxPlayers, true},
        {"setMaxPlayers", CLuaFunctionDefs::SetMaxPlayers, false},
        {"outputChatBox", CLuaFunctionDefs::OutputChatBox, true},
        {"outputConsole", CLuaFunctionDefs::OutputConsole, true},
        {"outputDebugString", CLuaFunctionDefs::OutputDebugString, true},
        {"outputServerLog", CLuaFunctionDefs::OutputServerLog, true},
        {"getServerName", CLuaFunctionDefs::GetServerName, false},
        {"getServerHttpPort", CLuaFunctionDefs::GetServerHttpPort, true},
        {"getServerPassword", CLuaFunctionDefs::GetServerPassword, true},
        {"setServerPassword", CLuaFunctionDefs::SetServerPassword, false},
        {"getServerConfigSetting", CLuaFunctionDefs::GetServerConfigSetting, false},
        {"clearChatBox", CLuaFunctionDefs::ClearChatBox, true},

        // Loaded map funcs
        {"getRootElement", CLuaFunctionDefs::GetRootElement, true},
        {"loadMapData", CLuaFunctionDefs::LoadMapData, false},
        {"saveMapData", CLuaFunctionDefs::SaveMapData, false},

        // All-Seeing Eye Functions
        {"getGameType", CLuaFunctionDefs::GetGameType, false},
        {"getMapName", CLuaFunctionDefs::GetMapName, false},
        {"setGameType", CLuaFunctionDefs::SetGameType, false},
        {"setMapName", CLuaFunctionDefs::SetMapName, false},
        {"getRuleValue", CLuaFunctionDefs::GetRuleValue, false},
        {"setRuleValue", CLuaFunctionDefs::SetRuleValue, false},
        {"removeRuleValue", CLuaFunctionDefs::RemoveRuleValue, false},

        // Registry functions
        {"getPerformanceStats", CLuaFunctionDefs::GetPerformanceStats, false},

        // Admin functions
        /*
        CLuaCFunctions::AddFunction ( "aexec", CLuaFunctionDefinitions::Aexec },
        CLuaCFunctions::AddFunction ( "kickPlayer", CLuaFunctionDefinitions::KickPlayer },
        CLuaCFunctions::AddFunction ( "banPlayer", CLuaFunctionDefinitions::BanPlayer },
        CLuaCFunctions::AddFunction ( "banPlayerIP", CLuaFunctionDefinitions::BanPlayerIP },
        CLuaCFunctions::AddFunction ( "setPlayerMuted", CLuaFunctionDefinitions::SetPlayerMuted },

        CLuaCFunctions::AddFunction ( "addAccount", CLuaFunctionDefinitions::AddAccount },
        CLuaCFunctions::AddFunction ( "delAccount", CLuaFunctionDefinitions::DelAccount },
        CLuaCFunctions::AddFunction ( "setAccountPassword", CLuaFunctionDefinitions::SetAccountPassword },
        */

        // Misc funcs
        {"resetMapInfo", CLuaFunctionDefs::ResetMapInfo, false},
        {"getServerPort", CLuaFunctionDefs::GetServerPort, false},

        // Settings registry funcs
        {"get", CLuaFunctionDefs::Get, false},
        {"set", CLuaFunctionDefs::Set, false},

        // Utility
        {"getVersion", CLuaFunctionDefs::GetVersion, false},
        {"getNetworkUsageData", CLuaFunctionDefs::GetNetworkUsageData, false},
        {"getNetworkStats", CLuaFunctionDefs::GetNetworkStats, false},
        {"getLoadedModules", CLuaFunctionDefs::GetModules, false},
        {"getModuleInfo", CLuaFunctionDefs::GetModuleInfo, false},

        {"setDevelopmentMode", CLuaFunctionDefs::SetDevelopmentMode, false},
        {"getDevelopmentMode", CLuaFunctionDefs::GetDevelopmentMode, false},
    };

    // Add all functions
    for (const auto& [name, func, threadSafe] : functions)
        CLuaCFunctions::AddFunction(name, func, threadSafe);
    
    // Restricted functions
    CLuaCFunctions::AddFunction("setServerConfigSetting", CLuaFunctionDefs::SetServerConfigSetting, true);
    CLuaCFunctions::AddFunction("shutdown", CLuaFunctionDefs::shutdown, true);

    // Load the functions from our classes
    CLuaACLDefs::LoadFunctions();
    CLuaAccountDefs::LoadFunctions();
    CLuaBanDefs::LoadFunctions();
    CLuaBlipDefs::LoadFunctions();
    CLuaCameraDefs::LoadFunctions();
    CLuaColShapeDefs::LoadFunctions();
    CLuaDatabaseDefs::LoadFunctions();
    CLuaElementDefs::LoadFunctions();
    CLuaHandlingDefs::LoadFunctions();
    CLuaMarkerDefs::LoadFunctions();
    CLuaNetworkDefs::LoadFunctions();
    CLuaObjectDefs::LoadFunctions();
    CLuaPedDefs::LoadFunctions();
    CLuaPickupDefs::LoadFunctions();
    CLuaPlayerDefs::LoadFunctions();
    CLuaRadarAreaDefs::LoadFunctions();
    CLuaResourceDefs::LoadFunctions();
    CLuaShared::LoadFunctions();
    CLuaTeamDefs::LoadFunctions();
    CLuaTextDefs::LoadFunctions();
    CLuaTimerDefs::LoadFunctions();
    CLuaVehicleDefs::LoadFunctions();
    CLuaVoiceDefs::LoadFunctions();
    CLuaWaterDefs::LoadFunctions();
    CLuaWorldDefs::LoadFunctions();
    CLuaXMLDefs::LoadFunctions();
    // Backward compatibility functions at the end, so the new function name is used in ACL
    CLuaCompatibilityDefs::LoadFunctions();
}
