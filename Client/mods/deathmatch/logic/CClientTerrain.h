/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientTerrain.h
 *  PURPOSE:     Terrain
 *
 *****************************************************************************/

#ifndef __CCLIENTTERRAIN_H
#define __CCLIENTTERRAIN_H

#include "CClientEntity.h"
#include "CVector.h"

class CClientTerrain;

class CClientTerrain : public CClientEntity
{
    DECLARE_CLASS(CClientTerrain, CClientEntity)

public:

    CClientTerrain(class CClientTerrainManager* pManager, ElementID ID);
    ~CClientTerrain(void);

    eClientEntityType GetType(void) const { return CCLIENTTERRAIN; }

    void Unlink(void);

    void GetPosition(CVector& vecPosition) const { vecPosition = m_vecPosition; }
    void SetPosition(const CVector& vecPosition) { m_vecPosition = vecPosition; }

protected:

private:

    class CClientTerrainManager*  m_pTerrainManager;
    CVector     m_vecPosition;
    CVector2D   m_vecSize;
    ushort      m_sMeshDensity;
};

#endif
