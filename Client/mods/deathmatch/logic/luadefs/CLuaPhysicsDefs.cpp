/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/luadefs/CLuaPhysicsDefs.cpp
 *  PURPOSE:     Lua definitions class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

void CLuaPhysicsDefs::LoadFunctions()
{
    std::map<const char*, lua_CFunction> functions{
        {"physicsCreate", PhysicsCreate},
    };

    // Add functions
    for (const auto& pair : functions)
    {
        CLuaCFunctions::AddFunction(pair.first, pair.second);
    }
}

int CLuaPhysicsDefs::PhysicsCreate(lua_State* luaVM)
{
    CScriptArgReader argStream(luaVM);

    if (!argStream.HasErrors())
    {

        // Grab the lua main and the resource belonging to this script
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            // Get the resource we belong to
            CResource* pResource = pLuaMain->GetResource();
            if (pResource)
            {
                CClientEntity*  pRoot = pResource->GetResourceCOLModelRoot();
                CClientPhysics* pPhysics = new CClientPhysics(m_pManager, INVALID_ELEMENT_ID);
                pPhysics->SetParent(pRoot);

                lua_pushelement(luaVM, pPhysics);
                return 1;
            }
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // We failed for some reason
    lua_pushboolean(luaVM, false);
    return 1;
}
