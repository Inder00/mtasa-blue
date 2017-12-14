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
    CLuaCFunctions::AddFunction("engineDFFGetPolygons", EngineDFFGetPolygons);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonInfo", EngineDFFGetPolygonInfo);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonVertices", EngineDFFGetPolygonConnectedToVertex);
    CLuaCFunctions::AddFunction("engineDFFGetVertices", EngineDFFGetVertices);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonPosition", EngineDFFGetPolygonPosition);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonMesh", EngineDFFGetPolygonMesh);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonPosition", EngineDFFSetPolygonPosition);
    CLuaCFunctions::AddFunction("engineDFFGetMaterialInfo", EngineDFFGetMaterialInfo);
    CLuaCFunctions::AddFunction("engineDFFSetVertexPosition", EngineDFFSetVertexPosition);
    CLuaCFunctions::AddFunction("engineDFFSetVertexUV", EngineDFFSetVertexUV);
    CLuaCFunctions::AddFunction("engineDFFDestroyVertex", EngineDFFDestroyVertex);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonVertices", EngineDFFSetPolygonVertices);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonMaterial", EngineDFFSetPolygonMaterial);
    CLuaCFunctions::AddFunction("engineDFFSetMaterialColor", EngineDFFSetMaterialColor);
    CLuaCFunctions::AddFunction("engineDFFSetMaterialLighting", EngineDFFSetMaterialLighting);
    CLuaCFunctions::AddFunction("engineDFFSetTextureName", EngineDFFSetTextureName);
    CLuaCFunctions::AddFunction("engineDFFSetTextureProperties", EngineDFFSetTextureProperties);
    CLuaCFunctions::AddFunction("engineDFFAddTexture", EngineDFFAddTexture);
    CLuaCFunctions::AddFunction("engineDFFFlipPolygon", EngineDFFFlipPolygon);
    CLuaCFunctions::AddFunction("engineDFFToString", EngineDFFToString);
    CLuaCFunctions::AddFunction("engineDFFDestroyPolygon", EngineDFFDestroyPolygon);
    CLuaCFunctions::AddFunction("engineDFFCreatePolygon", EngineDFFCreatePolygon);
    CLuaCFunctions::AddFunction("engineDFFCreateVertex", EngineDFFCreateVertex);
    CLuaCFunctions::AddFunction("engineDFFGetMeshInfo", EngineDFFGetMeshInfo);
    CLuaCFunctions::AddFunction("engineDFFSelectVertices", EngineDFFSelectVertices);
    //CLuaCFunctions::AddFunction("engineDFFCreateLight", EngineDFFCreateLight);
    //CLuaCFunctions::AddFunction("engineDFFGetFrameInfo", EngineDFFGetFrameInfo);
    //CLuaCFunctions::AddFunction("engineDFFSetInterpolation", EngineDFFSetInterpolation);


    CLuaCFunctions::AddFunction("engineCOLGetInfo", EngineCOLGetInfo);
    CLuaCFunctions::AddFunction("engineCOLSetPolygonSurface", EngineCOLSetPolygonSurface);
    CLuaCFunctions::AddFunction("engineCOLSetPolygonLighting", EngineCOLSetPolygonLighting);

    CLuaCFunctions::AddFunction("engineCOLGetPolygonPosition", EngineCOLGetPolygonPosition);
    CLuaCFunctions::AddFunction("engineCOLGetPolygonConnectedVertices", EngineCOLGetPolygonConnectedVertices);
    CLuaCFunctions::AddFunction("engineCOLSetPolygonConnectedVertices", EngineCOLSetPolygonConnectedVertices);
    CLuaCFunctions::AddFunction("engineCOLGetVertexPosition", EngineCOLGetVertexPosition);
    CLuaCFunctions::AddFunction("engineCOLSetVertexPosition", EngineCOLSetVertexPosition);
    CLuaCFunctions::AddFunction("engineCOLCreateVertex", EngineCOLCreateVertex);
    CLuaCFunctions::AddFunction("engineCOLCreatePolygon", EngineCOLCreatePolygon);
    CLuaCFunctions::AddFunction("engineCOLDestroyVertex", EngineCOLDestroyVertex);
    CLuaCFunctions::AddFunction("engineCOLDestroyPolygon", EngineCOLDestroyPolygon);


    CLuaCFunctions::AddFunction("engineTXDGetTexturesCount", EngineTXDGetTexturesCount);
    CLuaCFunctions::AddFunction("engineTXDGetTextureInfo", EngineTXDGetTextureInfo);
    CLuaCFunctions::AddFunction("engineTXDGetTexturePixels", EngineTXDGetTexturePixels);

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
    unsigned short usModel;
    CScriptArgReader argStream ( luaVM );
    // Grab the COL filename or data
    argStream.ReadString ( strFile );
    argStream.ReadNumber(usModel, false);

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
                        pCol->usModel = usModel;
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

int CLuaEngineDefs::EngineDFFGetFrameInfo(lua_State* luaVM)
{
    CClientDFF* pDFF;
    unsigned short usFrameId;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usFrameId);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RwFrame* pFrame = reinterpret_cast<RwFrame *>(pAtomic->object.object.parent);
                RpGeometry* pGeometry = pAtomic->geometry;
                unsigned short framesCount = 1;
                while (pFrame->child != NULL)
                {
                    framesCount++;
                    pFrame = pFrame->child;
                }
                if (usFrameId > framesCount)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                lua_newtable(luaVM);

                lua_pushstring(luaVM, "name");
                lua_pushstring(luaVM, pFrame->szName);
                lua_settable(luaVM, -3);
                if (pFrame->child != NULL)
                {
                    lua_pushstring(luaVM, "child");
                    lua_pushnumber(luaVM, (unsigned short)pFrame->child);
                    lua_settable(luaVM, -3);
                }
                if (pFrame->next != NULL)
                {
                    lua_pushstring(luaVM, "next");
                    lua_pushnumber(luaVM, (unsigned short)pFrame->next);
                    lua_settable(luaVM, -3);
                }
                lua_pushstring(luaVM, "rotationMatrixAt");
                lua_pushvector(luaVM, pFrame->modelling.at.getVector());
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "rotationMatrixRight");
                lua_pushvector(luaVM, pFrame->modelling.right.getVector());
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "rotationMatrixUp");
                lua_pushvector(luaVM, pFrame->modelling.up.getVector());
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "position");
                lua_pushvector(luaVM, pFrame->modelling.pos.getVector());
                lua_settable(luaVM, -3);
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

int CLuaEngineDefs::EngineDFFCreateLight(lua_State* luaVM)
{
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RwFrame* pFrame = pAtomic->getFrame();
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

                lua_pushstring(luaVM, "morphTargetCount");
                lua_pushnumber(luaVM, pGeometry->morphTarget_size);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "meshCount");
                lua_pushnumber(luaVM, pGeometry->mesh->numMeshes);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "texCoordSetsCount");
                lua_pushnumber(luaVM, pGeometry->texcoords_size);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "framesCount");
                unsigned short framesCount = 1;
                while (pFrame->child != NULL)
                {
                    framesCount++;
                    pFrame = pFrame->child;
                }
                lua_pushnumber(luaVM, framesCount);
                lua_settable(luaVM, -3);


                lua_pushstring(luaVM, "geometryCount");
                lua_pushnumber(luaVM, 2);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "flags");
                lua_pushnumber(luaVM, pGeometry->flags);
                //lua_pushstring(luaVM, CClientDFF::GetometryFlags(pGeometry));
                lua_settable(luaVM, -3);
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
                RpAtomic* pAtomic = pClump->getAtomic();
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

int CLuaEngineDefs::EngineDFFSetTextureProperties(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiTextureId = NULL;
    float uiValue;
    SString sPropertiesName;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiTextureId);
    argStream.ReadString(sPropertiesName);
    argStream.ReadNumber(uiValue);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                uiTextureId--;
                if (!pGeometry->mesh->isValidMeshId(uiTextureId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMaterial* material = pGeometry->materials.materials[uiTextureId];
                if (material->texture == NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (sPropertiesName == "u")
                {
                    material->texture->raster->u = uiValue;
                }
                else if (sPropertiesName == "v")
                {
                    material->texture->raster->v = uiValue;
                }
                else if (sPropertiesName == "width")
                {
                    material->texture->raster->width = uiValue;
                }
                else if (sPropertiesName == "height")
                {
                    material->texture->raster->height = uiValue;
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

int CLuaEngineDefs::EngineDFFAddTexture(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiMaterialId = NULL;
    int width, height, depth, flags;
    SString sName;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiMaterialId);
    argStream.ReadString(sName);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                uiMaterialId--;
                if ( !pGeometry->mesh->isValidMeshId(uiMaterialId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMaterial* material = pGeometry->materials.materials[uiMaterialId];
                RpMaterial* material2 = pGeometry->mesh->getMeshes()[uiMaterialId].material;
                if (material->texture != NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwRaster* newRaster = CClientDFF::CreateRaster(512, 512, 16, 0);
                RwTexture* newTexture = CClientDFF::CreateTexture(newRaster);
                strcpy(newTexture->name, sName);
                material->texture = newTexture;
                material2->texture = newTexture;
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

int CLuaEngineDefs::EngineDFFSetInterpolation(lua_State* luaVM)
{
    CClientDFF* pDFF;
    unsigned int i1,i2,i3,i4,i5;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(i1);
    argStream.ReadNumber(i2);
    argStream.ReadNumber(i3);
    argStream.ReadNumber(i4);
    argStream.ReadNumber(i5);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                pAtomic->interpolation.unknown1 = i1;
                pAtomic->interpolation.unknown2 = i2;
                pAtomic->interpolation.unknown3 = i3;
                pAtomic->interpolation.unknown4 = i4;
                pAtomic->interpolation.unknown5 = i5;
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
    uint uiMaterialId = NULL;

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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                uiMaterialId--;
                if (!pGeometry->mesh->isValidMeshId(uiMaterialId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh m = pGeometry->mesh->getMeshes()[uiMaterialId];
                RpMaterial* material = m.material;
                lua_newtable(luaVM);
                lua_pushstring(luaVM, "id");
                lua_pushnumber(luaVM, material->id);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "refs");
                lua_pushnumber(luaVM, material->refs);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "mat");
                RpMaterial* asdf = pGeometry->materials.materials[uiMaterialId];
                if (asdf->texture != nullptr)
                {
                    lua_pushstring(luaVM, asdf->texture->name);
                    lua_settable(luaVM, -3);
                    lua_pushstring(luaVM, "raster");
                    lua_pushboolean(luaVM, asdf->texture->raster!=NULL);
                    lua_settable(luaVM, -3);
                }
                else {
                    lua_pushstring(luaVM, "NIE");
                    lua_settable(luaVM, -3);
                }
                lua_pushstring(luaVM, "texture");
                if (material->texture == nullptr)
                {
                    lua_pushboolean(luaVM, false);
                }
                else
                {
                    lua_pushstring(luaVM, material->texture->name);
                }
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "polygons");
                lua_pushnumber(luaVM, m.numIndices/3);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "lighting");
                lua_newtable(luaVM);
                    lua_pushstring(luaVM, "ambient");
                    lua_pushnumber(luaVM, material->lighting.ambient);
                    lua_settable(luaVM, -3);
                    lua_pushstring(luaVM, "diffuse");
                    lua_pushnumber(luaVM, material->lighting.diffuse);
                    lua_settable(luaVM, -3);
                    lua_pushstring(luaVM, "specular");
                    lua_pushnumber(luaVM, material->lighting.specular);
                    lua_settable(luaVM, -3);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "color");
                lua_newtable(luaVM);
                    lua_pushnumber(luaVM, 1);
                    lua_pushnumber(luaVM, material->color.r);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 2);
                    lua_pushnumber(luaVM, material->color.g);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 3);
                    lua_pushnumber(luaVM, material->color.b);
                    lua_settable(luaVM, -3);
                    lua_pushnumber(luaVM, 4);
                    lua_pushnumber(luaVM, material->color.a);
                    lua_settable(luaVM, -3);
                lua_settable(luaVM, -3);
                lua_pushstring(luaVM, "asdf");
                RwResEntry* fff = pGeometry->repEntry;
                lua_pushnumber(luaVM, pGeometry->repEntry->size);
                lua_settable(luaVM, -3);
                abort();
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
                RpAtomic* pAtomic = pClump->getAtomic();
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

int CLuaEngineDefs::EngineDFFSetTextureName(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiMaterialId = NULL;
    SString name, mask;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiMaterialId);
    argStream.ReadString(name);
    argStream.ReadString(mask);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                uiMaterialId--;
                if (uiMaterialId > pGeometry->mesh->numMeshes - 1) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh* m = pGeometry->mesh->getMeshes() + uiMaterialId;

                if (m->material->texture != nullptr)
                {
                    strcpy(m->material->texture->name, name);
                    strcpy(m->material->texture->mask, mask);
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
                RpAtomic* pAtomic = pClump->getAtomic();
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

bool sort(int i, int j) { return (i<j); }
int CLuaEngineDefs::EngineDFFSelectVertices(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString sSelectType;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(sSelectType);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (sSelectType == "byMeshId") {

                    uint materialId = NULL;
                    argStream.ReadNumber(materialId);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    RpMesh* mesh = pGeometry->mesh->getMeshes();
                    if (materialId > mesh->numIndices || materialId==NULL)
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }

                    materialId--;
                    mesh = mesh + materialId;
                    uint id = 0;
                    std::vector<int> vertices;
                    lua_newtable(luaVM);
                    for (uint i = 0; i < mesh->numIndices / 3; i++)
                    {
                        unsigned short indices1 = mesh->indices[(i * 3) + 0];
                        unsigned short indices2 = mesh->indices[(i * 3) + 1];
                        unsigned short indices3 = mesh->indices[(i * 3) + 2];

                        for (uint i2 = 0; i2 < pGeometry->triangles_size; i2++)
                        {
                            RpTriangle pTriangle = pGeometry->triangles[i2];
                            if (pTriangle.v[0] == indices1 &&
                                pTriangle.v[1] == indices2 &&
                                pTriangle.v[2] == indices3)
                            {
                                if (std::find(vertices.begin(), vertices.end(), indices1) == vertices.end())
                                    vertices.push_back(indices1);
                                if (std::find(vertices.begin(), vertices.end(), indices2) == vertices.end())
                                    vertices.push_back(indices2);
                                if (std::find(vertices.begin(), vertices.end(), indices3) == vertices.end())
                                    vertices.push_back(indices3);

                            }
                        }
                    }
                    std::sort(vertices.begin(), vertices.end(), sort);
                    for (int i = 0; i < vertices.size(); i++) {
                        lua_pushnumber(luaVM, i+1);
                        lua_pushnumber(luaVM, vertices[i]+1);
                        lua_settable(luaVM, -3);
                    }
                    return 1;
                }
                else if (sSelectType == "byasdf")
                {

                }
                else if (sSelectType == "nearest3d")
                {
                    CVector vPosition;
                    argStream.ReadVector3D(vPosition);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    uint nearest = NULL;
                    float distance = 99999;
                    for (uint i = 0; i < pGeometry->vertices_size; i++)
                    {
                        RwV3d vert = pGeometry->morphTarget->verts[i];
                        CVector vVertPosition;
                        vVertPosition.fX = vert.x;
                        vVertPosition.fY = vert.y;
                        vVertPosition.fZ = vert.z;
                        float dis=DistanceBetweenPoints3D(vPosition, vVertPosition);
                        if (distance > dis)
                        {
                            distance = dis;
                            nearest = i+1;
                        }
                    }
                    lua_pushnumber(luaVM, nearest);
                    return 1;
                }
                else if (sSelectType == "nearest2d")
                {
                    CVector2D vPosition;
                    argStream.ReadVector2D(vPosition);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    uint nearest = NULL;
                    float distance = 99999;
                    for (uint i = 0; i < pGeometry->vertices_size; i++)
                    {
                        RwV3d vert = pGeometry->morphTarget->verts[i];
                        CVector2D vVertPosition;
                        vVertPosition.fX = vert.x;
                        vVertPosition.fY = vert.y;
                        float dis = DistanceBetweenPoints2D(vPosition, vVertPosition);
                        if (distance > dis)
                        {
                            distance = dis;
                            nearest = i + 1;
                        }
                    }
                    lua_pushnumber(luaVM, nearest);
                    return 1;
                }
                lua_pushboolean(luaVM, false);
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);
                lua_newtable(luaVM);
                for (uint i = 0; i < pGeometry->vertices_size; i++)
                {
                    if (pGeometry->morphTarget->normals != NULL)
                    {
                        RwV3d* vVert = &pGeometry->morphTarget->verts[i];
                        RwV3d* pTriangle = &pGeometry->morphTarget->normals[i];
                        CVector vPos;
                        vPos.fX = vVert->x;
                        vPos.fY = vVert->y;
                        vPos.fZ = vVert->z;
                        CVector vNormal;
                        int pp = (int)&pTriangle;
                        vNormal.fX = pTriangle->x;  //crash
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

int CLuaEngineDefs::EngineDFFGetMeshInfo(lua_State* luaVM)
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uMeshId != NULL && uMeshId <= pGeometry->mesh->numMeshes)
                {
                    RpMesh* mesh = pGeometry->mesh->getMeshes();
                    uint meshCount = pGeometry->mesh->numMeshes;
                    if (uMeshId > meshCount)
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    uMeshId--;
                    RpMesh* myMesh = &mesh[uMeshId];
                    lua_newtable(luaVM);
                    lua_pushstring(luaVM, "materialId");
                    lua_pushnumber(luaVM, myMesh->material->id);
                    lua_settable(luaVM, -3);
                    lua_pushstring(luaVM, "materialId2");
                    lua_pushnumber(luaVM, (int)myMesh->material);
                    lua_settable(luaVM, -3);

                    lua_pushstring(luaVM, "polygonsCounts");
                    lua_pushnumber(luaVM, myMesh->numIndices/3);
                    lua_settable(luaVM, -3);

                    if (myMesh->material->texture != nullptr)
                    {
                        lua_pushstring(luaVM, "texture");
                        lua_pushstring(luaVM, myMesh->material->texture->name);
                        lua_settable(luaVM, -3);
                    }
                    else
                    {
                        lua_pushstring(luaVM, "texture");
                        lua_pushboolean(luaVM, false);
                        lua_settable(luaVM, -3);
                    }
                    
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

int CLuaEngineDefs::EngineDFFGetPolygonInfo(lua_State* luaVM)
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uTriangleId != NULL && uTriangleId <= pGeometry->triangles_size)
                {
                    RpMesh* mesh = pGeometry->mesh->getMeshes();
                    uint meshCount = pGeometry->mesh->numMeshes;
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
                                if (i2 == uTriangleId &&
                                    pTriangle.v[0] == indices1 &&
                                    pTriangle.v[1] == indices2 &&
                                    pTriangle.v[2] == indices3)
                                {
                                    lua_newtable(luaVM);
                                    lua_pushstring(luaVM, "materialId");
                                    lua_pushnumber(luaVM, pTriangle.matId);
                                    lua_settable(luaVM, -3);
                                    lua_pushstring(luaVM, "meshId");
                                    lua_pushnumber(luaVM, meshCount + 1);
                                    lua_settable(luaVM, -3);
                                    if (myMesh->material->texture != nullptr)
                                    {
                                        lua_pushstring(luaVM, "textureName");
                                        lua_pushstring(luaVM, myMesh->material->texture->name);
                                        lua_settable(luaVM, -3);
                                    }
                                    return 1;
                                }
                            }
                        }
                    }
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

int CLuaEngineDefs::EngineDFFFlipPolygon(lua_State* luaVM)
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
                if (uTriangleId == NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uTriangleId--;
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                RpMesh* mesh = pGeometry->mesh->getMeshes();
                uint meshCount = pGeometry->mesh->numMeshes;
                while(meshCount>0)
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
                            if (i2 == uTriangleId &&
                                pTriangle.v[0] == indices1 &&
                                pTriangle.v[1] == indices2 &&
                                pTriangle.v[2] == indices3)
                            {
                                std::swap(myMesh->indices[i* 3 + 2], myMesh->indices[i * 3 + 0]);
                                lua_pushboolean(luaVM, true);
                                return 1;
                            }
                        }
                    }
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

int CLuaEngineDefs::EngineDFFGetPolygons(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygonId = NULL;
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);
                for (uint i = 0; i < pGeometry->triangles_size; i++)
                {
                    RpTriangle* pTriangle = &pGeometry->triangles[i];
                    lua_pushnumber(luaVM, i+1); // start from 1 not 0
                    lua_newtable(luaVM);
                        lua_pushnumber(luaVM, 1);
                        lua_pushnumber(luaVM, pTriangle->v[0] + 1);
                        lua_settable(luaVM, -3);
                        lua_pushnumber(luaVM, 2);
                        lua_pushnumber(luaVM, pTriangle->v[1] + 1);
                        lua_settable(luaVM, -3);
                        lua_pushnumber(luaVM, 3);
                        lua_pushnumber(luaVM, pTriangle->v[2] + 1);
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

int CLuaEngineDefs::EngineDFFCreateVertex(lua_State* luaVM)
{
    CClientDFF* pDFF;
    CVector pos;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadVector3D(pos);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                pGeometry->vertices_size++;
                int lastVertex = pGeometry->vertices_size - 1;
                RwV3d* verts = pGeometry->morphTarget->verts;
                RwV3d* newVerts = reinterpret_cast<RwV3d *>(malloc(pGeometry->vertices_size * sizeof(RwV3d)));
                for (int i = 0; i < lastVertex; i++)
                {
                    newVerts[i] = verts[i];
                }
                RwV3d vVert;
                vVert.x = pos.fX;
                vVert.y = pos.fY;
                vVert.z = pos.fZ;
                newVerts[lastVertex] = vVert;
                free(pGeometry->morphTarget->verts);
                pGeometry->morphTarget->verts = (RwV3d *)newVerts;
                lua_pushnumber(luaVM, pGeometry->vertices_size);
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


int CLuaEngineDefs::EngineDFFSetVertexUV(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiVertexId;
    float u,v;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiVertexId);
    argStream.ReadNumber(u);
    argStream.ReadNumber(v);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (!pGeometry->isValidVertexId(uiVertexId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uiVertexId--;
                RwTextureCoordinates* vVert = pGeometry->texcoords[0];
                if (vVert == NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwTextureCoordinates asdf = vVert[uiVertexId];
                asdf.u = u;
                asdf.v = v;
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiVertex > pGeometry->vertices_size) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uiVertex--;
                RwV3d* vVert = &pGeometry->morphTarget->verts[uiVertex];
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

int CLuaEngineDefs::EngineDFFSetPolygonPosition(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygonId;
    CVector vNewPosition;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiPolygonId);
    argStream.ReadVector3D(vNewPosition);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {

                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiPolygonId == NULL || uiPolygonId > pGeometry->triangles_size)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uiPolygonId--;
                RpTriangle pTriangle = pGeometry->triangles[uiPolygonId];
                RwV3d* vert1 = &pGeometry->morphTarget->verts[pTriangle.v[0]];
                RwV3d* vert2 = &pGeometry->morphTarget->verts[pTriangle.v[1]];
                RwV3d* vert3 = &pGeometry->morphTarget->verts[pTriangle.v[2]];
                CVector avgPosition;
                avgPosition.fX = (vert1->x + vert2->x + vert3->x) / 3;
                avgPosition.fY = (vert1->y + vert2->y + vert3->y) / 3;
                avgPosition.fZ = (vert1->z + vert2->z + vert3->z) / 3;
                CVector moveOffset = vNewPosition - avgPosition;
                vert1->x += moveOffset.fX;
                vert2->x += moveOffset.fX;
                vert3->x += moveOffset.fX;
                vert1->y += moveOffset.fY;
                vert2->y += moveOffset.fY;
                vert3->y += moveOffset.fY;
                vert1->z += moveOffset.fZ;
                vert2->z += moveOffset.fZ;
                vert3->z += moveOffset.fZ;
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

int CLuaEngineDefs::EngineDFFGetPolygonPosition(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiPolygonId;
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiPolygonId == NULL || uiPolygonId > pGeometry->triangles_size)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uiPolygonId--;
                RpTriangle pTriangle = pGeometry->triangles[uiPolygonId];
                RwV3d vert1 = pGeometry->morphTarget->verts[pTriangle.v[0]];
                RwV3d vert2 = pGeometry->morphTarget->verts[pTriangle.v[1]];
                RwV3d vert3 = pGeometry->morphTarget->verts[pTriangle.v[2]];
                CVector avgPosition;
                avgPosition.fX = (vert1.x + vert2.x + vert3.x)/3;
                avgPosition.fY = (vert1.y + vert2.y + vert3.y)/3;
                avgPosition.fZ = (vert1.z + vert2.z + vert3.z)/3;
                lua_pushvector(luaVM, avgPosition);
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

int CLuaEngineDefs::EngineDFFSetPolygonVertices(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uTriangleId = NULL;
    uint vertex1, vertex2, vertex3;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uTriangleId);
    argStream.ReadNumber(vertex1);
    argStream.ReadNumber(vertex2);
    argStream.ReadNumber(vertex3);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                if (uTriangleId == NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uTriangleId--;
                vertex1--;
                vertex2--;
                vertex3--;
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                RpMesh* mesh = pGeometry->mesh->getMeshes();
                uint meshCount = pGeometry->mesh->numMeshes;
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
                            if (i2 == uTriangleId &&
                                pTriangle.v[0] == indices1 &&
                                pTriangle.v[1] == indices2 &&
                                pTriangle.v[2] == indices3)
                            {
                                myMesh->indices[i * 3] = vertex1;
                                myMesh->indices[i * 3 + 1] = vertex2;
                                myMesh->indices[i * 3 + 2] = vertex3;
                                lua_pushboolean(luaVM, true);
                                return 1;
                            }
                        }
                    }
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
                RpAtomic* pAtomic = pClump->getAtomic();
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

int CLuaEngineDefs::EngineDFFGetPolygonMesh(lua_State* luaVM)
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if ( !pGeometry->isValidTriangleId(uTriangleId) )
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uTriangleId--;
                uint meshId = CClientDFF::GetMeshIdFromPolygonId(pGeometry, uTriangleId);
                if(meshId==-1)
                    lua_pushboolean(luaVM, false);
                else
                    lua_pushnumber(luaVM, meshId+1);

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

int CLuaEngineDefs::EngineDFFDestroyPolygon(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint uiTriangleId;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiTriangleId);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (!pGeometry->isValidTriangleId(uiTriangleId))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uiTriangleId--;
                bool ret = CClientDFF::GeometryDestroyPolygon(pGeometry, uiTriangleId);
                //uint rrr = CClientDFF::GetPolygonIdInMesh(pGeometry, CClientDFF::GetMeshFromPolygonId(pGeometry, uiTriangleId), uiTriangleId);
                lua_pushboolean(luaVM, ret);
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

int CLuaEngineDefs::EngineDFFCreatePolygon(lua_State* luaVM)
{
    CClientDFF* pDFF;
    uint vertex1, vertex2, vertex3, meshId;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(vertex1);
    argStream.ReadNumber(vertex2);
    argStream.ReadNumber(vertex3);
    argStream.ReadNumber(meshId, 1);
    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                vertex1--;
                vertex2--;
                vertex3--;
                meshId--;
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                RpMesh* mesh = pGeometry->mesh->getMeshes();
                RpMesh* myMesh = &mesh[meshId];
                pGeometry->triangles_size++;
                uint lastPolygon = pGeometry->triangles_size - 1;
                myMesh->numIndices += 3;
                pGeometry->mesh->totalIndicesInMesh += 3;
                uint numIndices = myMesh->numIndices;
                unsigned short* polygons = myMesh->indices;
                unsigned short* newPolygons1 = reinterpret_cast<unsigned short*>(malloc(numIndices * 4));    // unsigned short - size=4
                RpTriangle* newPolygons2 = reinterpret_cast<RpTriangle*>(malloc(sizeof(RpTriangle) * pGeometry->triangles_size));
                for (int i = 0; i < numIndices-3; i++)
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
                lua_pushnumber(luaVM, pGeometry->triangles_size);
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (uiVertex > pGeometry->vertices_size) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                int ii = 0;
                for (int i = 0; i < pGeometry->vertices_size; i++)
                {
                    //pGeometry->morphTarget->verts[i] = std::move(pGeometry->morphTarget->verts[i + 1]);
                }
                //RwV3d* vert = &pGeometry->morphTarget->verts[pGeometry->vertices_size-1];
                //vert = NULL;
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

int CLuaEngineDefs::EngineDFFGetPolygonConnectedToVertex(lua_State* luaVM)
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
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                lua_newtable(luaVM);
                uiVertex--;
                uint ii = 0;
                for (uint i = 0; i < pGeometry->triangles_size; i++)
                {
                    RpTriangle* pTriangle = &pGeometry->triangles[i];
                    if (pTriangle!=nullptr && (pTriangle->v[0] == uiVertex ||
                        pTriangle->v[1] == uiVertex ||
                        pTriangle->v[2] == uiVertex))
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


// COL Functions

int CLuaEngineDefs::EngineCOLGetInfo(lua_State* luaVM)
{
    CClientColModel* pCOL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);

    if (!argStream.HasErrors())
    {
        //lua_newtable(luaVM);
        lua_newtable(luaVM);
        lua_pushstring(luaVM, "polygonCount");
        lua_pushnumber(luaVM, pCOL->GetModelPolygonCount());
        lua_settable(luaVM, -3);
        lua_pushstring(luaVM, "boundingBox");
        lua_newtable(luaVM);
        lua_pushstring(luaVM, "radius");
        lua_pushnumber(luaVM, pCOL->GetModelBoundingBoxRadius());
        lua_settable(luaVM, -3);
        lua_pushstring(luaVM, "offset");
        lua_pushvector(luaVM, pCOL->GetModelBoundingBoxOffset());
        lua_settable(luaVM, -3);
        lua_pushstring(luaVM, "vecMin");
        lua_pushvector(luaVM, pCOL->GetModelBoundingBoxVecMin());
        lua_settable(luaVM, -3);
        lua_pushstring(luaVM, "vecMax");
        lua_pushvector(luaVM, pCOL->GetModelBoundingBoxVecMax());
        lua_settable(luaVM, -3);

        lua_settable(luaVM, -3);

        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLSetPolygonSurface(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usSurfaceId, usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usSurfaceId);
    argStream.ReadNumber(usVertex);

    if (!argStream.HasErrors())
    {
        pCOL->SetModelPolygonSurface(usVertex, usSurfaceId);
        lua_pushboolean(luaVM, true);
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLGetVertexPosition(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usVertex);

    if (!argStream.HasErrors())
    {
        if (usVertex == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usVertex--;
        lua_pushvector(luaVM, pCOL->GetVertexPosition(usVertex) / 128);    // this is compressed vertex position, 128 = 1
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLGetPolygonPosition(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usPolygon;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usPolygon);

    if (!argStream.HasErrors())
    {
        if (usPolygon == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usPolygon--;
        unsigned short vertex1 = NULL;
        unsigned short vertex2 = NULL;
        unsigned short vertex3 = NULL;
        pCOL->GetTriangleConnectedVertices(usPolygon, vertex1, vertex2, vertex3);
        CVector position;
        position += pCOL->GetVertexPosition(vertex1) / 128;
        position += pCOL->GetVertexPosition(vertex2) / 128;
        position += pCOL->GetVertexPosition(vertex3) / 128;
        lua_pushvector(luaVM, position / 3);
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLSetVertexPosition(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usVertex;
    CVector position;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usVertex);
    argStream.ReadVector3D(position);

    if (!argStream.HasErrors())
    {
        if (usVertex == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usVertex--;
        pCOL->SetVertexPosition(usVertex, position);
        pCOL->UpdateBoundingBox();
        lua_pushboolean(luaVM, true);
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLGetPolygonConnectedVertices(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usPolygon;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usPolygon);

    if (!argStream.HasErrors())
    {
        if (usPolygon == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usPolygon--;
        unsigned short vertex1 = NULL;
        unsigned short vertex2 = NULL;
        unsigned short vertex3 = NULL;
        pCOL->GetTriangleConnectedVertices(usPolygon, vertex1, vertex2, vertex3);
        if (vertex1 == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        else
        {
            lua_pushnumber(luaVM, vertex1+1);
            lua_pushnumber(luaVM, vertex2+1);
            lua_pushnumber(luaVM, vertex3+1);
            return 3;
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLSetPolygonConnectedVertices(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usPolygon, usVertex1, usVertex2, usVertex3;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usPolygon);
    argStream.ReadNumber(usVertex1);
    argStream.ReadNumber(usVertex2);
    argStream.ReadNumber(usVertex3);

    if (!argStream.HasErrors())
    {
        if (usPolygon == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usPolygon--;
        usVertex1--;
        usVertex2--;
        usVertex3--;
        pCOL->SetTriangleConnectedVertices(usPolygon, usVertex1, usVertex2, usVertex3);
        lua_pushboolean(luaVM, true);
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLSetPolygonLighting(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usPolygon;
    CVector position;
    unsigned short day, night=NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usPolygon);
    argStream.ReadNumber(day);
    argStream.ReadNumber(night);

    if (!argStream.HasErrors())
    {
        if (usPolygon == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usPolygon--;
        pCOL->SetTriangleSetLighting(usPolygon, day, night);
        lua_pushboolean(luaVM, true);
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLCreatePolygon(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short vertex1, vertex2, vertex3;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(vertex1);
    argStream.ReadNumber(vertex2);
    argStream.ReadNumber(vertex3);

    if (!argStream.HasErrors())
    {
        vertex1--;
        vertex2--;
        vertex3--;
        unsigned short usPolygon = pCOL->CreatePolygon(vertex1, vertex2, vertex3);
        if (usPolygon == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        else
        {
            lua_pushnumber(luaVM, usPolygon + 1);
            return 1;
        }
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLDestroyPolygon(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usPolygon;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usPolygon);

    if (!argStream.HasErrors())
    {
        usPolygon--;
        bool result = pCOL->DestroyPolygon(usPolygon);
        if (result)
        {
            pCOL->UpdateBoundingBox();
            lua_pushboolean(luaVM, true);
            return 1;
        }
        else
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLCreateVertex(lua_State* luaVM)
{
    CClientColModel* pCOL;
    CVector vecPosition;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadVector3D(vecPosition);

    if (!argStream.HasErrors())
    {
        unsigned short usVertex = pCOL->CreateVertex(vecPosition);
        if (usVertex == NULL)
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        else
        {
            lua_pushnumber(luaVM, usVertex + 1);
            pCOL->UpdateBoundingBox();
            return 1;
        }
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineCOLDestroyVertex(lua_State* luaVM)
{
    CClientColModel* pCOL;
    unsigned short usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usVertex);

    if (!argStream.HasErrors())
    {
        usVertex--;
        lua_pushboolean(luaVM, pCOL->DestroyVertex(usVertex));
        pCOL->UpdateBoundingBox();
        return 1;
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

// TXD Functions

int CLuaEngineDefs::EngineTXDGetTexturesCount(lua_State* luaVM)
{
    CClientTXD* pTXD = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTXD);

    if (!argStream.HasErrors())
    {
        std::vector< RwTexture* > textures = pTXD->m_ReplacementTextures.textures;
        lua_pushnumber(luaVM, textures.size());
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineTXDGetTextureInfo(lua_State* luaVM)
{
    CClientTXD* pTXD = NULL;
    unsigned short textureId=NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTXD);
    argStream.ReadNumber(textureId);

    if (!argStream.HasErrors())
    {
        std::vector< RwTexture* > textures = pTXD->m_ReplacementTextures.textures;
        if (textureId > NULL && textureId <= textures.size() || 1==1)
        {
            RwTexture* texture = textures.at(textureId);

            lua_newtable(luaVM);
            lua_pushstring(luaVM, "name");
            lua_pushstring(luaVM, texture->name);
            lua_settable(luaVM, -3);

            lua_pushstring(luaVM, "mask");
            lua_pushstring(luaVM, texture->mask);
            lua_settable(luaVM, -3);

            lua_pushstring(luaVM, "width");
            lua_pushnumber(luaVM, texture->raster->width);
            lua_settable(luaVM, -3);

            lua_pushstring(luaVM, "height");
            lua_pushnumber(luaVM, texture->raster->height);
            lua_settable(luaVM, -3);

            lua_pushstring(luaVM, "depth");
            lua_pushnumber(luaVM, texture->raster->depth);
            lua_settable(luaVM, -3);
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaEngineDefs::EngineTXDGetTexturePixels(lua_State* luaVM)
{
    /*
    CClientTXD* pTXD = NULL;
    unsigned short textureId = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTXD);
    argStream.ReadNumber(textureId);

    if (!argStream.HasErrors())
    {
        std::vector< RwTexture* > textures = pTXD->m_ReplacementTextures.textures;
        if (textureId > NULL && textureId <= textures.size())
        {
            RwTexture* texture = textures.at(textureId);
            unsigned char* pixels = texture->raster->pixels;    // NULL
            unsigned char* pixels2 = pixels + 1;
            unsigned char* pixels3 = pixels + 2;
            unsigned char* pixels4 = pixels + 3;
            //abort();
            lua_pushstring(luaVM, (const char*)texture->raster->pixels);
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
        */
    lua_pushboolean(luaVM, false);
    return 1;
}