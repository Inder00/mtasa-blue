/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientDFF.cpp
*  PURPOSE:     .dff model handling class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*
*****************************************************************************/

#include "StdInc.h"

CClientDFF::CClientDFF ( CClientManager* pManager, ElementID ID ) : ClassInit ( this ), CClientEntity ( ID )
{
    // Init
    m_pManager = pManager;
    m_pDFFManager = pManager->GetDFFManager ();

    SetTypeName ( "dff" );

    // Add us to DFF manager list
    m_pDFFManager->AddToList ( this );
}


CClientDFF::~CClientDFF ( void )
{
    // Remove us from DFF manager list
    m_pDFFManager->RemoveFromList ( this );

    // Restore all our models
    RestoreModels ();

    // Unload our clumps
    UnloadDFF ();
}


// Get a clump which has been loaded to replace the specified model id
RpClump* CClientDFF::GetLoadedClump ( ushort usModelId )
{
    if ( usModelId == 0 )
        return NULL;

    SLoadedClumpInfo& info = MapGet ( m_LoadedClumpInfoMap, usModelId );

    if ( !info.bTriedLoad )
    {
        info.bTriedLoad = true;

        // Make sure previous model+collision is loaded
        m_pManager->GetModelRequestManager ()->RequestBlocking ( usModelId, "CClientDFF::LoadDFF" );

        // Attempt loading it
        if( !m_bIsRawData ) // We have file
        {
            if ( g_pCore->GetNetwork ()->CheckFile ( "dff", m_strDffFilename ) )
            {
                g_pClientGame->GetResourceManager()->ValidateResourceFile( m_strDffFilename, CBuffer() );
                info.pClump = g_pGame->GetRenderWare ()->ReadDFF ( m_strDffFilename, CBuffer(), usModelId, CClientVehicleManager::IsValidModel ( usModelId ) );
            }
        }
        else //We have raw data
        {
            info.pClump = g_pGame->GetRenderWare ()->ReadDFF ( NULL, m_RawDataBuffer, usModelId, CClientVehicleManager::IsValidModel ( usModelId ) );

            // Remove raw data from memory (can only do one replace when using raw data)
            m_RawDataBuffer.Clear ();
        }
    }

    return info.pClump;
}


bool CClientDFF::LoadDFF ( const SString& strFile, bool bIsRawData )
{
    // Should only be called once, directly after construction
    m_bIsRawData = bIsRawData;
    if( !m_bIsRawData ) // If we have actual file
    {
        assert ( m_strDffFilename.empty () );

        m_strDffFilename = strFile;
        if ( m_strDffFilename.empty () )
            return false;

        if ( !FileExists ( m_strDffFilename ) )
            return false;

        if ( !g_pCore->GetNetwork ()->CheckFile ( "dff", m_strDffFilename ) )
            return false;
    }
    else
    {
        m_RawDataBuffer = CBuffer( strFile, strFile.length() );
        if ( !g_pCore->GetNetwork ()->CheckFile ( "dff", "", m_RawDataBuffer.GetData(), m_RawDataBuffer.GetSize() ) )
            return false;
    }

    // Do actual load later (in ReplaceModel)
    return true;
}


void CClientDFF::UnloadDFF ( void )
{
    for ( std::map < ushort, SLoadedClumpInfo >::iterator iter = m_LoadedClumpInfoMap.begin () ; iter != m_LoadedClumpInfoMap.end () ; ++iter )
    {
        SLoadedClumpInfo& info = iter->second;
        if ( info.pClump )
            g_pGame->GetRenderWare ()->DestroyDFF ( info.pClump );
    }

    m_LoadedClumpInfoMap.clear ();
}


bool CClientDFF::ReplaceModel ( ushort usModel, bool bAlphaTransparency )
{
    // Record attempt in case it all goes wrong
    CArgMap argMap;
    argMap.Set( "id", usModel );
    argMap.Set( "reason", "ReplaceModel" );
    SetApplicationSetting( "diagnostics", "gta-model-fail", argMap.ToString() );

    bool bResult = DoReplaceModel( usModel, bAlphaTransparency );

    SetApplicationSetting( "diagnostics", "gta-model-fail", "" );
    return bResult;
}


bool CClientDFF::DoReplaceModel ( ushort usModel, bool bAlphaTransparency )
{
    if ( !CClientDFFManager::IsReplacableModel( usModel ) )
        return false;

    // Get clump loaded for this model id
    RpClump* pClump = GetLoadedClump ( usModel );

    // We have a DFF?
    if ( pClump )
    {
        // Have someone already replaced that model?
        CClientDFF* pReplaced = m_pDFFManager->GetElementThatReplaced ( usModel );
        if ( pReplaced )
        {
            // Remove it from its list so it won't restore the object if
            // it's destroyed or its resource is when it's been replaced
            // again by an another resource.
            pReplaced->m_Replaced.remove ( usModel );
        }

        // Is this a vehicle ID?
        if ( CClientVehicleManager::IsValidModel ( usModel ) )
        {
            return ReplaceVehicleModel ( pClump, usModel, bAlphaTransparency );
        }
        else if ( CClientObjectManager::IsValidModel ( usModel ) )
        {
            if ( CVehicleUpgrades::IsUpgrade ( usModel ) )
            {
                bool bResult = ReplaceObjectModel ( pClump, usModel, bAlphaTransparency );
                // 'Restream' upgrades after model replacement
                m_pManager->GetVehicleManager ()->RestreamVehicleUpgrades ( usModel );
                return bResult;
            }
            if ( CClientPedManager::IsValidWeaponModel ( usModel ) )
            {
                return ReplaceWeaponModel ( pClump, usModel, bAlphaTransparency );
            }
            return ReplaceObjectModel ( pClump, usModel, bAlphaTransparency );
        }
        else if ( CClientPlayerManager::IsValidModel ( usModel ) )
        {
            return ReplacePedModel ( pClump, usModel, bAlphaTransparency );
        }
    }

    // No supported type or no loaded clump
    return false;
}


bool CClientDFF::HasReplaced ( ushort usModel )
{
    // See if we have a match in our list
    std::list < ushort > ::iterator iter = m_Replaced.begin ();
    for ( ; iter != m_Replaced.end (); iter++ )
    {
        // Compare the models
        if ( *iter == usModel )
        {
            return true;
        }
    }

    // We haven't replaced this model
    return false;
}


void CClientDFF::RestoreModel ( ushort usModel )
{
    // Restore the model and remove it from the list
    InternalRestoreModel ( usModel );
    m_Replaced.remove ( usModel );
}


void CClientDFF::RestoreModels ( void )
{
    // Loop through our list over replaced models
    std::list < ushort > ::iterator iter = m_Replaced.begin ();
    for ( ; iter != m_Replaced.end (); iter++ )
    {
        // Restore this model
        InternalRestoreModel ( *iter );
    }

    // Clear the list
    m_Replaced.clear ();
}


void CClientDFF::InternalRestoreModel ( ushort usModel )
{
    // Is this a vehicle ID?
    if ( CClientVehicleManager::IsValidModel ( usModel ) )
    {
        // Stream the vehicles of that model out so we have no
        // loaded when we do the restore. The streamer will
        // eventually stream them back in with async loading.
        m_pManager->GetVehicleManager ()->RestreamVehicles ( usModel );
    }

    // Is this an object ID?
    else if ( CClientObjectManager::IsValidModel ( usModel ) )
    {
        if ( CClientPedManager::IsValidWeaponModel ( usModel ) )
        {
            // Stream the weapon of that model out so we have no
            // loaded when we do the restore. The streamer will
            // eventually stream them back in with async loading.
            m_pManager->GetPedManager ()->RestreamWeapon ( usModel );
            m_pManager->GetPickupManager ()->RestreamPickups ( usModel );
        }
        // Stream the objects of that model out so we have no
        // loaded when we do the restore. The streamer will
        // eventually stream them back in with async loading.
        m_pManager->GetObjectManager ()->RestreamObjects ( usModel );
        g_pGame->GetModelInfo ( usModel )->RestreamIPL ();
    }
    // Is this an ped ID?
    else if ( CClientPlayerManager::IsValidModel ( usModel ) )
    {
        // Stream the ped of that model out so we have no
        // loaded when we do the restore. The streamer will
        // eventually stream them back in with async loading.
        m_pManager->GetPedManager ()->RestreamPeds ( usModel );
    }
    else
        return;

    // Restore all the models we replaced.
    CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModel );
    pModelInfo->RestoreOriginalModel ();
    pModelInfo->ResetAlphaTransparency ();

    // 'Restream' upgrades after model replacement to propagate visual changes with immediate effect
    if ( CClientObjectManager::IsValidModel ( usModel ) && CVehicleUpgrades::IsUpgrade ( usModel ) )
        m_pManager->GetVehicleManager ()->RestreamVehicleUpgrades ( usModel );

    // Force dff reload if this model id is used again
    SLoadedClumpInfo* pInfo = MapFind ( m_LoadedClumpInfoMap, usModel );
    if ( pInfo )
    {
        if ( pInfo->pClump )
            g_pGame->GetRenderWare ()->DestroyDFF ( pInfo->pClump );
        MapRemove ( m_LoadedClumpInfoMap, usModel );
    }
}


bool CClientDFF::ReplaceObjectModel ( RpClump* pClump, ushort usModel, bool bAlphaTransparency )
{
    // Stream out all the object models with matching ID.
    // Streamer will stream them back in async after a frame
    // or so.
    m_pManager->GetObjectManager ()->RestreamObjects ( usModel );
    g_pGame->GetModelInfo ( usModel )->RestreamIPL ();

    // Grab the model info for that model and replace the model
    CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModel );
    pModelInfo->SetCustomModel ( pClump );

    pModelInfo->SetAlphaTransparencyEnabled( bAlphaTransparency );

    // Remember that we've replaced that object model
    m_Replaced.push_back ( usModel );

    // Success
    return true;
}

bool CClientDFF::ReplaceWeaponModel ( RpClump* pClump, ushort usModel, bool bAlphaTransparency )
{
    // Stream out all the weapon models with matching ID.
    // Streamer will stream them back in async after a frame
    // or so.
    m_pManager->GetPedManager ()->RestreamWeapon ( usModel );
    m_pManager->GetPickupManager ()->RestreamPickups ( usModel );

    // Grab the model info for that model and replace the model
    CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModel );
    pModelInfo->SetCustomModel ( pClump );

    pModelInfo->SetAlphaTransparencyEnabled( bAlphaTransparency );

    // Remember that we've replaced that weapon model
    m_Replaced.push_back ( usModel );

    // Success
    return true;
}

bool CClientDFF::ReplacePedModel ( RpClump* pClump, ushort usModel, bool bAlphaTransparency )
{
    // Stream out all the weapon models with matching ID.
    // Streamer will stream them back in async after a frame
    // or so.
    m_pManager->GetPedManager ()->RestreamPeds ( usModel );

    // Grab the model info for that model and replace the model
    CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModel );
    pModelInfo->SetCustomModel ( pClump );

    pModelInfo->SetAlphaTransparencyEnabled( bAlphaTransparency );

    // Remember that we've replaced that weapon model
    m_Replaced.push_back ( usModel );

    // Success
    return true;
}

bool CClientDFF::ReplaceVehicleModel ( RpClump* pClump, ushort usModel, bool bAlphaTransparency )
{
    // Make sure previous model+collision is loaded
    m_pManager->GetModelRequestManager ()->RequestBlocking ( usModel, "CClientDFF::ReplaceVehicleModel" );

    // Grab the model info for that model and replace the model
    CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModel );
    pModelInfo->SetCustomModel ( pClump );

    pModelInfo->SetAlphaTransparencyEnabled( bAlphaTransparency );

    // Remember that we've replaced that vehicle model
    m_Replaced.push_back ( usModel );

    // Stream out all the vehicle models with matching ID.
    // Streamer will stream them back in async after a frame
    // or so.
    m_pManager->GetVehicleManager ()->RestreamVehicles ( usModel );

    // Success
    return true;
}

// Return true if data looks like DFF file contents
bool CClientDFF::IsDFFData ( const SString& strData )
{
    return strData.length() > 32 && memcmp( strData, "\x10\x00\x00\x00", 4 ) == 0;
}

int CClientDFF::GetPolygonIdInMesh(RpGeometry* pGeometry, RpMesh* pMesh, ushort uiTriangle)
{
    for (ushort i = 0; i < pMesh->numIndices / 3; i++)
    {
        ushort indices1 = pMesh->indices[(i * 3) + 0];
        ushort indices2 = pMesh->indices[(i * 3) + 1];
        ushort indices3 = pMesh->indices[(i * 3) + 2];

        for (ushort i2 = 0; i2 < pGeometry->triangles_size; i2++)
        {
            RpTriangle pTriangle = pGeometry->triangles[i2];
            if (i2 == uiTriangle &&
                pTriangle.v[0] == indices1 &&
                pTriangle.v[1] == indices2 &&
                pTriangle.v[2] == indices3)
                return i;
        }
    }
    return -1;
}

RpMesh* CClientDFF::GetMeshFromPolygonId(RpGeometry* pGeometry, ushort uiTriangle)
{
    RpMesh* mesh = pGeometry->header->getMeshes();
    ushort meshCount = pGeometry->header->numMeshes;
    while (meshCount>0)
    {
        meshCount--;
        RpMesh* myMesh = &mesh[meshCount];
        for (ushort i = 0; i < myMesh->numIndices / 3; i++)
        {
            ushort indices1 = myMesh->indices[(i * 3) + 0];
            ushort indices2 = myMesh->indices[(i * 3) + 1];
            ushort indices3 = myMesh->indices[(i * 3) + 2];

            for (ushort i2 = 0; i2 < pGeometry->triangles_size; i2++)
            {
                RpTriangle pTriangle = pGeometry->triangles[i2];
                if (i2 == uiTriangle &&
                    pTriangle.v[0] == indices1 &&
                    pTriangle.v[1] == indices2 &&
                    pTriangle.v[2] == indices3)
                    return myMesh;
            }
        }
    }
    return NULL;
}

int CClientDFF::GetMeshIdFromPolygonId(RpGeometry* pGeometry, ushort uiTriangle)
{
    RpMesh* mesh = pGeometry->header->getMeshes();
    ushort usMesh = pGeometry->header->numMeshes;
    while (usMesh>0)
    {
        usMesh--;
        RpMesh* myMesh = &mesh[usMesh];
        for (ushort i = 0; i < myMesh->numIndices / 3; i++)
        {
            ushort indices1 = myMesh->indices[(i * 3) + 0];
            ushort indices2 = myMesh->indices[(i * 3) + 1];
            ushort indices3 = myMesh->indices[(i * 3) + 2];

            for (ushort i2 = 0; i2 < pGeometry->triangles_size; i2++)
            {
                RpTriangle pTriangle = pGeometry->triangles[i2];
                if (i2 == uiTriangle &&
                    pTriangle.v[0] == indices1 &&
                    pTriangle.v[1] == indices2 &&
                    pTriangle.v[2] == indices3)
                    return usMesh;
            }
        }
    }
    return 9999;
}

bool CClientDFF::GeometryDestroyVertex(RpGeometry* pGeometry, ushort usVertex)
{
    std::vector < ushort > vecPolygons = GetPolygonsUsedByVertex(pGeometry, usVertex);
    ushort polygons = vecPolygons.size();
    std::sort(vecPolygons.begin(), vecPolygons.end(), std::greater<ushort>());  // sort from MAX to MIN
    for (ushort i = 0; i < polygons; i++) // destroy all polygons which use this vertex
    {
        GeometryDestroyPolygon(pGeometry, vecPolygons.at(i));
    }
    ushort lastVertex = pGeometry->vertices_size;
    pGeometry->vertices_size--;
    RwV3d* newVerts = reinterpret_cast<RwV3d *>(malloc(pGeometry->vertices_size * sizeof(RwV3d)));
    ushort next = 0;
    for (ushort i = 0; i < lastVertex; i++)    // remove vertex
    {
        if (i != usVertex)
            newVerts[next++] = pGeometry->morphTarget->verts[i];
    }

    RpMesh* mesh = pGeometry->header->getMeshes();
    ushort meshCount = pGeometry->header->numMeshes;
    while (meshCount > 0)
    {
        meshCount--;
        RpMesh* myMesh = &mesh[meshCount];
        for (ushort i = 0; i < myMesh->numIndices; i++)
        {
            ushort indic = myMesh->indices[i];
            if (indic > usVertex)
                myMesh->indices[i]--;
        }
    }
    for (ushort i = 0; i < pGeometry->triangles_size; i++) // fix gap
    {
        RpTriangle* triangle = &pGeometry->triangles[i];

        if (triangle->v[0] >= usVertex)
            triangle->v[0] --;
        if (triangle->v[1] >= usVertex)
            triangle->v[1] --;
        if (triangle->v[2] >= usVertex)
            triangle->v[2] --;
    }
    pGeometry->morphTarget->verts = newVerts;
    return true;
}
bool CClientDFF::GeometryDestroyPolygon(RpGeometry* pGeometry, ushort uiTriangle)
{
    ushort meshId = CClientDFF::GetMeshIdFromPolygonId(pGeometry, uiTriangle);
    if (meshId == 9999)
    {
        return false;
    }
    RpMesh* mesh = pGeometry->header->getMeshes();
    RpMesh* myMesh = &mesh[meshId];
    ushort numIndices = myMesh->numIndices;
    if (numIndices <= 0)
    {
        return false;
    }
    pGeometry->triangles_size--;
    myMesh->numIndices -= 3;
    pGeometry->header->totalIndicesInMesh -= 3;
    ushort* polygons = myMesh->indices;
    ushort* newPolygons1 = reinterpret_cast<ushort*>(malloc(numIndices * 4));    // ushort - size=4
    RpTriangle* newPolygons2 = reinterpret_cast<RpTriangle*>(malloc(sizeof(RpTriangle) * pGeometry->triangles_size));

    ushort id = GetPolygonIdInMesh(pGeometry, myMesh, uiTriangle);
    unsigned int next = 0;
    for (int i = 0; i < numIndices/3; i++)
    {
        if (id != i)
        {
            newPolygons1[(next * 3) + 0] = polygons[(i * 3) + 0];
            newPolygons1[(next * 3) + 1] = polygons[(i * 3) + 1];
            newPolygons1[(next * 3) + 2] = polygons[(i * 3) + 2];
            next++;
        }
    }
    next = 0;
    for (int i = 0; i < pGeometry->triangles_size + 1; i++)
    {

        if (i != uiTriangle)
        {
            newPolygons2[next] = pGeometry->triangles[i];
            next++;
        }
    }
    //free(myMesh->indices);  //crash
    //free(pGeometry->triangles);
    myMesh->indices = newPolygons1;
    pGeometry->triangles = newPolygons2;
    return true;
}

char* CClientDFF::GetometryFlags(RpGeometry* pGeometry)
{
    int n =pGeometry->flags;
    char flags[8];
    for (short i = 0; i <= 7; i++)
        flags[i] = (char)((n >> 32-i*4) & 0xF);
    return flags;
}

const RpGeometry * CClientDFF::GeometryTriangleSetVertexIndices(const RpGeometry * geo, RpTriangle * tri, ushort v1, ushort v2, ushort v3)
{
    return g_pGame->GetRenderWare()->GeometryTriangleSetVertexIndices(geo, tri, v1, v2, v3);
}

RpGeometry * CClientDFF::GeometryTriangleSetMaterialId(RpGeometry * geo, RpTriangle * tri, RpMaterial * mat)
{
    return g_pGame->GetRenderWare()->GeometryTriangleSetMaterial(geo, tri, mat);
}

RpAtomic * CClientDFF::AtomicSetGeometry(RpAtomic * atomic, RpGeometry * geometry, unsigned int flags)
{
    return g_pGame->GetRenderWare()->AtomicSetGeometry(atomic, geometry, flags);
}

int CClientDFF::ClumpGetNumAtomics(RpClump * clump)
{
    return g_pGame->GetRenderWare()->ClumpGetNumAtomics(clump);
}
RwTexture* CClientDFF::CreateTexture(RwRaster* pRaster)
{
    return g_pGame->GetRenderWare()->RwCreateTexture(pRaster);
}

RwRaster* CClientDFF::CreateRaster(int width, int height, int depth, int flags)
{
    return g_pGame->GetRenderWare()->RasterCreate(width, height, depth, flags);
}

RpMaterial* CClientDFF::CreateMaterial( void )
{
    return g_pGame->GetRenderWare()->MaterialCreate( );
}

RpMeshHeader* CClientDFF::CreateMeshHeader(unsigned int size)
{
    return g_pGame->GetRenderWare()->CreateMeshHeader(size);
}

bool CClientDFF::CreatePolygon(RpGeometry* pGeometry, ushort vertex1, ushort vertex2, ushort vertex3, ushort usMesh)
{
    if (!pGeometry->header->isValidMeshId(usMesh))
        return false;

    if (!pGeometry->isValidTriangleId(vertex1) || !pGeometry->isValidTriangleId(vertex2) || !pGeometry->isValidTriangleId(vertex3))
        return false;

    RpMesh* mesh = pGeometry->header->getMeshes();
    RpMesh* myMesh = &mesh[usMesh];
    pGeometry->triangles_size++;
    ushort lastPolygon = pGeometry->triangles_size - 1;
    myMesh->numIndices += 3;
    pGeometry->header->totalIndicesInMesh += 3;
    ushort numIndices = myMesh->numIndices;
    ushort* polygons = myMesh->indices;
    ushort* newPolygons1 = reinterpret_cast<ushort*>(malloc(numIndices * 4));    // ushort - size=4
    RpTriangle* newPolygons2 = reinterpret_cast<RpTriangle*>(malloc(sizeof(RpTriangle) * pGeometry->triangles_size));
    for (int i = 0; i < numIndices - 3; i++)
    {
        newPolygons1[i] = polygons[i];
    }
    for (int i = 0; i < lastPolygon; i++)
    {
        newPolygons2[i] = pGeometry->triangles[i];
    }
    newPolygons1[numIndices - 1] = vertex1;
    newPolygons1[numIndices - 2] = vertex2;
    newPolygons1[numIndices - 3] = vertex3;
    newPolygons2[lastPolygon].matId = 0;
    newPolygons2[lastPolygon].v[0] = vertex1;
    newPolygons2[lastPolygon].v[1] = vertex2;
    newPolygons2[lastPolygon].v[2] = vertex3;
    free(myMesh->indices);  //crash
    free(pGeometry->triangles);
    myMesh->indices = newPolygons1;
    pGeometry->triangles = newPolygons2;
    return true;
}

ushort CClientDFF::CreateMesh(RpGeometry* pGeometry)
{
    if (pGeometry->header->numMeshes >= 24)
    {
        return 0;
    }
    ushort lastId = pGeometry->header->numMeshes;
    RpMesh* oldMeshes = pGeometry->header->getMeshes();
    ushort meshSize = sizeof(RpMesh);
    ushort headerSize = sizeof(RpMeshHeader);
    ushort mSize = sizeof(RpMesh) * (lastId + 1) + sizeof(RpMeshHeader);
    RpMeshHeader* newHeader = reinterpret_cast<RpMeshHeader*>(malloc(mSize));
    newHeader->flags = pGeometry->header->flags;
    newHeader->serialNum = pGeometry->header->serialNum;
    newHeader->firstMeshOffset = pGeometry->header->firstMeshOffset;
    newHeader->totalIndicesInMesh = pGeometry->header->totalIndicesInMesh + 3;
    newHeader->numMeshes = pGeometry->header->numMeshes + 1;
    RpMesh* b = newHeader->getMeshes();
    for (int i = 0; i < lastId; i++)
    {
        RpMesh* xd = &b[i];
        xd->numIndices = oldMeshes[i].numIndices;
        xd->indices = oldMeshes[i].indices;
        xd->material = oldMeshes[i].material;
    }
    RpMaterial* mat = CreateMaterial();
    RpMesh* last = &b[lastId];
    ushort indices[3];
    indices[0] = 2;
    indices[1] = 5;
    indices[2] = 25;
    last->numIndices = 3;
    last->indices = indices;
    last->material = mat;
    auto a1_11 = &oldMeshes[0];
    auto a1_12 = &oldMeshes[1];
    auto a1_13 = &oldMeshes[3];
    auto a1_14 = &oldMeshes[5];
    auto a1_15 = &oldMeshes[6];
    auto a1_16 = &oldMeshes[7];
    auto a1_17 = &oldMeshes[8];
    auto a1_18 = &oldMeshes[9];
    pGeometry->header = newHeader;
    auto newMeshes = pGeometry->header->getMeshes();
    auto a1_21 = &newMeshes[0];
    auto a1_22 = &newMeshes[1];
    auto a1_23 = &newMeshes[2];
    auto a1_24 = &newMeshes[6];
    auto a1_25 = &newMeshes[7];
    auto a1_26 = &newMeshes[8];
    auto a1_27 = &newMeshes[9];
    auto a1_28 = &newMeshes[10];
    lastId = pGeometry->materials.entries;
    RpMaterial** newMaterials = reinterpret_cast<RpMaterial**>(malloc(sizeof(RpMaterial) * (lastId + 1)));
    for (int i = 0; i < pGeometry->materials.entries; i++)
    {
        newMaterials[i] = pGeometry->materials.materials[i];
    }
    newMaterials[lastId] = mat;
    newMaterials[lastId]->refs = 1;
    pGeometry->materials.entries++;
    pGeometry->materials.unknown++;
    pGeometry->materials.materials = newMaterials;
    //free(pGeometry->header);
    //abort();
    return pGeometry->header->numMeshes; 
}

RpLight* CClientDFF::CreateLight(int type)
{
    return g_pGame->GetRenderWare()->LightCreate( type );
}

RpClump* CClientDFF::ClumpAddLight(RpClump* clump, RpLight* light)
{
    return g_pGame->GetRenderWare()->ClumpAddLight(clump, light);
}

bool CClientDFF::TransformMove(std::vector< ushort > vertices, CVector vecMove)
{
    if (uimodel != INVALID_MODEL_ID)
    {
        RpClump* pClump = GetLoadedClump(uimodel);
        if (pClump)
        {
            RpAtomic* pAtomic = pClump->getAtomic();
            RpGeometry* pGeometry = pAtomic->geometry;
            for (int i = 0; i < vertices.size(); i++)
            {
                RwV3d* vVert = &pGeometry->morphTarget->verts[vertices.at(i)];
                vVert->x += vecMove.fX;
                vVert->y += vecMove.fY;
                vVert->z += vecMove.fZ;
            }
            return true;
        }
    }
    return false;
}

bool CClientDFF::TransformScale(std::vector< ushort > vertices, CVector vecScale)
{
    if (uimodel != INVALID_MODEL_ID)
    {
        RpClump* pClump = GetLoadedClump(uimodel);
        if (pClump)
        {
            RpAtomic* pAtomic = pClump->getAtomic();
            RpGeometry* pGeometry = pAtomic->geometry;
            CVector offset;
            for (int i = 0; i < vertices.size(); i++)
            {
                RwV3d vVert = pGeometry->morphTarget->verts[vertices.at(i)];
                offset += vVert.getVector();
            }
            offset /= vertices.size();

            for (int i = 0; i < vertices.size(); i++)
            {
                RwV3d *vVert = &pGeometry->morphTarget->verts[vertices.at(i)];
                vVert->x = (vVert->x - offset.fX) * vecScale.fX + offset.fX;
                vVert->y = (vVert->y - offset.fY) * vecScale.fY + offset.fY;
                vVert->z = (vVert->z - offset.fZ) * vecScale.fZ + offset.fZ;
            }
            return true;
        }
    }
    return false;
}

bool CClientDFF::EnableVerticesLighting(RpGeometry* pGeometry)
{
    if ( !pGeometry->isFlag(RpGeometryFlag::rpGEOMETRYPRELIT) )
    {
        pGeometry->flags += RpGeometryFlag::rpGEOMETRYPRELIT;   // lets enable light;
        RwColor* colors = reinterpret_cast<RwColor*>(malloc(pGeometry->vertices_size * sizeof(RwColor)));
        for (ushort i = 0; i < pGeometry->vertices_size; i++)
        {
            RwColor col;
            col.a = 0;
            col.r = 32;
            col.g = 32;
            col.b = 32;
            colors[i] = col;
        }
        pGeometry->colors = colors;
        return true;
    }
    return false;
}

std::vector < ushort > CClientDFF::GetPolygonsUsedByVertex(RpGeometry* pGeometry, ushort usVertex)
{
    std::vector < ushort > vecPolygons;
    for (ushort i = 0; i < pGeometry->triangles_size; i++)
    {
        RpTriangle pTriangle = pGeometry->triangles[i];
        if (pTriangle.v[0] == usVertex ||
            pTriangle.v[1] == usVertex ||
            pTriangle.v[2] == usVertex)
        {
            vecPolygons.push_back(i);
        }
    }
    return vecPolygons;
}

bool CClientDFF::CreateVertex(RpGeometry* pGeometry, CVector vecPosition)
{
    pGeometry->vertices_size++;
    int lastVertex = pGeometry->vertices_size - 1;
    RwV3d* verts = pGeometry->morphTarget->verts;
    RwV3d* newVerts = reinterpret_cast<RwV3d *>(malloc(pGeometry->vertices_size * sizeof(RwV3d)));
    for (int i = 0; i < lastVertex; i++)
    {
        newVerts[i] = verts[i];
    }
    RwV3d vVert;
    vVert.x = vecPosition.fX;
    vVert.y = vecPosition.fY;
    vVert.z = vecPosition.fZ;
    newVerts[lastVertex] = vVert;
    free(pGeometry->morphTarget->verts);
    pGeometry->morphTarget->verts = (RwV3d *)newVerts;
    if (pGeometry->isFlag(RpGeometryFlag::rpGEOMETRYPRELIT))
    {
        RwColor* newColors = reinterpret_cast<RwColor*>(malloc(pGeometry->vertices_size * sizeof(RwColor)));
        for (int i = 0; i < lastVertex; i++)
        {
            newColors[i] = pGeometry->colors[i];
        }
        RwColor color;
        color.a = 0;
        color.r = 32;
        color.g = 32;
        color.b = 32;
        newColors[lastVertex] = color;
        pGeometry->colors = newColors;
        
    }
    return true;
}

void CClientDFF::GetVerticesInMesh(lua_State* luaVM, RpMesh* mesh)
{
    lua_newtable(luaVM);
    std::vector< ushort > vertices;
    for (ushort i = 0; i < mesh->numIndices; i++)
    {
        ushort ind = mesh->indices[i];
        if (std::find(vertices.begin(), vertices.end(), ind) == vertices.end())
            vertices.push_back(ind);
    }
    for (int i = 0; i < vertices.size(); i++) {
        lua_pushnumber(luaVM, i + 1);
        lua_pushnumber(luaVM, vertices[i] + 1);
        lua_settable(luaVM, -3);
    }
}

void CClientDFF::GetVertices(lua_State* luaVM, RpGeometry* pGeometry)
{
    lua_newtable(luaVM);
    for (ushort i = 0; i < pGeometry->vertices_size; i++)
    {
        lua_pushnumber(luaVM, i + 1);
        lua_pushnumber(luaVM, i + 1);
        lua_settable(luaVM, -3);
    }
}

void CClientDFF::GetVerticesInRange(lua_State* luaVM, RpGeometry* pGeometry, CVector vecPosition, float fRange)
{
    lua_newtable(luaVM);
    ushort next = 0;
    for (ushort i = 0; i < pGeometry->vertices_size; i++)
    {
        RwV3d vert = pGeometry->morphTarget->verts[i];
        if (fRange >= (vert.getVector() - vecPosition).Length())
        {
            lua_pushnumber(luaVM, ++next);
            lua_pushnumber(luaVM, i + 1);
            lua_settable(luaVM, -3);
        }
    }
}


void CClientDFF::GetVertexNeares3d(lua_State* luaVM, RpGeometry* pGeometry, CVector vecPosition)
{
    ushort nearest = NULL;
    float distance = 99999;
    for (ushort i = 0; i < pGeometry->vertices_size; i++)
    {
        RwV3d vert = pGeometry->morphTarget->verts[i];
        float dis = DistanceBetweenPoints3D(vecPosition, vert.getVector());
        if (distance > dis)
        {
            distance = dis;
            nearest = i;
        }
    }
    lua_pushnumber(luaVM, nearest + 1);
}

void CClientDFF::GetVertexNeares2d(lua_State* luaVM, RpGeometry* pGeometry, CVector2D vecPosition)
{
    ushort nearest = NULL;
    float distance = 99999;
    for (ushort i = 0; i < pGeometry->vertices_size; i++)
    {
        RwV3d vert = pGeometry->morphTarget->verts[i];
        float dis = DistanceBetweenPoints2D(vecPosition, vert.getVector());
        if (distance > dis)
        {
            distance = dis;
            nearest = i + 1;
        }
    }
    lua_pushnumber(luaVM, nearest);
}

bool CClientDFF::SetPolygonPosition(RpGeometry* pGeometry, ushort usPolygon, CVector newPosition)
{
    RpTriangle pTriangle = pGeometry->triangles[usPolygon];
    RwV3d* vert1 = &pGeometry->morphTarget->verts[pTriangle.v[0]];
    RwV3d* vert2 = &pGeometry->morphTarget->verts[pTriangle.v[1]];
    RwV3d* vert3 = &pGeometry->morphTarget->verts[pTriangle.v[2]];
    CVector moveOffset = newPosition - GetPolygonPosition(pGeometry, usPolygon);
    vert1->x += moveOffset.fX;
    vert2->x += moveOffset.fX;
    vert3->x += moveOffset.fX;
    vert1->y += moveOffset.fY;
    vert2->y += moveOffset.fY;
    vert3->y += moveOffset.fY;
    vert1->z += moveOffset.fZ;
    vert2->z += moveOffset.fZ;
    vert3->z += moveOffset.fZ;
    return true;
}

CVector CClientDFF::GetPolygonPosition(RpGeometry* pGeometry, ushort usPolygon)
{
    RpTriangle pTriangle = pGeometry->triangles[usPolygon];
    RwV3d vert1 = pGeometry->morphTarget->verts[pTriangle.v[0]];
    RwV3d vert2 = pGeometry->morphTarget->verts[pTriangle.v[1]];
    RwV3d vert3 = pGeometry->morphTarget->verts[pTriangle.v[2]];
    CVector avgPosition;
    avgPosition.fX = (vert1.x + vert2.x + vert3.x) / 3;
    avgPosition.fY = (vert1.y + vert2.y + vert3.y) / 3;
    avgPosition.fZ = (vert1.z + vert2.z + vert3.z) / 3;
    return avgPosition;
}

bool CClientDFF::SetPolygonVertices(RpGeometry* pGeometry, ushort usPolygon, ushort vertex1, ushort vertex2, ushort vertex3)
{
    RpMesh* mesh = pGeometry->header->getMeshes();
    ushort meshCount = pGeometry->header->numMeshes;
    while (meshCount>0)
    {
        meshCount--;
        RpMesh* myMesh = &mesh[meshCount];
        for (ushort i = 0; i < myMesh->numIndices / 3; i++)
        {
            ushort indices1 = myMesh->indices[(i * 3) + 0];
            ushort indices2 = myMesh->indices[(i * 3) + 1];
            ushort indices3 = myMesh->indices[(i * 3) + 2];

            for (ushort i2 = 0; i2 < pGeometry->triangles_size; i2++)
            {
                RpTriangle pTriangle = pGeometry->triangles[i2];
                if (i2 == usPolygon &&
                    pTriangle.v[0] == indices1 &&
                    pTriangle.v[1] == indices2 &&
                    pTriangle.v[2] == indices3)
                {
                    myMesh->indices[i * 3] = vertex1;
                    myMesh->indices[i * 3 + 1] = vertex2;
                    myMesh->indices[i * 3 + 2] = vertex3;
                    return true;
                }
            }
        }
    }
    return false;
}

bool CClientDFF::VerticesToolMakePlanear(lua_State* luaVM, RpGeometry* pGeometry, std::vector< ushort > vertices, SString axis)
{
    if (axis == "x" || axis == "y" || axis == "z")
    {
        float averageX = 0;
        float averageY = 0;
        float averageZ = 0;
        for (ushort i = 0; i < vertices.size(); i++)
        {
            RwV3d vVert = pGeometry->morphTarget->verts[vertices.at(i)];
            averageX += vVert.x;
            averageY += vVert.y;
            averageZ += vVert.z;
        }
        if (axis == "x")
        {
            averageX /= vertices.size();
            for (ushort i = 0; i < vertices.size(); i++)
            {
                pGeometry->morphTarget->verts[vertices.at(i)].x = averageX;
            }
            return true;
        }
        else if (axis == "y")
        {
            averageY /= vertices.size();
            for (ushort i = 0; i < vertices.size(); i++)
            {
                pGeometry->morphTarget->verts[vertices.at(i)].y = averageY;
            }
            return true;
        }
        else if (axis == "z")
        {
            averageZ /= vertices.size();
            for (ushort i = 0; i < vertices.size(); i++)
            {
                pGeometry->morphTarget->verts[vertices.at(i)].z = averageZ;
            }
            return true;
        }
    }
    return false;
}