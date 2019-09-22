/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/logic/lua/CLuaPhysicsRigidBodyManager.cpp
 *  PURPOSE:     Lua physics rigid body manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include <StdInc.h>

void CLuaPhysicsRigidBodyManager::DoPulse(CLuaMain* pLuaMain)
{
    assert(m_ProcessQueue.empty());
    assert(!m_pPendingDelete);
    assert(!m_pProcessingTimer);

    CTickCount llCurrentTime = CTickCount::Now();

    // Use a separate queue to avoid trouble
    for (CFastList<CLuaPhysicsRigidBody*>::const_iterator iter = m_RigidBodyList.begin(); iter != m_RigidBodyList.end(); iter++)
    {
    }
}

void CLuaPhysicsRigidBodyManager::RemoveRigidBody(CLuaPhysicsRigidBody* pRigidBody)
{
    assert(pRigidBody);

    // Check if already removed
    if (!ListContains(m_RigidBodyList, pRigidBody))
        return;

    // Remove all references
    ListRemove(m_RigidBodyList, pRigidBody);

    delete pRigidBody;
}

void CLuaPhysicsRigidBodyManager::RemoveAllRigidBodies()
{
    // Delete all the timers
    CFastList<CLuaPhysicsRigidBody*>::const_iterator iter = m_RigidBodyList.begin();
    for (; iter != m_RigidBodyList.end(); iter++)
    {
        delete *iter;
    }

    // Clear the timer list
    m_RigidBodyList.clear();
    m_ProcessQueue.clear();
    m_pPendingDelete = NULL;
    m_pProcessingTimer = NULL;
}

CLuaPhysicsRigidBody* CLuaPhysicsRigidBodyManager::GetRigidBodyFromScriptID(uint uiScriptID)
{
    CLuaPhysicsRigidBody* pLuaTimer = (CLuaPhysicsRigidBody*)CIdArray::FindEntry(uiScriptID, EIdClass::TIMER);
    if (!pLuaTimer)
        return NULL;

    if (!ListContains(m_RigidBodyList, pLuaTimer))
        return NULL;
    return pLuaTimer;
}

CLuaPhysicsRigidBody* CLuaPhysicsRigidBodyManager::CreateRigidBody(CClientPhysics* pPhysics)
{
    // Add the rigid body
    CLuaPhysicsRigidBody* pLuaRigidBody = new CLuaPhysicsRigidBody(pPhysics);
    return pLuaRigidBody;
}
