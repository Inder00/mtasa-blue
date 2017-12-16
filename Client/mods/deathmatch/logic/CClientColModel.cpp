/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientColModel.cpp
*  PURPOSE:     Model collision (.col file) entity class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*
*****************************************************************************/

#include "StdInc.h"
#include "../game_sa/CColModelSA.h"

CClientColModel::CClientColModel ( CClientManager* pManager, ElementID ID ) : ClassInit ( this ), CClientEntity ( ID )
{
    // Init
    m_pManager = pManager;
    m_pColModelManager = pManager->GetColModelManager ();
    m_pColModel = NULL;

    SetTypeName ( "col" );

    // Add us to DFF manager's list
    m_pColModelManager->AddToList ( this );
}


CClientColModel::~CClientColModel ( void )
{
    // Remove us from DFF manager's list
    m_pColModelManager->RemoveFromList ( this );

    // Unreplace our cols
    RestoreAll ();

    if ( m_pColModel )
        delete m_pColModel;
}


bool CClientColModel::LoadCol ( const SString& strFile, bool bIsRawData )
{
    // Not already got a col model?
    if ( !m_pColModel )
    {
        SString strFilename;
        CBuffer buffer;
        if ( !bIsRawData )
        {
            strFilename = strFile;
            buffer.LoadFromFile( strFilename );
            g_pClientGame->GetResourceManager()->ValidateResourceFile( strFilename, buffer );
        }
        else
        {
            buffer = CBuffer( strFile, strFile.length() );
        }

        if ( !g_pCore->GetNetwork()->CheckFile( "col", strFilename, buffer.GetData(), buffer.GetSize() ) )
            return false;

        // Load the collision file
        m_pColModel = g_pGame->GetRenderWare ()->ReadCOL ( buffer );

        // Success if the col model is != NULL
        return ( m_pColModel != NULL );
    }

    // Failed. Already loaded
    return false;
}


bool CClientColModel::Replace ( unsigned short usModel )
{
    // We have a model loaded?
    if ( m_pColModel )
    {
        // Check if anyone has replaced that model already. If so make it forget that
        // it replaced it. We're the new replacer.
        CClientColModel* pAlready = m_pColModelManager->GetElementThatReplaced ( usModel );
        if ( pAlready )
        {
            pAlready->m_Replaced.remove ( usModel );
        }

        // Replace the collisions
        CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModel );
        pModelInfo->SetColModel ( m_pColModel );

        // Remember that we replaced it
        m_Replaced.push_back ( usModel );

        // Success
        return true;
    }

    // Failed
    return false;
}


void CClientColModel::Restore ( unsigned short usModel )
{
    // Restore it
    InternalRestore ( usModel );

    // Remove the restored id from the list
    m_Replaced.remove ( usModel );
}


void CClientColModel::RestoreAll ( void )
{
    // Loop through our replaced ids
    std::list < unsigned short > ::iterator iter = m_Replaced.begin ();
    for ( ; iter != m_Replaced.end (); iter++ )
    {
        // Restore this model
        InternalRestore ( *iter );
    }

    // Clear the list
    m_Replaced.clear ();
}


bool CClientColModel::HasReplaced ( unsigned short usModel )
{
    // Loop through our replaced ids
    std::list < unsigned short > ::iterator iter = m_Replaced.begin ();
    for ( ; iter != m_Replaced.end (); iter++ )
    {
        // Is this the given ID
        if ( *iter == usModel )
        {
            // We have replaced it
            return true;
        }
    }

    // We have not replaced it
    return false;
}


void CClientColModel::InternalRestore ( unsigned short usModel )
{
    // Grab the model info and restore it
    CModelInfo* pModel = g_pGame->GetModelInfo ( usModel );
    pModel->RestoreColModel ();
}


// Return true if data looks like COL file contents
bool CClientColModel::IsCOLData(const SString& strData)
{
    return strData.length() > 32 && memcmp(strData, "COL", 3) == 0 && strData[7] == 0;
}

unsigned short CClientColModel::GetModelPolygonCount()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return (unsigned short)pModelInfo->GetModelPolygonCount(m_pColModel);
}

unsigned short CClientColModel::GetModelVerticesCount()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return (unsigned short)pModelInfo->GetModelVerticesCount(m_pColModel);
}

float CClientColModel::GetModelBoundingBoxRadius()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetModelBoundingBoxRadius(m_pColModel);
}

CVector CClientColModel::GetModelBoundingBoxOffset()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetModelBoundingBoxOffset(m_pColModel);
}

CVector CClientColModel::GetModelBoundingBoxVecMin()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetModelBoundingBoxVecMin(m_pColModel);
}

CVector CClientColModel::GetModelBoundingBoxVecMax()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetModelBoundingBoxVecMax(m_pColModel);
}

bool CClientColModel::SetModelPolygonSurface(unsigned short usPolygonId, unsigned short usSurfaceId)
{
    if (GetModelPolygonCount() >= usPolygonId && usPolygonId != NULL)
    {
        CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
        return pModelInfo->SetModelPolygonSurface(m_pColModel, usPolygonId-1, usSurfaceId);
    }
    else
    {
        return false;
    }
}

CVector CClientColModel::GetVertexPosition(unsigned short usPolygonId)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetVertexPosition(m_pColModel, usPolygonId);
}

bool CClientColModel::SetVertexPosition(unsigned short usVertex, CVector position)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->SetVertexPosition(m_pColModel, usVertex, position);
}

void CClientColModel::GetTriangleConnectedVertices(unsigned short usPolygon, unsigned short &vertex1, unsigned short &vertex2, unsigned short &vertex3)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetTriangleConnetedVertices(m_pColModel, usPolygon, vertex1, vertex2, vertex3);
}

bool CClientColModel::SetTriangleSetLighting(unsigned short usPolygon, unsigned short day, unsigned short night)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->SetTriangleSetLighting(m_pColModel, usPolygon, day, night);
}

bool CClientColModel::SetTriangleConnectedVertices(unsigned short usPolygon, unsigned short vertex1, unsigned short vertex2, unsigned short vertex3)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->SetTriangleConnectedVertices(m_pColModel, usPolygon, vertex1,vertex2,vertex3);
}

unsigned short CClientColModel::CreateVertex(CVector vecPosition)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->CreateVertex(m_pColModel, vecPosition);
}

unsigned short CClientColModel::CreatePolygon(unsigned short vertex1, unsigned short vertex2, unsigned short vertex3)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->CreatePolygon(m_pColModel, vertex1, vertex2, vertex3);
}

bool CClientColModel::DestroyVertex(unsigned short usVertex)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->DestroyVertex(m_pColModel, usVertex);
}

bool CClientColModel::DestroyPolygon(unsigned short usPolygon)
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->DestroyPolygon(m_pColModel, usPolygon);
}

void CClientColModel::UpdateBoundingBox()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    pModelInfo->UpdateBoundingBox(m_pColModel);
}

std::vector < CColTriangleSA > CClientColModel::GetAllPolygons()
{
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(usModel);
    return pModelInfo->GetAllPolygons(m_pColModel);
}

CVector CClientColModel::GetTrianglePosition(unsigned short usPolygon)
{
    unsigned short vertex1 = NULL;
    unsigned short vertex2 = NULL;
    unsigned short vertex3 = NULL;
    GetTriangleConnectedVertices(usPolygon, vertex1, vertex2, vertex3);
    CVector position;
    position += GetVertexPosition(vertex1) / 128;
    position += GetVertexPosition(vertex2) / 128;
    position += GetVertexPosition(vertex3) / 128;
    return position / 3;
}

bool CClientColModel::IsValidPolygonId(unsigned short usPolygon)
{
    return usPolygon >= 0 && usPolygon < GetModelPolygonCount();
}

// due performance reason, i pass there vector with all polygons to prevent use "GetAllPolygons" eg. 500 times every function use
void CClientColModel::GetNeighbors(CColTriangleSA polygon, std::vector < CColTriangleSA > &polygons, std::vector < int > &neighbors, bool recursion)
{
    for (int i = 0; i < polygons.size(); i++)
    {
        CColTriangleSA triangle = polygons.at(i);
        if (polygon.v1 == triangle.v1 || polygon.v1 == triangle.v2 || polygon.v1 == triangle.v3 ||
            polygon.v2 == triangle.v1 || polygon.v2 == triangle.v2 || polygon.v2 == triangle.v3 ||
            polygon.v3 == triangle.v1 || polygon.v3 == triangle.v2 || polygon.v3 == triangle.v3
            )
        {
            if (std::find(neighbors.begin(), neighbors.end(), i) == neighbors.end())
            {
                neighbors.push_back(i);
                if(recursion)
                    GetNeighbors(triangle, polygons, neighbors, true);
            }
        }
    }
}

bool CClientColModel::SelectElement(lua_State* luaVM, unsigned short usPolygon)
{
    std::vector < CColTriangleSA > polygons = GetAllPolygons();
    lua_newtable(luaVM);
    CColTriangleSA polygon = polygons.at(usPolygon);
    std::vector < int > neighbors;
    GetNeighbors(polygon, polygons, neighbors, true);
    for (int i = 0; i < neighbors.size(); i++)
    {
        lua_pushnumber(luaVM, i + 1);
        lua_pushnumber(luaVM, neighbors.at(i) + 1);
        lua_settable(luaVM, -3);
    }
    return true;
}

bool CClientColModel::Grow(lua_State* luaVM, unsigned short usPolygon, unsigned short &usNext)
{
    std::vector < CColTriangleSA > polygons = GetAllPolygons();
    CColTriangleSA polygon = polygons.at(usPolygon);
    std::vector < int > neighbors;
    GetNeighbors(polygon, polygons, neighbors, false);
    for (int i = 0; i < neighbors.size(); i++)
    {
        lua_pushnumber(luaVM, ++usNext);
        lua_pushnumber(luaVM, neighbors.at(i) + 1);
        lua_settable(luaVM, -3);
    }
    return true;
}