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

CClientTerrain::CClientTerrain(CClientManager* pManager, ElementID ID) : CClientEntity(ID)
{
    // Init
    m_pManager = pManager;

    SetTypeName("terrain");

    // Add it to our manager's list
    //m_pManager->AddToList(this);
}

CClientTerrain::~CClientTerrain(void)
{
    Unlink();
}

void CClientTerrain::Unlink(void)
{
    //m_pManager->RemoveFromList(this);
}
