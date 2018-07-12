/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientColShape.cpp
 *  PURPOSE:     Shaped collision entity base class
 *
 *****************************************************************************/

#include "StdInc.h"

using std::list;

CClientTerrain::CClientTerrain(CClientTerrainManager* pManager, ElementID ID) : ClassInit(this), CClientEntity(ID)
{
    // Init
    m_pTerrainManager = pManager;

    SetTypeName("terrain");

    // Add it to our manager's list
    m_pTerrainManager->AddToList(this);
}

CClientTerrain::~CClientTerrain(void)
{
    Unlink();
}

void CClientTerrain::Unlink(void)
{
    m_pTerrainManager->RemoveFromList(this);
}
