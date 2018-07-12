/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientColManager.h
 *  PURPOSE:     Collision entity manager class
 *
 *****************************************************************************/

#ifndef __CCLIENTTERRAINMANAGER_H
#define __CCLIENTTERRAINMANAGER_H

#include "CClientCommon.h"
#include <list>

class CClientEntity;
class CClientTerrain;

class CClientTerrainManager
{
    friend class CClientManager;
public:

    ~CClientTerrainManager(void);
    bool Exists(CClientTerrain* pTerrain);
    void DeleteAll(void);

    void AddToList(CClientTerrain* pTerrain) { m_List.push_back(pTerrain); }
    void RemoveFromList(CClientTerrain* pTerrain);
private:

    std::vector<CClientTerrain*> m_List;
};

#endif
