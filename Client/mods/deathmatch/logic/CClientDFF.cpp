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


bool CClientDFF::ReplaceModel ( unsigned short usModel, bool bAlphaTransparency )
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


bool CClientDFF::DoReplaceModel ( unsigned short usModel, bool bAlphaTransparency )
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


bool CClientDFF::HasReplaced ( unsigned short usModel )
{
    // See if we have a match in our list
    std::list < unsigned short > ::iterator iter = m_Replaced.begin ();
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


void CClientDFF::RestoreModel ( unsigned short usModel )
{
    // Restore the model and remove it from the list
    InternalRestoreModel ( usModel );
    m_Replaced.remove ( usModel );
}


void CClientDFF::RestoreModels ( void )
{
    // Loop through our list over replaced models
    std::list < unsigned short > ::iterator iter = m_Replaced.begin ();
    for ( ; iter != m_Replaced.end (); iter++ )
    {
        // Restore this model
        InternalRestoreModel ( *iter );
    }

    // Clear the list
    m_Replaced.clear ();
}


void CClientDFF::InternalRestoreModel ( unsigned short usModel )
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

int CClientDFF::GetPolygonIdInMesh(RpGeometry* pGeometry, RpMesh* pMesh, uint uiTriangleId)
{
    for (uint i = 0; i < pMesh->numIndices / 3; i++)
    {
        unsigned short indices1 = pMesh->indices[(i * 3) + 0];
        unsigned short indices2 = pMesh->indices[(i * 3) + 1];
        unsigned short indices3 = pMesh->indices[(i * 3) + 2];

        for (uint i2 = 0; i2 < pGeometry->triangles_size; i2++)
        {
            RpTriangle pTriangle = pGeometry->triangles[i2];
            if (i2 == uiTriangleId &&
                pTriangle.v[0] == indices1 &&
                pTriangle.v[1] == indices2 &&
                pTriangle.v[2] == indices3)
                return i;
        }
    }
    return -1;
}

RpMesh* CClientDFF::GetMeshFromPolygonId(RpGeometry* pGeometry, uint uiTriangleId)
{
    RpMesh* mesh = pGeometry->mesh->getMeshes();
    short meshCount = pGeometry->mesh->numMeshes;
    while (meshCount>0)
    {
        meshCount--;
        RpMesh* myMesh = &mesh[meshCount];
        for (uint i = 0; i < myMesh->numIndices / 3; i++)
        {
            unsigned short indices1 = myMesh->indices[(i * 3) + 0];
            unsigned short indices2 = myMesh->indices[(i * 3) + 1];
            unsigned short indices3 = myMesh->indices[(i * 3) + 2];

            for (uint i2 = 0; i2 < pGeometry->triangles_size; i2++)
            {
                RpTriangle pTriangle = pGeometry->triangles[i2];
                if (i2 == uiTriangleId &&
                    pTriangle.v[0] == indices1 &&
                    pTriangle.v[1] == indices2 &&
                    pTriangle.v[2] == indices3)
                    return myMesh;
            }
        }
    }
    return NULL;
}

int CClientDFF::GetMeshIdFromPolygonId(RpGeometry* pGeometry, uint uiTriangleId)
{
    RpMesh* mesh = pGeometry->mesh->getMeshes();
    short meshCount = pGeometry->mesh->numMeshes;
    while (meshCount>0)
    {
        meshCount--;
        RpMesh* myMesh = &mesh[meshCount];
        for (uint i = 0; i < myMesh->numIndices / 3; i++)
        {
            unsigned short indices1 = myMesh->indices[(i * 3) + 0];
            unsigned short indices2 = myMesh->indices[(i * 3) + 1];
            unsigned short indices3 = myMesh->indices[(i * 3) + 2];

            for (uint i2 = 0; i2 < pGeometry->triangles_size; i2++)
            {
                RpTriangle pTriangle = pGeometry->triangles[i2];
                if (i2 == uiTriangleId &&
                    pTriangle.v[0] == indices1 &&
                    pTriangle.v[1] == indices2 &&
                    pTriangle.v[2] == indices3)
                    return meshCount;
            }
        }
    }
    return -1;
}

bool CClientDFF::GeometryDestroyPolygon(RpGeometry* pGeometry, uint uiTriangleId)
{

    unsigned short meshId = CClientDFF::GetMeshIdFromPolygonId(pGeometry, uiTriangleId);
    if (meshId == -1)
    {
        return false;
    }
    RpMesh* mesh = pGeometry->mesh->getMeshes();
    RpMesh* myMesh = &mesh[meshId];
    unsigned short numIndices = myMesh->numIndices;
    if (numIndices <= 0)
    {
        return false;
    }
    pGeometry->triangles_size--;
    myMesh->numIndices -= 3;
    pGeometry->mesh->totalIndicesInMesh -= 3;
    unsigned short* polygons = myMesh->indices;
    unsigned short* newPolygons1 = reinterpret_cast<unsigned short*>(malloc(numIndices * 4));    // unsigned short - size=4
    RpTriangle* newPolygons2 = reinterpret_cast<RpTriangle*>(malloc(sizeof(RpTriangle) * pGeometry->triangles_size));

    uint id = GetPolygonIdInMesh(pGeometry, myMesh, uiTriangleId);
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

        if (i != uiTriangleId)
        {
            newPolygons2[next] = pGeometry->triangles[i];
            next++;
        }
    }
    free(myMesh->indices);  //crash
    free(pGeometry->triangles);
    myMesh->indices = newPolygons1;
    pGeometry->triangles = newPolygons2;
    return true;
}

const RpGeometry * CClientDFF::GeometryTriangleSetVertexIndices(const RpGeometry * geo, RpTriangle * tri, unsigned short v1, unsigned short v2, unsigned short v3)
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
RwTexture* CClientDFF::CreateTexture(int width, int height, int depth, int flags)
{
    return g_pGame->GetRenderWare()->RwCreateTexture(width, height,depth,flags);
}