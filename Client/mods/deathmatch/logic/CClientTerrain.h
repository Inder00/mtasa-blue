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

public:

    struct TerrainVertex {
        float position[3];
        char texture[24];
        char textureMask[24];
        char lightPower;
        char lightColor[3];
        float u, v;
    };

    struct TerrainPolygon {
        TerrainVertex vertex[3];
    };

    struct TerrainSelect {
        TerrainVertex vertex;
        float power;
    };

    CClientTerrain(class CClientManager* pManager, ElementID ID);
    ~CClientTerrain(void);

    eClientEntityType GetType(void) const { return CCLIENTTERRAIN; }

    void Unlink(void);

    void GetPosition(CVector& vecPosition) const { vecPosition = m_vecPosition; }
    void SetPosition(const CVector& vecPosition) { m_vecPosition = vecPosition; }

    void GetSize(CVector2D& vecSize) const { vecSize = m_vecSize; }
    void SetSize(const CVector2D& vecSize) { m_vecSize = vecSize; }

    void SetDensity(ushort& sDensity) const { sDensity = m_sMeshDensity; }
    void GetDensity(const ushort& sDensity) { m_sMeshDensity = sDensity; }


protected:

private:

    class CClientTerrainManager*  m_pTerrainManager;
    CVector                       m_vecPosition;
    CVector2D                     m_vecSize;
    ushort                        m_sMeshDensity;
    std::vector<TerrainPolygon*>  vecMesh;
    std::vector<TerrainSelect*>   vecSelected;
};

#endif
