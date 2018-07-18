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

enum eMeshType {
    MESH_TRIANGLE,
    MESH_DIAMOND,
};

struct TerrainVertex {
    CVector position;
    float lightPower;
    CVector lightColor;
    float u, v;
};

struct TerrainPolygon {
    TerrainVertex* vertex[3];
    char texture[24];
    char textureMask[24];
};

struct TerrainSelect {
    TerrainVertex vertex;
    float power;
};

class CClientTerrain;

class CClientTerrain : public CClientEntity
{

public:

    CClientTerrain(class CClientManager* pManager, ElementID ID);
    ~CClientTerrain(void);

    eClientEntityType GetType(void) const { return CCLIENTTERRAIN; }

    void Unlink(void);

    void GetPosition(CVector& vecPosition) const { vecPosition = m_vecPosition; }
    void SetPosition(const CVector& vecPosition) { m_vecPosition = vecPosition; }

    CVector2D GetSize(void) { return m_vecSize; }
    void      SetSize(CVector2D vecSize) { m_vecSize = vecSize; }

    CVector2D GetDensity(void) { return m_vecMeshDensity; }
    void      SetDensity(CVector2D sDensity) { m_vecMeshDensity = sDensity; }

    void    SetMeshType(SString meshType) { m_meshType = meshType; }
    SString GetMeshType(void) { return m_meshType;  }

    void BuildMesh(void);
    char AddTexture(SString textureName);
    char SetDefaultTexture(SString textureName);
    void DrawPreview(bool bDrawVertexIds);

protected:

private:

    class CClientTerrainManager*  m_pTerrainManager;
    CVector                       m_vecPosition;
    CVector2D                     m_vecSize;
    CVector2D                     m_vecMeshDensity;
    SString                       m_meshType;
    std::vector<TerrainVertex*>   m_vecMeshVertices;
    std::vector<TerrainPolygon*>  m_vecMeshPolygons;
    std::vector<TerrainSelect*>   m_vecSelected;
    std::vector<SString>          m_vecTextures;
    SString                       m_strDefaultTexture;
};

#endif
