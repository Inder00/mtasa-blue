/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientRenderer.cpp
 *  PURPOSE:     Renderer entity class
 *
 *****************************************************************************/

#include "StdInc.h"

CClientRenderer::CClientRenderer(CClientManager* pManager, ElementID ID) : ClassInit(this), CClientEntity(ID)
{
    // Init
    m_pManager = pManager;
    m_pRendererManager = pManager->GetRendererManager();

    SetTypeName("renderer");

    // Add us to Renderer manager's list
    m_pRendererManager->AddToList(this);
}

CClientRenderer::~CClientRenderer(void)
{
    // Remove us from Renderer manager's list
    m_pRendererManager->RemoveFromList(this);

}

void CClientRenderer::DoPulse()
{

}
