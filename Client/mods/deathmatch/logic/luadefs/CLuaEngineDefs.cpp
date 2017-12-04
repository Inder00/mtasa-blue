/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/luadefs/CLuaEngineDefs.cpp
*  PURPOSE:     Lua definitions class
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include "StdInc.h"


void CLuaEngineDefs::LoadFunctions ( void )
{
    CLuaCFunctions::AddFunction ( "engineLoadTXD", EngineLoadTXD );
    CLuaCFunctions::AddFunction ( "engineLoadCOL", EngineLoadCOL );
    CLuaCFunctions::AddFunction ( "engineLoadDFF", EngineLoadDFF );
    CLuaCFunctions::AddFunction ( "engineImportTXD", EngineImportTXD );
    CLuaCFunctions::AddFunction ( "engineReplaceCOL", EngineReplaceCOL );
    CLuaCFunctions::AddFunction ( "engineRestoreCOL", EngineRestoreCOL );
    CLuaCFunctions::AddFunction("engineDFFGetInfo", EngineDFFGetInfo);
    CLuaCFunctions::AddFunction("engineDFFSetGeometry", EngineDFFSetGeometry);
    CLuaCFunctions::AddFunction("engineDFFSetSetCenter", EngineDFFSetCenter);
    CLuaCFunctions::AddFunction("engineDFFGetTriangles", EngineDFFGetTriangle);
    CLuaCFunctions::AddFunction("engineDFFGetTrianglesByMaterialId", EngineDFFGetTrianglesByMaterialId);
    CLuaCFunctions::AddFunction("engineDFFGetTriangleInfo", EngineDFFGetTriangleInfo);
    CLuaCFunctions::AddFunction("engineDFFGetVertices", EngineDFFGetVertices);
    CLuaCFunctions::AddFunction("engineDFFSetVertexPosition", EngineDFFSetVertexPosition);
    CLuaCFunctions::AddFunction("engineDFFGetMaterialInfo", EngineDFFGetMaterialInfo);
    CLuaCFunctions::AddFunction("engineDFFDestroyVertex", EngineDFFDestroyVertex);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonVertices", EngineDFFSetPolygonVertices);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonMaterial", EngineDFFSetPolygonMaterial);
    CLuaCFunctions::AddFunction("engineDFFSetMaterialColor", EngineDFFSetMaterialColor);
    CLuaCFunctions::AddFunction("engineDFFSetMaterialLighting", EngineDFFSetMaterialLighting);

    CLuaCFunctions::AddFunction("engineDFFToString", EngineDFFToString);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonsConnectedToVertex", EngineDFFGetPolygonsConnectedToVertex);
    CLuaCFunctions::AddFunction("engineDFFDestroyPolygon", EngineDFFDestroyPolygon);
    CLuaCFunctions::AddFunction("engineDFFGetMeshInfo", engineDFFGetMeshInfo);

    CLuaCFunctions::AddFunction("engineReplaceModel", EngineReplaceModel);
    CLuaCFunctions::AddFunction ( "engineRestoreModel", EngineRestoreModel );
    CLuaCFunctions::AddFunction ( "engineGetModelLODDistance", EngineGetModelLODDistance );
    CLuaCFunctions::AddFunction ( "engineSetModelLODDistance", EngineSetModelLODDistance );
    CLuaCFunctions::AddFunction ( "engineSetAsynchronousLoading", EngineSetAsynchronousLoading );
    CLuaCFunctions::AddFunction ( "engineApplyShaderToWorldTexture", EngineApplyShaderToWorldTexture );
    CLuaCFunctions::AddFunction ( "engineRemoveShaderFromWorldTexture", EngineRemoveShaderFromWorldTexture );
    CLuaCFunctions::AddFunction ( "engineGetModelNameFromID", EngineGetModelNameFromID );
    CLuaCFunctions::AddFunction ( "engineGetModelIDFromName", EngineGetModelIDFromName );
    CLuaCFunctions::AddFunction ( "engineGetModelTextureNames", EngineGetModelTextureNames );
    CLuaCFunctions::AddFunction ( "engineGetVisibleTextureNames", EngineGetVisibleTextureNames );

    //CLuaCFunctions::AddFunction ( "engineReplaceMatchingAtomics", EngineReplaceMatchingAtomics );
    //CLuaCFunctions::AddFunction ( "engineReplaceWheelAtomics", EngineReplaceWheelAtomics );
    //CLuaCFunctions::AddFunction ( "enginePositionAtomic", EnginePositionAtomic );
    //CLuaCFunctions::AddFunction ( "enginePositionSeats", EnginePositionSeats );
    //CLuaCFunctions::AddFunction ( "engineAddAllAtomics", EngineAddAllAtomics );
    //CLuaCFunctions::AddFunction ( "engineReplaceVehiclePart", EngineReplaceVehiclePart ); 
}

void CLuaEngineDefs::AddClass ( lua_State* luaVM )
{
    lua_newclass ( luaVM );

    lua_classfunction ( luaVM, "restoreCOL", "engineRestoreCOL" );
    lua_classfunction ( luaVM, "restoreModel", "engineRestoreModel" );
    lua_classfunction ( luaVM, "setAsynchronousLoading", "engineSetAsynchronousLoading" );
    lua_classfunction ( luaVM, "setModelLODDistance", "engineSetModelLODDistance" );

    lua_classfunction ( luaVM, "getVisibleTextureNames", "engineGetVisibleTextureNames" );
    lua_classfunction ( luaVM, "getModelLODDistance", "engineGetModelLODDistance" );
    lua_classfunction ( luaVM, "getModelTextureNames", "engineGetModelTextureNames" );
    lua_classfunction ( luaVM, "getModelIDFromName", "engineGetModelIDFromName" );
    lua_classfunction ( luaVM, "getModelNameFromID", "engineGetModelNameFromID" );

    //  lua_classvariable ( luaVM, "modelLODDistance", "engineSetModelLODDistance", "engineGetModelLODDistance" ); .modelLODDistance[model] = distance
    //  lua_classvariable ( luaVM, "modelNameFromID", NULL, "engineGetModelNameFromID" ); .modelNameFromID[id] = "name"
    //  lua_classvariable ( luaVM, "modelIDFromName", NULL, "engineGetModelIDFromName" ); .modelIDFromName["name"] = id
    //  lua_classvariable ( luaVM, "modelTextureNames", NULL, "engineGetModelTextureNames" ); .modelTextureNames[mode] = {names}

    lua_registerstaticclass ( luaVM, "Engine" );

    AddEngineColClass ( luaVM );
    AddEngineTxdClass ( luaVM );
    AddEngineDffClass ( luaVM );
}

void CLuaEngineDefs::AddEngineColClass ( lua_State* luaVM )
{
    lua_newclass ( luaVM );

    lua_classfunction ( luaVM, "create", "engineLoadCOL" );
    lua_classfunction ( luaVM, "replace", "engineReplaceCOL" );

    lua_registerclass ( luaVM, "EngineCOL", "Element" );
}


void CLuaEngineDefs::AddEngineTxdClass ( lua_State* luaVM )
{
    lua_newclass ( luaVM );

    lua_classfunction ( luaVM, "create", "engineLoadTXD" );

    lua_classfunction ( luaVM, "import", "engineImportTXD" );

    lua_registerclass ( luaVM, "EngineTXD", "Element" );
}


void CLuaEngineDefs::AddEngineDffClass ( lua_State* luaVM )
{
    lua_newclass ( luaVM );

    lua_classfunction ( luaVM, "create", "engineLoadDFF" );
    lua_classfunction ( luaVM, "replace", "engineReplaceModel" );

    lua_registerclass ( luaVM, "EngineDFF", "Element" );
}

int CLuaEngineDefs::EngineLoadCOL ( lua_State* luaVM )
{
    SString strFile = "";
    CScriptArgReader argStream ( luaVM );
    // Grab the COL filename or data
    argStream.ReadString ( strFile );

    if ( !argStream.HasErrors ( ) )
    {
        // Grab the lua main and the resource belonging to this script
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine ( luaVM );
        if ( pLuaMain )
        {
            // Get the resource we belong to
            CResource* pResource = pLuaMain->GetResource ();
            if ( pResource )
            {
                bool bIsRawData = CClientColModel::IsCOLData( strFile );
                SString strPath;
                // Is this a legal filepath?
                if ( bIsRawData || CResourceManager::ParseResourcePathInput( strFile, pResource, &strPath ) )
                {
                    // Grab the resource root entity
                    CClientEntity* pRoot = pResource->GetResourceCOLModelRoot ();

                    // Create the col model
                    CClientColModel* pCol = new CClientColModel ( m_pManager, INVALID_ELEMENT_ID );

                    // Attempt loading the file
                    if ( pCol->LoadCol ( bIsRawData ? strFile : strPath, bIsRawData ) )
                    {
                        // Success. Make it a child of the resource collision root
                        pCol->SetParent ( pRoot );

                        // Return the created col model
                        lua_pushelement ( luaVM, pCol );
                        return 1;
                    }
                    else
                    {
                        // Delete it again. We failed
                        delete pCol;
                        argStream.SetCustomError( bIsRawData ? "raw data" : strFile, "Error loading COL" );
                    }
                }
                else
                    argStream.SetCustomError( bIsRawData ? "raw data" : strFile, "Bad file path" );
            }
        }
    }
    if ( argStream.HasErrors ( ) )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed for some reason
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineLoadDFF ( lua_State* luaVM )
{
    SString strFile = "";
    SString strModelName = NULL;

    CScriptArgReader argStream ( luaVM );
    // Grab the DFF filename or data (model ID ignored after 1.3.1)
    argStream.ReadString ( strFile );
    argStream.ReadString ( strModelName, NULL );
    if ( !argStream.HasErrors ( ) )
    {
        // Grab our virtual machine and grab our resource from that.
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine ( luaVM );
        if ( pLuaMain )
        {
            // Get this resource
            CResource* pResource = pLuaMain->GetResource ();
            if ( pResource )
            {
                bool bIsRawData = CClientDFF::IsDFFData( strFile );
                SString strPath;
                // Is this a legal filepath?
                if ( bIsRawData || CResourceManager::ParseResourcePathInput( strFile, pResource, &strPath ) )
                {
                    // Grab the resource root entity
                    CClientEntity* pRoot = pResource->GetResourceDFFRoot ();

                    // Create a DFF element
                    CClientDFF* pDFF = new CClientDFF ( m_pManager, INVALID_ELEMENT_ID );

                    // Try to load the DFF file
                    if ( pDFF->LoadDFF ( bIsRawData ? strFile : strPath, bIsRawData ) )
                    {
                        // Success loading the file. Set parent to DFF root
                        pDFF->SetParent ( pRoot );

                        if (strModelName != NULL)
                        {
                            ushort usModelID = CModelNames::ResolveModelID(strModelName);
                            if (usModelID != INVALID_MODEL_ID)
                            {
                                pDFF->uimodel = usModelID;
                            }
                        }
                        // Return the DFF
                        lua_pushelement ( luaVM, pDFF );
                        return 1;
                    }
                    else
                    {
                        // Delete it again
                        delete pDFF;
                        argStream.SetCustomError( bIsRawData ? "raw data" : strFile, "Error loading DFF" );
                    }
                }
                else
                    argStream.SetCustomError( bIsRawData ? "raw data" : strFile, "Bad file path" );
            }
        }
    }
    if ( argStream.HasErrors ( ) )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineLoadTXD ( lua_State* luaVM )
{
    SString strFile = "";
    bool bFilteringEnabled = true;
    CScriptArgReader argStream ( luaVM );
    // Grab the TXD filename or data
    argStream.ReadString ( strFile );
    if ( argStream.NextIsBool() )   // Some scripts have a number here (in error)
        argStream.ReadBool ( bFilteringEnabled, true );

    if ( !argStream.HasErrors ( ) )
    {
        // Grab our virtual machine and grab our resource from that.
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine ( luaVM );
        if ( pLuaMain )
        {
            // Grab this resource
            CResource* pResource = pLuaMain->GetResource ();
            if ( pResource )
            {
                bool bIsRawData = CClientTXD::IsTXDData( strFile );
                SString strPath;
                // Is this a legal filepath?
                if ( bIsRawData || CResourceManager::ParseResourcePathInput( strFile, pResource, &strPath ) )
                {
                    // Grab the resource root entity
                    CClientEntity* pRoot = pResource->GetResourceTXDRoot ();

                    // Create a TXD element
                    CClientTXD* pTXD = new CClientTXD ( m_pManager, INVALID_ELEMENT_ID );

                    // Try to load the TXD file
                    if ( pTXD->LoadTXD ( bIsRawData ? strFile : strPath, bFilteringEnabled, bIsRawData ) )
                    {
                        // Success loading the file. Set parent to TXD root
                        pTXD->SetParent ( pRoot );

                        // Return the TXD
                        lua_pushelement ( luaVM, pTXD );
                        return 1;
                    }
                    else
                    {
                        // Delete it again
                        delete pTXD;
                        argStream.SetCustomError( bIsRawData ? "raw data" : strFile, "Error loading TXD" );
                    }
                }
                else
                    argStream.SetCustomError( bIsRawData ? "raw data" : strFile, "Bad file path" );
            }
        }
    }
    if ( argStream.HasErrors() )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineReplaceCOL ( lua_State* luaVM )
{
    CClientColModel* pCol = NULL;
    unsigned short usModel = 0;
    CScriptArgReader argStream ( luaVM );
    // Grab the COL and model ID
    argStream.ReadUserData ( pCol );
    argStream.ReadNumber ( usModel );

    if ( !argStream.HasErrors ( ) )
    {
        // Valid client DFF and model?
        if ( CClientColModelManager::IsReplacableModel ( usModel ) )
        {
            // Replace the colmodel
            if ( pCol->Replace ( usModel ) )
            {
                lua_pushboolean ( luaVM, true );
                return 1;
            }
        }
        else
            m_pScriptDebugging->LogBadPointer ( luaVM, "number", 2 );
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // Failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineRestoreCOL ( lua_State* luaVM )
{
    SString strModelName = "";
    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strModelName );

    if ( !argStream.HasErrors ( ) )
    {
        unsigned short usModelID = CModelNames::ResolveModelID ( strModelName );

        if ( m_pColModelManager->RestoreModel ( usModelID ) )
        {
            // Success
            lua_pushboolean ( luaVM, true );
            return 1;
        }  
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // Failed.
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineImportTXD ( lua_State* luaVM )
{
    CClientTXD* pTXD = NULL;
    SString strModelName;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadUserData ( pTXD );
    argStream.ReadString ( strModelName );

    if ( !argStream.HasErrors ( ) )
    {
        // Valid importable model?
        ushort usModelID = CModelNames::ResolveModelID ( strModelName );
        if ( usModelID == INVALID_MODEL_ID )
            usModelID = CModelNames::ResolveClothesTexID ( strModelName );
        if ( CClientTXD::IsImportableModel ( usModelID ) )
        {
            // Try to import
            if ( pTXD->Import ( usModelID ) )
            {
                // Success
                lua_pushboolean ( luaVM, true );
                return 1;
            }
        }
        else
            m_pScriptDebugging->LogBadPointer ( luaVM, "number", 2 );
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // Failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineReplaceModel(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString strModelName;
    bool bAlphaTransparency;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(strModelName);
    argStream.ReadBool(bAlphaTransparency, false);

    if (!argStream.HasErrors())
    {
        ushort usModelID = CModelNames::ResolveModelID(strModelName);
        if (usModelID != INVALID_MODEL_ID)
        {
            if (pDFF->ReplaceModel(usModelID, bAlphaTransparency))
            {
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d replace failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFGetInfo(lua_State* luaVM)
{
    CClientDFF* pDFF;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);

    if (!argStream.HasErrors())
    {
        ushort usModelID=pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);

                lua_pushstring(luaVM, "verticesCount");
                lua_pushnumber(luaVM, pGeometry->vertices_size);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "trianglesCount");
                lua_pushnumber(luaVM, pGeometry->triangles_size);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "materialsCount");
                lua_pushnumber(luaVM, pGeometry->materials.entries);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "radius");
                lua_pushnumber(luaVM, pAtomic->bsphereLocal.radius);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "center");
                CVector center;
                center.fX = pAtomic->bsphereLocal.position.x;
                center.fY = pAtomic->bsphereLocal.position.y;
                center.fZ = pAtomic->bsphereLocal.position.z;
                lua_pushvector(luaVM, center);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "atomics");
                lua_pushnumber(luaVM, CClientDFF::ClumpGetNumAtomics(pClump));
                lua_settable(luaVM, -3);

                /*lua_pushstring(luaVM, "meshesCount");
                lua_pushnumber(luaVM, pGeometry->mesh->numMeshes);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "totalIndicesInMesh");
                lua_pushnumber(luaVM, pGeometry->mesh->totalIndicesInMesh);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "meshFlags");
                lua_pushnumber(luaVM, pGeometry->mesh->flags);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "serialNum");
                lua_pushnumber(luaVM, pGeometry->mesh->serialNum);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "firstMeshOffset");
                lua_pushnumber(luaVM, pGeometry->mesh->firstMeshOffset);
                lua_settable(luaVM, -3);*/
                /*lua_pushstring(luaVM, "a1");
                RpMesh* m = pGeometry->mesh->getMeshes();
                lua_pushnumber(luaVM, m->numIndices);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a10");
                lua_pushnumber(luaVM, m->indices[0]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a11");
                lua_pushnumber(luaVM, m->indices[1]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a12");
                lua_pushnumber(luaVM, m->indices[2]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a13");
                lua_pushnumber(luaVM, m->indices[3]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a14");
                lua_pushnumber(luaVM, m->indices[4]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a15");
                lua_pushnumber(luaVM, m->indices[5]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a16");
                lua_pushnumber(luaVM, m->indices[6]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a17");
                lua_pushnumber(luaVM, m->indices[7]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a18");
                lua_pushnumber(luaVM, m->indices[8]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a19");
                lua_pushnumber(luaVM, m->indices[9]);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a20");
                lua_pushnumber(luaVM, m->indices[10]);
                m->indices[10] = 10;
                m->indices[11] = 11;
                m->indices[12] = 12;
                m->material->->color.r = 123;
                m->material->color.g = 123;
                m->material->color.b = 123;

                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "a21");
                lua_pushnumber(luaVM, m->indices[11]);
                lua_settable(luaVM, -3);*/


                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFSetMaterialColor(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiMaterialId = NULL;
    uint uiMaterialR = NULL;
    uint uiMaterialG = NULL;
    uint uiMaterialB = NULL;
    uint uiMaterialA = NULL;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiMaterialId);
    argStream.ReadNumber(uiMaterialR);
    argStream.ReadNumber(uiMaterialG);
    argStream.ReadNumber(uiMaterialB);
    argStream.ReadNumber(uiMaterialA, NULL, true);


    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                uiMaterialId--;
                if (uiMaterialId > pGeometry->mesh->numMeshes-1) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh* m = pGeometry->mesh->getMeshes() + uiMaterialId; // example textures 0-5 in mta are 1-6
                m->material->color.r = uiMaterialR;
                m->material->color.g = uiMaterialG;
                m->material->color.b = uiMaterialB;
                if (uiMaterialA!=NULL) {
                    m->material->color.a = uiMaterialA;
                }
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFSetMaterialLighting(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiMaterialId = NULL;
    float ambient = NULL;
    float diffuse = NULL;
    float specular = NULL;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiMaterialId);
    argStream.ReadNumber(ambient);
    argStream.ReadNumber(diffuse);
    argStream.ReadNumber(specular);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                uiMaterialId--;
                if (uiMaterialId > pGeometry->mesh->numMeshes - 1) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh* m = pGeometry->mesh->getMeshes() + uiMaterialId; // example textures 0-5 in mta are 1-6
                m->material->lighting.ambient = ambient;
                m->material->lighting.diffuse = diffuse;
                m->material->lighting.specular = specular;
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}
int CLuaEngineDefs::EngineDFFSetGeometry(lua_State* luaVM)
{

    CClientDFF* pDFF;
    ushort uiGeometry;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiGeometry);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                pDFF->uiGeometry = uiGeometry;
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}
int CLuaEngineDefs::EngineDFFSetCenter(lua_State* luaVM)
{
    CClientDFF* pDFF;
    CVector vNewCenter;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadVector3D(vNewCenter);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                //RpGeometry* pGeometry = pAtomic->geometry;
                pAtomic->bsphereWorld.position.x = vNewCenter.fX;
                pAtomic->bsphereWorld.position.y = vNewCenter.fY;
                pAtomic->bsphereWorld.position.z = vNewCenter.fZ;

                pAtomic->bsphereLocal.position.x = vNewCenter.fX;
                pAtomic->bsphereLocal.position.y = vNewCenter.fY;
                pAtomic->bsphereLocal.position.z = vNewCenter.fZ;
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFGetVertices(lua_State* luaVM)
{
    CClientDFF* pDFF;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);
                lua_newtable(luaVM);
                for (uint i = 0; i < pGeometry->vertices_size; i++)
                {
                    RwV3d* vVert = pGeometry->morphTarget->verts + i;
                    RwV3d* pTriangle = pGeometry->morphTarget->normals + i;
                    CVector vPos;
                    vPos.fX = vVert->x;
                    vPos.fY = vVert->y;
                    vPos.fZ = vVert->z;
                    CVector vNormal;
                    vNormal.fX = pTriangle->x;
                    vNormal.fY = pTriangle->y;
                    vNormal.fZ = pTriangle->z;
                    lua_pushnumber(luaVM, i + 1); // start from 1 not 0
                    lua_newtable(luaVM);
                        lua_pushstring(luaVM, "position");
                        lua_pushvector(luaVM, vPos);
                        lua_settable(luaVM, -3);
                        lua_pushstring(luaVM, "normal");
                        lua_pushvector(luaVM, vNormal);
                        lua_settable(luaVM, -3);
                    lua_settable(luaVM, -3);
                }
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::engineDFFGetMeshInfo(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uMeshId = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uMeshId);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uMeshId != NULL && uMeshId <= pGeometry->mesh->numMeshes)
                {
                    /*pGeometry->mesh
                    RpTriangle* pTriangle = pGeometry->triangles + uTriangleId;
                    lua_newtable(luaVM);
                    lua_pushstring(luaVM, "vertices");
                    lua_newtable(luaVM);
                    lua_pushnumber(luaVM, 1);
                    lua_pushnumber(luaVM, pTriangle->v[0]);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 2);
                    lua_pushnumber(luaVM, pTriangle->v[1]);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 3);
                    lua_pushnumber(luaVM, pTriangle->v[2]);
                    lua_settable(luaVM, -3);
                    lua_settable(luaVM, -3);
                    lua_pushstring(luaVM, "materialId");
                    lua_pushnumber(luaVM, pTriangle->matId);

                    lua_settable(luaVM, -3);*/

                    return 1;
                }
                else
                    argStream.SetCustomError(SString("Triangle ID %s invalid", "asD"));
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFGetTriangleInfo(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uTriangleId = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uTriangleId);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uTriangleId != NULL && uTriangleId <= pGeometry->triangles_size)
                {
                    RpTriangle* pTriangle = pGeometry->triangles + uTriangleId;
                    lua_newtable(luaVM);
                    lua_pushstring(luaVM, "vertices");
                    lua_newtable(luaVM);
                        lua_pushnumber(luaVM, 1);
                        lua_pushnumber(luaVM, pTriangle->v[0]);
                        lua_settable(luaVM, -3);
                        lua_pushnumber(luaVM, 2);
                        lua_pushnumber(luaVM, pTriangle->v[1]);
                        lua_settable(luaVM, -3);
                        lua_pushnumber(luaVM, 3);
                        lua_pushnumber(luaVM, pTriangle->v[2]);
                        lua_settable(luaVM, -3);
                    lua_settable(luaVM, -3);
                    lua_pushstring(luaVM, "materialId");
                    lua_pushnumber(luaVM, pTriangle->matId);

                    lua_settable(luaVM, -3);

                    return 1;
                }
                else
                    argStream.SetCustomError(SString("Triangle ID %ui invalid", uTriangleId));
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFGetTriangle(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygonId = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiPolygonId);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);
                for (uint i = 0; i < pGeometry->triangles_size; i++)
                {
                    RpTriangle* pTriangle = &pGeometry->triangles[i];
                    lua_pushnumber(luaVM, i+1); // start from 1 not 0
                    lua_newtable(luaVM);
                        lua_pushnumber(luaVM, 1);
                        lua_pushnumber(luaVM, pTriangle->v[0]);
                        lua_settable(luaVM, -3);
                        lua_pushnumber(luaVM, 2);
                        lua_pushnumber(luaVM, pTriangle->v[1]);
                        lua_settable(luaVM, -3);
                        lua_pushnumber(luaVM, 3);
                        lua_pushnumber(luaVM, pTriangle->v[2]);
                        lua_settable(luaVM, -3);
                    lua_settable(luaVM, -3);
                }
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
    m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFGetTrianglesByMaterialId(lua_State* luaVM)
{
    CClientDFF* pDFF;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                RpMesh* meshes = pGeometry->mesh->getMeshes();
                lua_newtable(luaVM);
                for (uint i = 0; i < meshes->numIndices; i++)
                {
                    RpMesh mesh = meshes[i];
                    lua_pushnumber(luaVM, i);
                    lua_pushnumber(luaVM, mesh.numIndices);
                    /*mesh.numIndices
                    RpTriangle* pTriangle = &pGeometry->triangles[i];
                    lua_pushnumber(luaVM, i + 1); // start from 1 not 0
                    lua_newtable(luaVM);
                    lua_pushnumber(luaVM, 1);
                    lua_pushnumber(luaVM, pTriangle->v[0]);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 2);
                    lua_pushnumber(luaVM, pTriangle->v[1]);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 3);
                    lua_pushnumber(luaVM, pTriangle->v[2]);
                    lua_settable(luaVM, -3);*/
                    lua_settable(luaVM, -3);
                }
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFSetVertexPosition(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiVertex;
    CVector pos;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiVertex);
    argStream.ReadVector3D(pos);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiVertex > pGeometry->vertices_size) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwV3d* vVert = pGeometry->morphTarget->verts + uiVertex;
                vVert->x = pos.fX;
                vVert->y = pos.fY;
                vVert->z = pos.fZ;
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Expected valid model ID or name at argument 2");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFGetMaterialInfo(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiMaterialId=NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiMaterialId);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                RpMaterials pMaterials = pGeometry->materials;
                if (uiMaterialId != NULL && uiMaterialId <= pMaterials.entries)
                {
                    RpMaterial* pMaterial = pMaterials.materials[uiMaterialId];
                    if (pMaterial==NULL || pMaterial==nullptr) {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    lua_newtable(luaVM);
                        lua_pushstring(luaVM, "color");
                        if (&pMaterial->color != NULL && &pMaterial->color.a != NULL)
                        {
                            RwColor rColor = pMaterial->color;
                            lua_newtable(luaVM);
                            lua_pushnumber(luaVM, 1);
                            lua_pushnumber(luaVM, rColor.r);
                            lua_settable(luaVM, -3);
                            lua_pushnumber(luaVM, 2);
                            lua_pushnumber(luaVM, rColor.g);
                            lua_settable(luaVM, -3);
                            lua_pushnumber(luaVM, 3);
                            lua_pushnumber(luaVM, rColor.b);
                            lua_settable(luaVM, -3);
                            lua_pushnumber(luaVM, 4);
                            lua_pushnumber(luaVM, rColor.a);
                            lua_settable(luaVM, -3);
                        }
                        else {
                            lua_pushboolean(luaVM, false);
                        }
                        lua_settable(luaVM, -3);
                        /*
                        lua_pushstring(luaVM, "texture");
                        if (pMaterial->texture!=nullptr)
                        {
                            lua_newtable(luaVM);
                                lua_pushstring(luaVM, "name");  // pMaterial->texture->raster->u
                                lua_pushstring(luaVM, pMaterial->texture->name);
                                lua_settable(luaVM, -3);
                        }
                        else
                        {
                            lua_pushboolean(luaVM, false);
                        }

                        lua_settable(luaVM, -3);


                        lua_pushstring(luaVM, "lighting");
                        if (&pMaterial->lighting)
                        {
                            lua_newtable(luaVM);
                            lua_pushstring(luaVM, "ambient");
                            lua_pushnumber(luaVM, pMaterial->lighting.ambient);
                            lua_settable(luaVM, -3);
                            lua_pushstring(luaVM, "diffuse");
                            lua_pushnumber(luaVM, pMaterial->lighting.diffuse);
                            lua_settable(luaVM, -3);
                            lua_pushstring(luaVM, "specular");
                            lua_pushnumber(luaVM, pMaterial->lighting.specular);
                            lua_settable(luaVM, -3);
                        }
                        else
                        {
                            lua_pushboolean(luaVM, false);
                        }*/
                    lua_settable(luaVM, -3);
                    return 1;
                }
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFSetPolygonVertices(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygon = NULL;
    uint uiVertex1 = NULL;
    uint uiVertex2 = NULL;
    uint uiVertex3 = NULL;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiPolygon);
    argStream.ReadNumber(uiVertex1);
    argStream.ReadNumber(uiVertex2);
    argStream.ReadNumber(uiVertex3);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiVertex1 > pGeometry->vertices_size || uiVertex2 > pGeometry->vertices_size || uiVertex3 > pGeometry->vertices_size)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (uiPolygon > pGeometry->triangles_size)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpTriangle* pTriangle = &pGeometry->triangles[uiPolygon];
                pDFF->AtomicSetGeometry(pAtomic, pGeometry, 118);
                pGeometry = (RpGeometry*)pDFF->GeometryTriangleSetVertexIndices(pGeometry, pTriangle, uiVertex1, uiVertex2, uiVertex3);
                //pDFF->ReplaceModel(usModelID, false);
                pTriangle->v[0] = uiVertex1;
                pTriangle->v[1] = uiVertex2;
                pTriangle->v[2] = uiVertex3;
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFSetPolygonMaterial(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygon = NULL;
    uint uiMaterialId = NULL;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiPolygon);
    argStream.ReadNumber(uiMaterialId);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry + pDFF->uiGeometry;
                if (uiPolygon > pGeometry->triangles_size)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMaterials pMaterials = pGeometry->materials;
                if (uiMaterialId != NULL && uiMaterialId <= pMaterials.entries)
                {
                    RpMaterial* pMaterial = pMaterials.materials[uiMaterialId];
                    if (pMaterial == NULL || pMaterial == nullptr || sizeof(pMaterial)!=4) {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    RpTriangle* pTriangle = pGeometry->triangles + uiPolygon;
                    pGeometry = (RpGeometry*)pDFF->GeometryTriangleSetMaterialId(pGeometry, pTriangle, pMaterial);
                    lua_pushboolean(luaVM, true);
                    return 1;
                }
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFDestroyPolygon(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygon = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiPolygon);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiPolygon > pGeometry->vertices_size) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                int ii = 0;
                uiPolygon--;
                for (int i = uiPolygon; i < pGeometry->triangles_size; i++)
                {
                    pGeometry->triangles[i] = std::move(pGeometry->triangles[i + 1]);
                }
                pGeometry->triangles[pGeometry->triangles_size].v[1]=-1;
                delete[] &pGeometry->triangles[pGeometry->triangles_size];
                pGeometry->triangles_size--;
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFDestroyVertex(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiVertex = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiVertex);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiVertex > pGeometry->vertices_size) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                int ii = 0;
                for (int i = 0; i < pGeometry->vertices_size; i++)
                {
                    pGeometry->morphTarget->verts[i] = std::move(pGeometry->morphTarget->verts[i + 1]);
                }
                RwV3d* vert = &pGeometry->morphTarget->verts[pGeometry->vertices_size-1];
                vert = NULL;
                pGeometry->vertices_size--;
                /*uint removedTriangles = 0;
                for (uint i = 0; i < pGeometry->triangles_size; i++)
                {
                    RpTriangle* pTriangle = &pGeometry->triangles[i];
                    if (pTriangle->v[0] == uiVertex ||
                        pTriangle->v[1] == uiVertex ||
                        pTriangle->v[2] == uiVertex)
                    {
                        for (uint i2 = i; i2 < pGeometry->triangles_size; i2++)
                        {
                            pGeometry->triangles[i] = std::move(pGeometry->triangles[i + 1]);
                        }
                        removedTriangles++;
                    }
                }
                pGeometry->triangles_size -= removedTriangles;*/
                lua_pushboolean(luaVM, true);
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineDFFGetPolygonsConnectedToVertex(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiVertex);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = (RpAtomic*)((pClump->atomics.root.next) - 0x8);
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);
                uiVertex--;
                uint ii = 0;
                for (uint i = 0; i < pGeometry->triangles_size; i++)
                {
                    RpTriangle* pTriangle = &pGeometry->triangles[i];
                    if (pTriangle->v[0] == uiVertex ||
                        pTriangle->v[1] == uiVertex ||
                        pTriangle->v[2] == uiVertex)
                    {
                        lua_pushnumber(luaVM, ++ii);
                        lua_pushnumber(luaVM, i+1);
                        lua_settable(luaVM, -3);
                    }
                }
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineDFFToString(lua_State* luaVM)
{
    CClientDFF* pDFF;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                lua_pushstring(luaVM, SString("%#v", pClump).c_str());
                return 1;
            }
            else
                argStream.SetCustomError(SString("Model ID %d failed", usModelID));
        }
        else
            argStream.SetCustomError("Dff model ID not set. Check 2 argument in engineLoadDFF");
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineRestoreModel ( lua_State* luaVM )
{
    // Grab the model ID
    unsigned short usModelID = CModelNames::ResolveModelID ( lua_tostring ( luaVM, 1 ) );

    // Valid client DFF and model?
    if ( CClientDFFManager::IsReplacableModel ( usModelID )  )
    {
        // Restore the model
        if ( m_pDFFManager->RestoreModel ( usModelID ) )
        {
            // Success
            lua_pushboolean ( luaVM, true );
            return true;
        }
    }
    else
    {
        m_pScriptDebugging->LogBadType ( luaVM );
    }

    // Failure
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineGetModelLODDistance ( lua_State* luaVM )
{
// float engineGetModelLODDistance ( int/string modelID )
    SString strModelId;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strModelId );

    if ( !argStream.HasErrors () )
    {
        ushort usModelID = CModelNames::ResolveModelID ( strModelId );
        CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModelID );
        if ( pModelInfo )
        {
            float fDistance = pModelInfo->GetLODDistance ();
            lua_pushnumber ( luaVM, fDistance );
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    // Failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineSetModelLODDistance ( lua_State* luaVM )
{
    SString strModel = "";
    float fDistance = 0.0;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strModel );
    argStream.ReadNumber ( fDistance );

    if ( !argStream.HasErrors () )
    {
        unsigned short usModelID = CModelNames::ResolveModelID ( strModel );
        CModelInfo* pModelInfo = g_pGame->GetModelInfo ( usModelID );
        if ( pModelInfo && fDistance > 0.0f )
        {
            pModelInfo->SetLODDistance ( fDistance );
            lua_pushboolean ( luaVM, true );
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineSetAsynchronousLoading ( lua_State* luaVM )
{
    bool bEnabled = false;
    bool bForced = false;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadBool ( bEnabled );
    argStream.ReadBool ( bForced, false );

    if ( !argStream.HasErrors () )
    {
        g_pGame->SetAsyncLoadingFromScript ( bEnabled, bForced );
        lua_pushboolean ( luaVM, true );
        return 1;
    }

    lua_pushboolean ( luaVM, false );
    return 1;
}


// TODO: int CLuaEngineDefs::EngineReplaceMatchingAtomics ( lua_State* luaVM )
int CLuaEngineDefs::EngineReplaceMatchingAtomics ( lua_State* luaVM )
{
    /*
    RpClump * pClump = ( lua_istype ( 1, LUA_TLIGHTUSERDATA ) ? reinterpret_cast < RpClump* > ( lua_touserdata ( luaVM, 1 ) ) : NULL );
    CClientEntity* pEntity = ( lua_istype ( 2, LUA_TLIGHTUSERDATA ) ? reinterpret_cast < CClientEntity* > ( lua_touserdata ( luaVM, 2 ) ) : NULL );
    RpAtomicContainer Atomics[MAX_ATOMICS_PER_CLUMP];
    RpClump * pEntityClump = NULL;
    unsigned int uiAtomics = 0;

    if ( pEntity ) {
    if ( IS_VEHICLE ( pEntity ) )
    pEntityClump = static_cast < CClientVehicle* > ( pEntity ) -> GetGameVehicle () -> GetRpClump ();
    else if ( IS_OBJECT ( pEntity ) )
    pEntityClump = static_cast < CClientObject* > ( pEntity ) -> GetGameObject () -> GetRpClump ();
    else {
    m_pScriptDebugging->LogWarning ( luaVM, "engineReplaceMatchingAtomics only supports vehicles and objects." );
    m_pScriptDebugging->LogBadType ( luaVM );
    }
    }

    if ( pEntityClump && pClump ) {
    uiAtomics = m_pRenderWare->LoadAtomics ( pClump, &Atomics[0] );
    m_pRenderWare->ReplaceAllAtomicsInClump ( pEntityClump, &Atomics[0], uiAtomics );

    lua_pushboolean ( luaVM, true );
    } else {
    m_pScriptDebugging->LogBadType ( luaVM );
    lua_pushboolean ( luaVM, false );
    }
    */

    lua_pushboolean ( luaVM, false );
    return 1;
}


// TODO: int CLuaEngineDefs::EngineReplaceWheelAtomics ( lua_State* luaVM )
int CLuaEngineDefs::EngineReplaceWheelAtomics ( lua_State* luaVM )
{
    /*
    RpClump * pClump = ( lua_istype ( 1, LUA_TLIGHTUSERDATA ) ? reinterpret_cast < RpClump* > ( lua_touserdata ( luaVM, 1 ) ) : NULL );
    CClientEntity* pEntity = ( lua_istype ( 2, LUA_TLIGHTUSERDATA ) ? reinterpret_cast < CClientEntity* > ( lua_touserdata ( luaVM, 2 ) ) : NULL );
    const char * szWheel = ( lua_istype ( 3, LUA_TSTRING ) ? lua_tostring ( luaVM, 3 ) : NULL );

    RpAtomicContainer Atomics[MAX_ATOMICS_PER_CLUMP];
    RpClump * pEntityClump = NULL;
    unsigned int uiAtomics = 0;

    if ( pEntity ) {
    if ( IS_VEHICLE ( pEntity ) )
    pEntityClump = static_cast < CClientVehicle* > ( pEntity ) -> GetGameVehicle () -> GetRpClump ();
    else if ( IS_OBJECT ( pEntity ) )
    pEntityClump = static_cast < CClientObject* > ( pEntity ) -> GetGameObject () -> GetRpClump ();
    else {
    m_pScriptDebugging->LogWarning ( luaVM, "engineReplaceWheelAtomics only supports vehicles and objects." );
    }
    }

    if ( pClump ) {
    uiAtomics = m_pRenderWare->LoadAtomics ( pClump, &Atomics[0] );
    m_pScriptDebugging->LogWarning ( luaVM, "engineReplaceWheelAtomics DFF argument was not valid." );
    }

    if ( pEntityClump && uiAtomics > 0 && szWheel ) {   
    m_pRenderWare->ReplaceWheels ( pEntityClump, &Atomics[0], uiAtomics, szWheel );

    lua_pushboolean ( luaVM, true );
    } else {
    m_pScriptDebugging->LogBadType ( luaVM );
    lua_pushboolean ( luaVM, false );
    }
    */

    lua_pushboolean ( luaVM, false );
    return 1;
}


// TODO: int CLuaEngineDefs::EnginePositionAtomic ( lua_State* luaVM )
int CLuaEngineDefs::EnginePositionAtomic ( lua_State* luaVM )
{
    lua_pushboolean ( luaVM, false );
    return 1;
}


// TODO: int CLuaEngineDefs::EnginePositionSeats ( lua_State* luaVM )
int CLuaEngineDefs::EnginePositionSeats ( lua_State* luaVM )
{
    lua_pushboolean ( luaVM, false );
    return 1;
}


// TODO: int CLuaEngineDefs::EngineAddAllAtomics ( lua_State* luaVM )
int CLuaEngineDefs::EngineAddAllAtomics ( lua_State* luaVM )
{
    lua_pushboolean ( luaVM, false );
    return 1;
}


// TODO: int CLuaEngineDefs::EngineReplaceVehiclePart ( lua_State* luaVM )
int CLuaEngineDefs::EngineReplaceVehiclePart ( lua_State* luaVM )
{
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineApplyShaderToWorldTexture ( lua_State* luaVM )
{
//  bool engineApplyShaderToWorldTexture ( element shader, string textureName, [ element targetElement, bool appendLayers ] )
    CClientShader* pShader; SString strTextureNameMatch; CClientEntity* pElement; bool bAppendLayers;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadUserData ( pShader );
    argStream.ReadString ( strTextureNameMatch );
    argStream.ReadUserData ( pElement, NULL );
    argStream.ReadBool ( bAppendLayers, true );

    if ( !argStream.HasErrors () )
    {
        bool bResult = g_pCore->GetGraphics ()->GetRenderItemManager ()->ApplyShaderItemToWorldTexture ( pShader->GetShaderItem (), strTextureNameMatch, pElement, bAppendLayers );
        lua_pushboolean ( luaVM, bResult );
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineRemoveShaderFromWorldTexture ( lua_State* luaVM )
{
//  bool engineRemoveShaderFromWorldTexture ( element shader, string textureName, [ element targetElement ] )
    CClientShader* pShader; SString strTextureNameMatch; CClientEntity* pElement;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadUserData ( pShader );
    argStream.ReadString ( strTextureNameMatch );
    argStream.ReadUserData ( pElement, NULL );

    if ( !argStream.HasErrors () )
    {
        bool bResult = g_pCore->GetGraphics ()->GetRenderItemManager ()->RemoveShaderItemFromWorldTexture ( pShader->GetShaderItem (), strTextureNameMatch, pElement );
        lua_pushboolean ( luaVM, bResult );
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineGetModelNameFromID ( lua_State* luaVM )
{
//  string engineGetModelNameFromID ( int modelID )
    int iModelID;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadNumber ( iModelID );

    if ( !argStream.HasErrors () )
    {
        SString strModelName = CModelNames::GetModelName ( iModelID );
        if ( !strModelName.empty () )
        {
            lua_pushstring ( luaVM, strModelName );
            return 1;
        }
        argStream.SetCustomError( "Expected valid model ID at argument 1" );
    }
    if ( argStream.HasErrors () )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineGetModelIDFromName ( lua_State* luaVM )
{
    //  int engineGetModelIDFromName ( string modelName )
    SString strModelName;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strModelName );

    if ( !argStream.HasErrors () )
    {
        int iModelID = CModelNames::GetModelID ( strModelName );
        if ( iModelID != INVALID_MODEL_ID )
        {
            lua_pushnumber ( luaVM, iModelID );
            return 1;
        }
        argStream.SetCustomError( "Expected valid model name at argument 1" );
    }
    if ( argStream.HasErrors () )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}

// Only works if the model is loaded. EngineGetVisibleTextureNames should be used instead
int CLuaEngineDefs::EngineGetModelTextureNames ( lua_State* luaVM )
{
//  table engineGetModelTextureNames ( string modelName )
    SString strModelName;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strModelName, "" );

    if ( !argStream.HasErrors () )
    {
        ushort usModelID = CModelNames::ResolveModelID ( strModelName );
        if ( usModelID != INVALID_MODEL_ID )
        {
            std::vector < SString > nameList;
            g_pGame->GetRenderWare ()->GetModelTextureNames ( nameList, usModelID );

            lua_newtable ( luaVM );
            for ( uint i = 0 ; i < nameList.size () ; i++ )
            {                
                lua_pushnumber ( luaVM, i + 1 );
                lua_pushstring ( luaVM, nameList [ i ] );
                lua_settable ( luaVM, -3 );
            }
            return 1;
        }
        argStream.SetCustomError( "Expected valid model ID or name at argument 1" );
    }
    if ( argStream.HasErrors () )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaEngineDefs::EngineGetVisibleTextureNames ( lua_State* luaVM )
{
//  table engineGetVisibleTextureNames ( string wildcardMatch = "*" [, string modelName )
    SString strTextureNameMatch; SString strModelName;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strTextureNameMatch, "*" );
    argStream.ReadString ( strModelName, "" );

    if ( !argStream.HasErrors () )
    {
        ushort usModelID = CModelNames::ResolveModelID ( strModelName );
        if ( usModelID != INVALID_MODEL_ID || strModelName == "" )
        {
            std::vector < SString > nameList;
            g_pCore->GetGraphics ()->GetRenderItemManager ()->GetVisibleTextureNames ( nameList, strTextureNameMatch, usModelID );

            lua_newtable ( luaVM );
            for ( uint i = 0 ; i < nameList.size () ; i++ )
            {                
                lua_pushnumber ( luaVM, i + 1 );
                lua_pushstring ( luaVM, nameList [ i ] );
                lua_settable ( luaVM, -3 );
            }
            return 1;
        }
        argStream.SetCustomError( "Expected valid model ID or name at argument 1" );
    }
    if ( argStream.HasErrors () )
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // We failed
    lua_pushboolean ( luaVM, false );
    return 1;
}
