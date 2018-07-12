/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientTerrainManager.cpp
 *  PURPOSE:     Terrain entity manager class
 *
 *****************************************************************************/

#include "StdInc.h"

using std::list;
using std::vector;

CClientTerrainManager::~CClientTerrainManager(void)
{
    DeleteAll();
}

bool CClientTerrainManager::Exists(CClientTerrain* pTerrain)
{
    // Return true if it exists
    return ListContains(m_List, pTerrain);
}

void CClientTerrainManager::DeleteAll(void)
{
    // Delete all of them
    vector<CClientTerrain*>                 cloneList = m_List;
    vector<CClientTerrain*>::const_iterator iter = cloneList.begin();
    for (; iter != cloneList.end(); ++iter)
    {
        delete *iter;
    }
    m_List.clear();
}

void CClientTerrainManager::RemoveFromList(CClientTerrain* pTerrain)
{
    ListRemove(m_List, pTerrain);
}
