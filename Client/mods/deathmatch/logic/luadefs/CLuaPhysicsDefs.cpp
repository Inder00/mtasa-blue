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
        {"physicsCreateWorld", PhysicsCreateWorld},
        {"physicsCreateRigidBody", PhysicsCreateRigidBody},
        {"physicsAddCollisionShape", PhysicsAddCollisionShape},
    };

    // Add functions
    for (const auto& pair : functions)
    {
        CLuaCFunctions::AddFunction(pair.first, pair.second);
    }
}

int CLuaPhysicsDefs::PhysicsCreateWorld(lua_State* luaVM)
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
                pPhysics->SetLuaMain(pLuaMain);

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

int CLuaPhysicsDefs::PhysicsCreateRigidBody(lua_State* luaVM)
{
    CClientPhysics* pPhysics;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pPhysics);

    if (!argStream.HasErrors())
    {
        CLuaPhysicsRigidBody* pRigidBody = pPhysics->CreateRigidBody();

        lua_pushphysicsrigidbody(luaVM, pRigidBody);
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // We failed for some reason
    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaPhysicsDefs::PhysicsAddCollisionShape(lua_State* luaVM)
{
    CLuaPhysicsRigidBody* pRigidBody;
    ePhysicsShapeType     physiscShapeType;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pRigidBody);
    argStream.ReadEnumString(physiscShapeType);

    if (!argStream.HasErrors())
    {
        CVector vector1, vector2;
        float   fMass; // in kilograms
        float   fRadius;
        switch (physiscShapeType)
        {
            case PHYSICAL_SHAPE_BOX:
                argStream.ReadVector3D(vector1);
                argStream.ReadNumber(fMass, 10);
                if (!argStream.HasErrors())
                {
                    pRigidBody->CreateBox(vector1, fMass);
                    lua_pushboolean(luaVM, true);
                    return 1;
                }
                else
                {
                
                }
                break;
            case PHYSICAL_SHAPE_SPHERE:
                argStream.ReadNumber(fRadius);
                argStream.ReadNumber(fMass, 10);
                if (!argStream.HasErrors())
                {
                    pRigidBody->CreateSphere(fRadius, fMass);
                    lua_pushboolean(luaVM, true);
                    return 1;
                }
                else
                {
                
                }
                break;
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // We failed for some reason
    lua_pushboolean(luaVM, false);
    return 1;
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
    lua_pushboolean(luaVM, false);
    return 1;
}
