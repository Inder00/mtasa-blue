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

enum eSelectType {
    SELECT_TYPE_SET,
    SELECT_TYPE_ADD,
    SELECT_TYPE_SUBSTRACT,
    SELECT_TYPE_UNSET,
};

enum eSelectTool {
    SELECT_TOOL_BYVERTEXID,
    SELECT_TOOL_BYPOLYGONID,
    SELECT_TOOL_NEAREST,
    SELECT_TOOL_INRANGE,
    SELECT_TOOL_INRANGESOFT,
    SELECT_TOOL_GROW,
    SELECT_TOOL_SHRINK,
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

struct TerrainSelection {
    TerrainVertex* vertex;
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

    std::vector<TerrainVertex*>  GetVertices(void) { return m_vecMeshVertices;  }
    std::vector<TerrainPolygon*> GetPolygons(void) { return m_vecMeshPolygons;  }

    void BuildMesh(void);
    char AddTexture(SString textureName);
    char SetDefaultTexture(SString textureName);
    void DrawPreview(float fDrawDistance, bool bDrawVertices, bool bDrawPolygons, bool bDrawVerticesId);
    void Select(lua_State* luaVM);

protected:

private:

    class CClientTerrainManager*   m_pTerrainManager;
    CVector                        m_vecPosition;
    CVector2D                      m_vecSize;
    CVector2D                      m_vecMeshDensity;
    SString                        m_meshType;
    std::vector<TerrainVertex*>    m_vecMeshVertices;
    std::vector<TerrainPolygon*>   m_vecMeshPolygons;
    std::vector<TerrainSelection*> m_vecSelected;
    std::vector<SString>           m_vecTextures;
    SString                        m_strDefaultTexture;
};

#endif
