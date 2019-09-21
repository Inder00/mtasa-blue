/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientPhysicsManager.h
 *  PURPOSE:     Effect manager
 *
 *****************************************************************************/

#pragma once

#include "CClientPhysics.h"

class CClientPhysicsManager
{
    friend class CClientManager;

public:
    void           DeleteAll();

    unsigned int           Count() { return m_PhysicsWorlds.size(); };
    static CClientPhysics* Get(ElementID ID);
    void                   AddToList(CClientPhysics* pEffect) { m_PhysicsWorlds.push_back(pEffect); }
    void                   RemoveFromList(CClientPhysics* pEffect);
    void                   DoPulse();

private:
    CClientPhysicsManager(class CClientManager* pManager);
    ~CClientPhysicsManager();

    class CClientManager*     m_pManager;
    bool                      m_bCanRemoveFromList;
    std::list<CClientPhysics*> m_PhysicsWorlds;
};
