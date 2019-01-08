/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientRendererManager.cpp
 *  PURPOSE:     PointLights entity manager class
 *
 *****************************************************************************/

#include "StdInc.h"

using std::list;

CClientRendererManager::CClientRendererManager(CClientManager* pManager)
{
    // Init
    m_pManager = pManager;
}

CClientRendererManager::~CClientRendererManager(void)
{
    // Make sure all the lights are deleted
    DeleteAll();
}

void CClientRendererManager::DeleteAll(void)
{
    list<CClientRenderer*>::const_iterator iter = IterBegin();
    for (; iter != IterEnd(); iter++)
    {
        delete *iter;
    }

    // Clear the list
    m_List.clear();
}

void CClientRendererManager::RemoveFromList(CClientRenderer* pLight)
{
    if (!m_List.empty())
        m_List.remove(pLight);
}

void CClientRendererManager::DoPulse(void)
{
    list<CClientRenderer*>::const_iterator iter = IterBegin();
    for (; iter != IterEnd(); iter++)
    {
        (*iter)->DoPulse();
    }
}
