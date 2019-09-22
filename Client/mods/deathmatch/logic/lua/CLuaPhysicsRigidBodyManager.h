/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/logic/lua/CLuaTimerManager.h
 *  PURPOSE:     Lua timer manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CLuaPhysicsRigidBodyManager;

#pragma once

#include "LuaCommon.h"
#include "CLuaPhysicsRigidBody.h"
#include <list>

class CLuaPhysicsRigidBodyManager
{
public:
    CLuaPhysicsRigidBodyManager()
    {
        m_pPendingDelete = NULL;
        m_pProcessingTimer = NULL;
    }
    ~CLuaPhysicsRigidBodyManager() { RemoveAllRigidBodies(); };

    void DoPulse(CLuaMain* pLuaMain);


    CLuaPhysicsRigidBody* GetRigidBodyFromScriptID(uint uiScriptID);

    CLuaPhysicsRigidBody*    CreateRigidBody(CClientPhysics* pPhysics);
    void                     RemoveRigidBody(CLuaPhysicsRigidBody* pRigidBody);
    void                     RemoveAllRigidBodies();
    unsigned long            GetRigidBodyCount() const { return m_RigidBodyList.size(); }

    CFastList<CLuaPhysicsRigidBody*>::const_iterator IterBegin() { return m_RigidBodyList.begin(); }
    CFastList<CLuaPhysicsRigidBody*>::const_iterator IterEnd() { return m_RigidBodyList.end(); }

private:
    CFastList<CLuaPhysicsRigidBody*>  m_RigidBodyList;
    std::deque<CLuaPhysicsRigidBody*> m_ProcessQueue;
    CLuaPhysicsRigidBody*             m_pPendingDelete;
    CLuaPhysicsRigidBody*             m_pProcessingTimer;
};
