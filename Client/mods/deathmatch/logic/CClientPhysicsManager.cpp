/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientPhysicsManager.cpp
 *  PURPOSE:     Physics manager class
 *
 *****************************************************************************/

#include "StdInc.h"

CClientPhysicsManager::CClientPhysicsManager(class CClientManager* pManager) : m_pManager(pManager), m_bCanRemoveFromList(true)
{
}

CClientPhysicsManager::~CClientPhysicsManager()
{
    DeleteAll();
}

void CClientPhysicsManager::DeleteAll()
{
    m_bCanRemoveFromList = false;
    for (std::list<CClientPhysics*>::iterator i = m_PhysicsWorlds.begin(); i != m_PhysicsWorlds.end(); ++i)
    {
        delete *i;
    }
    m_PhysicsWorlds.clear();
    m_bCanRemoveFromList = true;
}

void CClientPhysicsManager::DoPulse()
{
    for (std::list<CClientPhysics*>::iterator i = m_PhysicsWorlds.begin(); i != m_PhysicsWorlds.end(); ++i)
    {
        (*i)->Update();
    }
}

void CClientPhysicsManager::RemoveFromList(CClientPhysics* pEffect)
{
    if (m_bCanRemoveFromList)
    {
        m_PhysicsWorlds.remove(pEffect);
    }
}

CClientPhysics* CClientPhysicsManager::Get(ElementID ID)
{
    // Grab the element with the given id. Check its type.
    CClientEntity* pEntity = CElementIDs::GetElement(ID);
    if (pEntity && pEntity->GetType() == CCLIENTPHYSICS)
    {
        return static_cast<CClientPhysics*>(pEntity);
    }

    return NULL;
}
