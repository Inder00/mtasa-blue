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
}

void CClientTerrain::Unlink(void)
{
}

void CClientTerrain::BuildMesh(void)
{
    float fGapsX = m_vecSize.fX / (m_vecMeshDensity.fX - 1);
    float fGapsY = m_vecSize.fY / (m_vecMeshDensity.fY - 1);

    // build vertices
    for (ushort x = 0; x < m_vecMeshDensity.fX; ++x)
    {
        for (ushort y = 0; y < m_vecMeshDensity.fY; ++y)
        {
            TerrainVertex* vertex = new TerrainVertex;
            vertex->position = *new CVector(fGapsX * x - m_vecSize.fX / 2, fGapsY * y - m_vecSize.fY / 2, 0);
            //strcpy(vertex->texture, m_strDefaultTexture.c_str());
            m_vecMeshVertices.push_back(vertex);
        }
    }

    // build polygons


    for (uint i = 0; i < m_vecMeshVertices.size() - m_vecMeshDensity.fY - 1; i++)
    {
        if (i % (int)m_vecMeshDensity.fY != m_vecMeshDensity.fY - 1)
        {
            TerrainVertex* vertex[3];

            vertex[0] = m_vecMeshVertices.at(i);
            vertex[1] = m_vecMeshVertices.at(i + 1);
            vertex[2] = m_vecMeshVertices.at(i + 1 + m_vecMeshDensity.fY);

            TerrainPolygon* polygon = new TerrainPolygon;
            polygon->vertex[0] = vertex[0];
            polygon->vertex[1] = vertex[1];
            polygon->vertex[2] = vertex[2];
            m_vecMeshPolygons.push_back(polygon);
        }
    }

    for (ushort x = 1; x < m_vecMeshDensity.fX; ++x)
    {
        TerrainVertex* vertex[3];

        vertex[0] = m_vecMeshVertices.at((x - 1) * m_vecMeshDensity.fY);
        vertex[1] = m_vecMeshVertices.at(x * m_vecMeshDensity.fY);
        vertex[2] = m_vecMeshVertices.at(x * m_vecMeshDensity.fY + 1);

        TerrainPolygon* polygon = new TerrainPolygon;
        polygon->vertex[0] = vertex[0];
        polygon->vertex[1] = vertex[1];
        polygon->vertex[2] = vertex[2];
        m_vecMeshPolygons.push_back(polygon);
    }

    for (ushort y = m_vecMeshVertices.size() - m_vecMeshDensity.fY + 1; y <= m_vecMeshVertices.size() - 1; ++y)
    {
        TerrainVertex* vertex[3];

        vertex[0] = m_vecMeshVertices.at(y);
        vertex[1] = m_vecMeshVertices.at(y - 1);
        vertex[2] = m_vecMeshVertices.at(y - 1 - m_vecMeshDensity.fY);

        TerrainPolygon* polygon = new TerrainPolygon;
        polygon->vertex[0] = vertex[0];
        polygon->vertex[1] = vertex[1];
        polygon->vertex[2] = vertex[2];
        m_vecMeshPolygons.push_back(polygon);
    }

}

char CClientTerrain::AddTexture(SString strTexture)
{
    m_vecTextures.push_back(strTexture);
    return m_vecTextures.size();    // return id of my texture
}

char CClientTerrain::SetDefaultTexture(SString strTexture)
{
    m_strDefaultTexture = strTexture;
    return CClientTerrain::AddTexture(strTexture);
}

void CClientTerrain::DrawPreview(float fDrawDistance, bool bDrawVertices, bool bDrawPolygons, bool bDrawVerticesId)
{
    
    SColorARGB          color(255, 0, 255, 0);
    CGraphicsInterface* pGraphics = g_pCore->GetGraphics();

    if (bDrawVertices)
    {
        SColorARGB          color(255, 255, 0, 0);
        for (uint i = 0; i < m_vecMeshVertices.size(); i++) {
            TerrainVertex* vertex = m_vecMeshVertices[i];
            CVector vecStart(vertex->position.fX, vertex->position.fY, vertex->position.fZ - 0.03f);
            CVector vecEnd(vertex->position.fX, vertex->position.fY, vertex->position.fZ + 0.03f);
            pGraphics->DrawLine3DQueued(vertex->position + m_vecPosition, vecEnd + m_vecPosition, 3, color, false);
        }
    }

    if (bDrawPolygons)
    {
        for (uint i = 0; i < m_vecMeshPolygons.size(); i++) {
            TerrainPolygon* polygon = m_vecMeshPolygons[i];
            TerrainVertex* vertex1 = polygon->vertex[0];
            TerrainVertex* vertex2 = polygon->vertex[1];
            TerrainVertex* vertex3 = polygon->vertex[2];
            pGraphics->DrawLine3DQueued(vertex1->position + m_vecPosition, vertex2->position + m_vecPosition, 1, color, false);
            pGraphics->DrawLine3DQueued(vertex2->position + m_vecPosition, vertex3->position + m_vecPosition, 1, color, false);
            pGraphics->DrawLine3DQueued(vertex3->position + m_vecPosition, vertex1->position + m_vecPosition, 1, color, false);
        }
    }

    if (bDrawVertices)
    {
        for (uint i = 0; i < m_vecMeshVertices.size(); i++) {
            TerrainVertex* vertex = m_vecMeshVertices[i];
            CVector vecScreen;
            if (CStaticFunctionDefinitions::GetScreenFromWorldPosition(vertex->position + m_vecPosition, vecScreen, 0, true))
            {
                pGraphics->DrawStringQueued(vecScreen.fX, vecScreen.fY, vecScreen.fX, vecScreen.fY, 0xFFFFFFFF, SString("%i", i + 1).c_str(), 1, 1, DT_NOCLIP | DT_CENTER, NULL, true, true);
            }
        }
    }
}


void CClientTerrain::Select(lua_State* luaVM)
{

}
