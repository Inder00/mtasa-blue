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
#include "../game_sa/CColModelSA.h"
#include <SharedUtil.Crypto.h>

void CLuaEngineDefs::LoadFunctions ( void )
{
    CLuaCFunctions::AddFunction ( "engineLoadTXD", EngineLoadTXD );
    CLuaCFunctions::AddFunction ( "engineLoadCOL", EngineLoadCOL );
    CLuaCFunctions::AddFunction ( "engineLoadDFF", EngineLoadDFF );
    CLuaCFunctions::AddFunction ( "engineImportTXD", EngineImportTXD );
    CLuaCFunctions::AddFunction ( "engineReplaceCOL", EngineReplaceCOL );
    CLuaCFunctions::AddFunction ( "engineRestoreCOL", EngineRestoreCOL );
    CLuaCFunctions::AddFunction("engineDFFGetProperties", EngineDFFGetProperties);
    CLuaCFunctions::AddFunction("engineDFFGetBoundingBox", EngineDFFGetBoundingBox);
    CLuaCFunctions::AddFunction("engineDFFSetGeometry", EngineDFFSetGeometry);
    CLuaCFunctions::AddFunction("engineDFFSetSetCenter", EngineDFFSetCenter);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonConnectedToVertex", EngineDFFGetPolygonConnectedToVertex);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonPosition", EngineDFFGetPolygonPosition);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonMesh", EngineDFFGetPolygonMesh);
    CLuaCFunctions::AddFunction("engineDFFGetPolygonVertices", EngineDFFGetPolygonVertices);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonPosition", EngineDFFSetPolygonPosition);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonMesh", EngineDFFSetPolygonMesh);
    CLuaCFunctions::AddFunction("engineDFFGetMaterialProperties", EngineDFFGetMaterialProperties);
    CLuaCFunctions::AddFunction("engineDFFSetVertexPosition", EngineDFFSetVertexPosition);
    CLuaCFunctions::AddFunction("engineDFFSetVertexUV", EngineDFFSetVertexUV);
    CLuaCFunctions::AddFunction("engineDFFSetVertexLight", EngineDFFSetVertexLight);
    CLuaCFunctions::AddFunction("engineDFFGetVertexUV", EngineDFFGetVertexUV);
    CLuaCFunctions::AddFunction("engineDFFGetVertexLight", EngineDFFGetVertexLight);
    CLuaCFunctions::AddFunction("engineDFFGetVertexPosition", EngineDFFGetVertexPosition);
    CLuaCFunctions::AddFunction("engineDFFDestroyVertex", EngineDFFDestroyVertex);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonVertices", EngineDFFSetPolygonVertices);
    CLuaCFunctions::AddFunction("engineDFFSetPolygonMaterial", EngineDFFSetPolygonMaterial);
    CLuaCFunctions::AddFunction("engineDFFSetMaterialColor", EngineDFFSetMaterialColor);
    CLuaCFunctions::AddFunction("engineDFFSetMaterialLighting", EngineDFFSetMaterialLighting);
    CLuaCFunctions::AddFunction("engineDFFSetTextureName", EngineDFFSetTextureName);
    CLuaCFunctions::AddFunction("engineDFFSetTextureProperties", EngineDFFSetTextureProperties);
    CLuaCFunctions::AddFunction("engineDFFSetTexture", EngineDFFSetTexture);
    CLuaCFunctions::AddFunction("engineDFFGetTextureProperties", EngineDFFGetTextureProperties);
    CLuaCFunctions::AddFunction("engineDFFDestroyPolygon", EngineDFFDestroyPolygon);
    CLuaCFunctions::AddFunction("engineDFFCreatePolygon", EngineDFFCreatePolygon);
    CLuaCFunctions::AddFunction("engineDFFCreateVertex", EngineDFFCreateVertex);
    CLuaCFunctions::AddFunction("engineDFFGetMeshInfo", EngineDFFGetMeshInfo);
    CLuaCFunctions::AddFunction("engineDFFSelectVertices", EngineDFFSelectVertices);
    CLuaCFunctions::AddFunction("engineDFFCreateEmptyModel", EngineDFFCreateEmptyModel);
    CLuaCFunctions::AddFunction("engineDFFCreateObject", EngineDFFCreateObject);
    CLuaCFunctions::AddFunction("engineDFFCreateCollision", EngineDFFCreateLight);
    CLuaCFunctions::AddFunction("engineDFFUseVerticesTool", EngineDFFUseVerticesTool);
    CLuaCFunctions::AddFunction("engineDFFUsePolygonsTool", EngineDFFUsePolygonsTool);
    CLuaCFunctions::AddFunction("engineDFFTransformVertices", EngineDFFTransformVertices);
    CLuaCFunctions::AddFunction("engineDFFTransformPolygons", EngineDFFTransformPolygons);
    //CLuaCFunctions::AddFunction("engineDFFCreateLight", EngineDFFCreateLight);
    //CLuaCFunctions::AddFunction("engineDFFCreateMesh", EngineDFFCreateMesh);
    //CLuaCFunctions::AddFunction("engineDFFGetFrameInfo", EngineDFFGetFrameInfo);
    //CLuaCFunctions::AddFunction("engineDFFSetInterpolation", EngineDFFSetInterpolation);


    CLuaCFunctions::AddFunction("engineCOLGetInfo", EngineCOLGetInfo);
    CLuaCFunctions::AddFunction("engineCOLSetPolygonSurface", EngineCOLSetPolygonSurface);
    CLuaCFunctions::AddFunction("engineCOLSetPolygonLighting", EngineCOLSetPolygonLighting);
    CLuaCFunctions::AddFunction("engineCOLCreateEmptyCollision", EngineCOLCreateEmptyCollision);

    CLuaCFunctions::AddFunction("engineCOLGetPolygonPosition", EngineCOLGetPolygonPosition);
    CLuaCFunctions::AddFunction("engineCOLGetPolygonConnectedVertices", EngineCOLGetPolygonConnectedVertices);
    CLuaCFunctions::AddFunction("engineCOLSetPolygonConnectedVertices", EngineCOLSetPolygonConnectedVertices);
    CLuaCFunctions::AddFunction("engineCOLGetVertexPosition", EngineCOLGetVertexPosition);
    CLuaCFunctions::AddFunction("engineCOLSetVertexPosition", EngineCOLSetVertexPosition);
    CLuaCFunctions::AddFunction("engineCOLCreateVertex", EngineCOLCreateVertex);
    CLuaCFunctions::AddFunction("engineCOLCreatePolygon", EngineCOLCreatePolygon);
    CLuaCFunctions::AddFunction("engineCOLDestroyVertex", EngineCOLDestroyVertex);
    CLuaCFunctions::AddFunction("engineCOLDestroyPolygon", EngineCOLDestroyPolygon);
    CLuaCFunctions::AddFunction("engineCOLSelectPolygons", EngineCOLSelectPolygons);

    CLuaCFunctions::AddFunction("engineTXDGetTexturesCount", EngineTXDGetTexturesCount);
    CLuaCFunctions::AddFunction("engineTXDGetTextureInfo", EngineTXDGetTextureInfo);
    //CLuaCFunctions::AddFunction("engineTXDGetTexturePixels", EngineTXDGetTexturePixels);

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
    ushort usModel;
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
    SString strModelName;

    CScriptArgReader argStream ( luaVM );
    // Grab the DFF filename or data (model ID ignored after 1.3.1)
    argStream.ReadString ( strFile );
    argStream.ReadString ( strModelName, "" );
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
                                pDFF->uimodel = usModelID;

                            pDFF->strModelName = strModelName;
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

int CLuaEngineDefs::EngineDFFCreateEmptyModel(lua_State* luaVM)
{
    SString strModelName;
    ushort usMeshes;
    CScriptArgReader argStream(luaVM);


    argStream.ReadString(strModelName);
    argStream.ReadNumber(usMeshes, 24);
    if (!argStream.HasErrors())
    {
        // Grab our virtual machine and grab our resource from that.
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            // Get this resource
            CResource* pResource = pLuaMain->GetResource();
            if (pResource)
            {
                SString strEmptyBase64;
                if (usMeshes == 1)
                {
                    strEmptyBase64 = "EAAAAIACAAD//wMYAQAAAAwAAAD//wMYAQAAAAAAAAAAAAAADgAAAGQAAAD//wMYAQAAADwAAAD//wMYAQAAAAAAgD8AAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAAAAAAAAAAAAP////8DAAIAAwAAABAAAAD//wMY/vJTAgQAAAD//wMYQmFzZRoAAAAoAQAA//8DGAEAAAAEAAAA//8DGAEAAAAPAAAADAEAAP//AxgBAAAAQAAAAP//AxhyAAAAAAAAAAEAAAABAAAAF7dROBe3UTgXt1E4Yp61OAEAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACAAAAHgAAAD//wMYAQAAAAgAAAD//wMYAQAAAP////8HAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAAAwAAADAAAAD//wMYDgUAABQAAAD//wMYAAAAAAEAAAAAAAAAAAAAAAAAAAD98lMCBAAAAP//AxgAAAAAFAAAACgAAAD//wMYAQAAABAAAAD//wMYAAAAAAAAAAAFAAAAAAAAAAMAAAAAAAAA//8DGAMAAACEAAAA//8DGPryUwJ4AAAA//8DGENPTDNwAAAAQmFzZQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAF7dRuBe3UbgXt1G4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==";
                }
                else
                {
                    strEmptyBase64 = "EAAAAHYQAAD//wMYAQAAAAwAAAD//wMYAQAAAAAAAAAAAAAADgAAAGYAAAD//wMYAQAAADwAAAD//wMYAQAAAAAAgD8AAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAAAAAAAAAAAAP////8DAAIAAwAAABIAAAD//wMY/vJTAgYAAAD//wMYQmFzZTI0GgAAAKAPAAD//wMYAQAAAAQAAAD//wMYAQAAAA8AAACEDwAA//8DGAEAAACIAwAA//8DGHYAAQAYAAAAFQAAAAEAAAAAAAAAAACAPwAAgD4AAIA/AAAAPwAAgD8AAAAAVVVVPwAAgD5VVVU/AAAAP1VVVT8AAAAAqqoqPwAAgD6qqio/AAAAP6qqKj8AAAAAAAAAPwAAgD4AAAA/AAAAPwAAAD8AAAAAqqqqPgAAgD6qqqo+AAAAP6qqqj4AAAAAqKoqPgAAgD6oqio+AAAAP6iqKj4AAAAAAAAAAAAAgD4AAAAAAAAAPwAAAAAAAAMAAAABAAQAAQAAAAMABAAFAAAAAQACAAEAAAAFAAQAAwAAAAcABgAHAAAAAwAEAAcAAAAFAAgABQAAAAcABgAJAAAABwAKAAcAAAAJAAgABwAAAAsACgALAAAABwAKAAkAAAANAAwADQAAAAkACgANAAAACwAOAAsAAAANAAwADwAAAA0AEAANAAAADwAOAA0AAAARABAAEQAAAA0AEAAPAAAAEwASABMAAAAPABAAEwAAABEAFAARAAAAEwAXt1E4AADAsxe3UTiCSpQ4AQAAAAEAAAAAAAAAAAAAtAAAAAAAAAAAAAAAtAAAAAAAAAAAAAAAtAAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAJUmSswAAAAAAAAAAJUmSswAAAAAAAAAAJUmSswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAACAswAAAAAAAAAAAAAAtAAAAAAAAAAAAAAAtAAAAAAAAAAAAAAAtAAAAAAAAIA/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAIAAAA0AkAAP//AxgBAAAAZAAAAP//AxgYAAAA////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////BwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAABwAAAFgAAAD//wMYAQAAABwAAAD//wMYAAAAAJaWlv/co/4AAAAAAAAAgD8AAAAAAACAPwMAAAAkAAAA//8DGPzyUwIYAAAA//8DGGZmZj9mZmY/ZmZmPwAAgD+ZmSFBAAAAAAcAAABYAAAA//8DGAEAAAAcAAAA//8DGAAAAACWlpb/3KP+AAAAAAAAAIA/AAAAAAAAgD8DAAAAJAAAAP//Axj88lMCGAAAAP//AxhmZmY/ZmZmP2ZmZj8AAIA/mZkhQQAAAAAHAAAAWAAAAP//AxgBAAAAHAAAAP//AxgAAAAAlpaW/9yj/gAAAAAAAACAPwAAAAAAAIA/AwAAACQAAAD//wMY/PJTAhgAAAD//wMYZmZmP2ZmZj9mZmY/AACAP5mZIUEAAAAAAwAAAAgCAAD//wMYDgUAAOwBAAD//wMYAAAAABgAAABIAAAAAwAAAAAAAAATAAAAEgAAAA8AAAADAAAAAQAAAAEAAAACAAAABQAAAAMAAAACAAAABQAAAAQAAAABAAAAAwAAAAMAAAAHAAAABAAAAAUAAAADAAAABAAAAAUAAAAIAAAABwAAAAMAAAAFAAAABwAAAAgAAAALAAAAAwAAAAYAAAALAAAACgAAAAcAAAADAAAABwAAAA0AAAAKAAAACwAAAAMAAAAIAAAACwAAAA4AAAANAAAAAwAAAAkAAAANAAAADgAAABEAAAADAAAACgAAABEAAAAQAAAADQAAAAMAAAALAAAAEwAAABAAAAARAAAAAwAAAAwAAAARAAAAFAAAABMAAAADAAAADQAAAAMAAAAAAAAAAQAAAAMAAAAOAAAAAQAAAAQAAAADAAAAAwAAAA8AAAADAAAABAAAAAcAAAADAAAAEAAAAAcAAAAGAAAAAwAAAAMAAAARAAAACQAAAAYAAAAHAAAAAwAAABIAAAAHAAAACgAAAAkAAAADAAAAEwAAAAkAAAAKAAAADQAAAAMAAAAUAAAADQAAAAwAAAAJAAAAAwAAABUAAAAPAAAADAAAAA0AAAADAAAAFgAAAA0AAAAQAAAADwAAAAMAAAAXAAAADwAAABAAAAATAAAA/fJTAgQAAAD//wMYAAAAABQAAAAoAAAA//8DGAEAAAAQAAAA//8DGAAAAAAAAAAABQAAAAAAAAADAAAAAAAAAP//AxgDAAAAAAAAAP//Axg=";
                }
                SString strFile = SharedUtil::Base64decode(strEmptyBase64);
                bool bIsRawData = CClientDFF::IsDFFData(strFile);
                SString strPath;
                // Is this a legal filepath?
                if (bIsRawData || CResourceManager::ParseResourcePathInput(strFile, pResource, &strPath))
                {
                    // Grab the resource root entity
                    CClientEntity* pRoot = pResource->GetResourceDFFRoot();

                    // Create a DFF element
                    CClientDFF* pDFF = new CClientDFF(m_pManager, INVALID_ELEMENT_ID);

                    // Try to load the DFF file
                    if (pDFF->LoadDFF(bIsRawData ? strFile : strPath, bIsRawData))
                    {
                        // Success loading the file. Set parent to DFF root
                        pDFF->SetParent(pRoot);

                        if (strModelName != NULL)
                        {
                            ushort usModelID = CModelNames::ResolveModelID(strModelName);
                            if (usModelID != INVALID_MODEL_ID)
                            {
                                pDFF->uimodel = usModelID;
                            }
                            pDFF->strModelName = strModelName;
                        }
                        // Return the DFF
                        lua_pushelement(luaVM, pDFF);
                        return 1;
                    }
                    else
                    {
                        // Delete it again
                        delete pDFF;
                        argStream.SetCustomError(bIsRawData ? "raw data" : strFile, "Error loading DFF");
                    }
                }
                else
                    argStream.SetCustomError(bIsRawData ? "raw data" : strFile, "Bad file path");
            }
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // We failed
    lua_pushboolean(luaVM, false);
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
    ushort usModel = 0;
    CScriptArgReader argStream ( luaVM );
    // Grab the COL and model ID
    argStream.ReadUserData ( pCol );
    if (argStream.NextIsNumber())
    {
        argStream.ReadNumber(usModel);
    }
    else
    {
        usModel = pCol->usModel;
    }

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
        ushort usModelID = CModelNames::ResolveModelID ( strModelName );

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
    if (argStream.NextIsBool())
    {
        argStream.ReadBool(bAlphaTransparency, false);
    }
    else
    {
        argStream.ReadString(strModelName, "");
        argStream.ReadBool(bAlphaTransparency, false);
    }

    if (!argStream.HasErrors())
    {
        ushort usModelID = INVALID_MODEL_ID;
        if (pDFF->strModelName != "")
        {
            usModelID = CModelNames::ResolveModelID(pDFF->strModelName);
        }
        else
        {
            usModelID = CModelNames::ResolveModelID(strModelName);
        }
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
    ushort usFrameId;
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
                ushort framesCount = 1;
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
                    lua_pushnumber(luaVM, (ushort)pFrame->child);
                    lua_settable(luaVM, -3);
                }
                if (pFrame->next != NULL)
                {
                    lua_pushstring(luaVM, "next");
                    lua_pushnumber(luaVM, (ushort)pFrame->next);
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
    CClientDFF* pDFF;
    int iType;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(iType);

    if (!argStream.HasErrors())
    {
        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpLight* newLight = CClientDFF::CreateLight(iType);
                newLight->color.r = 255;
                newLight->color.g = 0;
                newLight->color.b = 0;
                newLight->color.a = 255;
                newLight->frame = 0;
                newLight->radius = 5;
                CClientDFF::ClumpAddLight(pClump, newLight);
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

int CLuaEngineDefs::EngineDFFGetProperties(lua_State* luaVM)
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

                lua_pushstring(luaVM, "morphTargetCount");
                lua_pushnumber(luaVM, pGeometry->morphTarget_size);
                lua_settable(luaVM, -3);

                /*lua_pushstring(luaVM, "meshCount");
                lua_pushnumber(luaVM, pGeometry->header->numMeshes);
                lua_settable(luaVM, -3);

                */  // same what materialsCount

                lua_pushstring(luaVM, "texCoordSetsCount");
                lua_pushnumber(luaVM, pGeometry->texcoords_size);
                lua_settable(luaVM, -3);

                /*lua_pushstring(luaVM, "framesCount");
                ushort framesCount = 1;
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
                
                lua_pushstring(luaVM, "atomics");
                lua_pushnumber(luaVM, CClientDFF::ClumpGetNumAtomics(pClump));
                lua_settable(luaVM, -3);
                */

                lua_pushstring(luaVM, "flags");
                lua_pushnumber(luaVM, pGeometry->flags);
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

int CLuaEngineDefs::EngineDFFGetBoundingBox(lua_State* luaVM)
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

                CVector vecMin;
                CVector vecMax;
                for (ushort i = 0; i < pGeometry->vertices_size; i++)
                {
                    RwV3d vVert = pGeometry->morphTarget->verts[i];
                    if (vVert.x < vecMin.fX)
                        vecMin.fX = vVert.x;
                    if (vVert.y < vecMin.fY)
                        vecMin.fZ = vVert.y;
                    if (vVert.z < vecMin.fZ)
                        vecMin.fZ = vVert.z;

                    if (vVert.x > vecMax.fX)
                        vecMax.fX = vVert.x;
                    if (vVert.y > vecMax.fY)
                        vecMax.fZ = vVert.y;
                    if (vVert.z > vecMax.fZ)
                        vecMax.fZ = vVert.z;
                }

                lua_newtable(luaVM);

                lua_pushstring(luaVM, "radius");
                lua_pushnumber(luaVM, pAtomic->bsphereLocal.radius);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "center");
                lua_pushvector(luaVM, pAtomic->bsphereLocal.position.getVector());
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "min");
                lua_pushvector(luaVM, vecMin);
                lua_settable(luaVM, -3);

                lua_pushstring(luaVM, "max");
                lua_pushvector(luaVM, vecMax);
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
    ushort uiMaterialId = NULL;
    ushort uiMaterialR = NULL;
    ushort uiMaterialG = NULL;
    ushort uiMaterialB = NULL;
    ushort uiMaterialA = NULL;

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
                if (uiMaterialId > pGeometry->header->numMeshes-1) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh* m = &pGeometry->header->getMeshes()[uiMaterialId]; // example textures 0-5 in mta are 1-6
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
    ushort uiTextureId = NULL;
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
                if (!pGeometry->header->isValidMeshId(uiTextureId)) {
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

int CLuaEngineDefs::EngineDFFGetTextureProperties(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort uiTextureId = NULL;
    SString sPropertiesName;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiTextureId);
    argStream.ReadString(sPropertiesName);

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
                if (!pGeometry->header->isValidMeshId(uiTextureId)) {
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
                    lua_pushnumber(luaVM, material->texture->raster->u);
                    return 1;
                }
                else if (sPropertiesName == "v")
                {
                    lua_pushnumber(luaVM, material->texture->raster->v);
                    return 1;
                }
                else if (sPropertiesName == "width")
                {
                    lua_pushnumber(luaVM, material->texture->raster->width);
                    return 1;
                }
                else if (sPropertiesName == "height")
                {
                    lua_pushnumber(luaVM, material->texture->raster->height);
                    return 1;
                }
                else if (sPropertiesName == "format")
                {
                    lua_pushnumber(luaVM, material->texture->raster->format);
                    return 1;
                }
                else if (sPropertiesName == "pixels")
                {
                    lua_pushstring(luaVM, (char *)material->texture->raster->pixels);
                    return 1;
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

int CLuaEngineDefs::EngineDFFSetTexture(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort uiMaterialId = NULL;
    CClientTXD* pTXD = NULL;
    ushort textureId = NULL;
    SString sName;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(uiMaterialId);
    argStream.ReadUserData(pTXD);
    argStream.ReadNumber(textureId);

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
                textureId--;
                if ( !pGeometry->header->isValidMeshId(uiMaterialId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMaterial* material = pGeometry->materials.materials[uiMaterialId];
                RpMaterial* material2 = pGeometry->header->getMeshes()[uiMaterialId].material;
                if (pTXD == NULL)
                {
                    material->texture = NULL;
                    material2->texture = NULL;
                    pTXD->RestreamModel(usModelID);
                    lua_pushboolean(luaVM, true);
                    return 1;
                }
                else
                {
                    std::vector< RwTexture* > textures = pTXD->m_ReplacementTextures.textures;
                    if (textureId >= 0 && textureId <= textures.size())
                    {
                        RwTexture* texture = textures.at(textureId);
                        material->texture = texture;
                        material2->texture = texture;
                        pTXD->RestreamModel(usModelID);
                        lua_pushboolean(luaVM, true);
                        return 1;
                    }
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

int CLuaEngineDefs::EngineDFFGetMaterialProperties(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort uiMaterialId = NULL;

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
                if (!pGeometry->header->isValidMeshId(uiMaterialId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh m = pGeometry->header->getMeshes()[uiMaterialId];
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
    ushort uiMaterialId = NULL;
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
                if (uiMaterialId > pGeometry->header->numMeshes - 1) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh* m = &pGeometry->header->getMeshes()[uiMaterialId]; // example textures 0-5 in mta are 1-6
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
    ushort uiMaterialId = NULL;
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
                if (uiMaterialId > pGeometry->header->numMeshes - 1) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RpMesh* m = &pGeometry->header->getMeshes()[uiMaterialId];

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
                    ushort usMeshId = NULL;
                    argStream.ReadNumber(usMeshId);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    if (!pGeometry->header->isValidMeshId(usMeshId))
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    RpMesh* mesh = pGeometry->header->getMeshes();
                    CClientDFF::GetVerticesInMesh(luaVM, &mesh[usMeshId-1]);
                    return 1;
                }
                else if (sSelectType == "*")
                {
                    CClientDFF::GetVertices(luaVM, pGeometry);
                    return 1;
                }
                else if (sSelectType == "inRange")
                {
                    CVector vecPosition;
                    float fRange = NULL;
                    argStream.ReadVector3D(vecPosition);
                    argStream.ReadNumber(fRange);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    CClientDFF::GetVerticesInRange(luaVM, pGeometry, vecPosition, fRange);
                    return 1;
                }
                else if (sSelectType == "nearest3d")
                {
                    CVector vecPosition;
                    argStream.ReadVector3D(vecPosition);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    CClientDFF::GetVertexNeares3d(luaVM, pGeometry, vecPosition);

                    return 1;
                }
                else if (sSelectType == "betweenPosition2d")
                {
                    CVector2D vPositionA, vPositionB;
                    argStream.ReadVector2D(vPositionA);
                    argStream.ReadVector2D(vPositionB);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    lua_newtable(luaVM);
                    ushort next = 0;
                    for ( ushort i = 0; i < pGeometry->vertices_size; i++)
                    {
                        RwV3d vert = pGeometry->morphTarget->verts[i];
                        if (vPositionA.fX < vert.x && vPositionA.fY < vert.y && vPositionB.fX > vert.x && vPositionB.fY > vert.y)
                        {
                            lua_pushnumber(luaVM, ++next);
                            lua_pushnumber(luaVM, i + 1);
                            lua_settable(luaVM, -3);
                        }
                    }
                    return 1;
                }
                else if (sSelectType == "betweenPosition3d")
                {
                    CVector vPositionA, vPositionB;
                    argStream.ReadVector3D(vPositionA);
                    argStream.ReadVector3D(vPositionB);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    lua_newtable(luaVM);
                    ushort next = 0;
                    for (ushort i = 0; i < pGeometry->vertices_size; i++)
                    {
                        RwV3d vert = pGeometry->morphTarget->verts[i];
                        if (vPositionA.fX < vert.x && vPositionA.fY < vert.y && vPositionA.fZ < vert.z && vPositionB.fX > vert.x && vPositionB.fY > vert.y && vPositionA.fZ > vert.z)
                        {
                            lua_pushnumber(luaVM, ++next);
                            lua_pushnumber(luaVM, i + 1);
                            lua_settable(luaVM, -3);
                        }
                    }
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

int CLuaEngineDefs::EngineDFFGetMeshInfo(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort uMeshId = NULL;
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
                if (uMeshId != NULL && uMeshId <= pGeometry->header->numMeshes)
                {
                    RpMesh* mesh = pGeometry->header->getMeshes();
                    ushort meshCount = pGeometry->header->numMeshes;
                    if (pGeometry->header->isValidMeshId(uMeshId))
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

int CLuaEngineDefs::EngineDFFCreateVertex(lua_State* luaVM)
{
    CClientDFF* pDFF;
    CVector vecPosition;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadVector3D(vecPosition);

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
                CClientDFF::CreateVertex(pGeometry, vecPosition);
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
    ushort usVertexId;
    float u,v;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertexId);
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
                usVertexId--;
                if (!pGeometry->isValidVertexId(usVertexId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwTextureCoordinates* vVert = &pGeometry->texcoords[0][usVertexId];

                if (vVert == NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                vVert->u = u;
                vVert->v = v;
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

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

int CLuaEngineDefs::EngineDFFSetVertexLight(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort usVertex;
    ushort r, g, b, a;
    bool blend;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertex);
    argStream.ReadNumber(r);
    argStream.ReadNumber(g);
    argStream.ReadNumber(b);
    argStream.ReadNumber(a);
    argStream.ReadBool(blend, false);

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
                if (!pGeometry->isFlag(RpGeometryFlag::rpGEOMETRYPRELIT))
                {
                    if (!CClientDFF::EnableVerticesLighting(pGeometry))
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                }
                usVertex--;
                if (!pGeometry->isValidVertexId(usVertex)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwColor* vertColor = &pGeometry->colors[usVertex];

                if (vertColor == NULL)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (blend)
                {
                    r += vertColor->r;
                    g += vertColor->g;
                    b += vertColor->b;
                    a += vertColor->a;
                }
                
                vertColor->r = clamp(r, 0, 255);
                vertColor->g = clamp(g, 0, 255);
                vertColor->b = clamp(b, 0, 255);
                vertColor->a = clamp(a, 0, 255);
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

int CLuaEngineDefs::EngineDFFGetVertexLight(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertex);

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
                if ( !pGeometry->isFlag(RpGeometryFlag::rpGEOMETRYPRELIT) )
                {
                    lua_pushnumber(luaVM, 0);
                    lua_pushnumber(luaVM, 0);
                    lua_pushnumber(luaVM, 0);
                    lua_pushnumber(luaVM, 0);
                    return 4;
                }

                usVertex--;
                if (!pGeometry->isValidVertexId(usVertex)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwColor vertColor = pGeometry->colors[usVertex];

                lua_pushnumber(luaVM, vertColor.r);
                lua_pushnumber(luaVM, vertColor.g);
                lua_pushnumber(luaVM, vertColor.b);
                lua_pushnumber(luaVM, vertColor.a);
                return 4;
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

int CLuaEngineDefs::EngineDFFGetVertexUV(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort usVertexId;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertexId);

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
                if (!pGeometry->isValidVertexId(usVertexId)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                usVertexId--;
                RwTextureCoordinates* vVert = &pGeometry->texcoords[0][usVertexId];
                lua_pushnumber(luaVM, vVert->u);
                lua_pushnumber(luaVM, vVert->v);
                return 2;
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
    ushort usVertex;
    CVector pos;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertex);
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
                usVertex--;
                if (!pGeometry->isValidVertexId(usVertex)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                RwV3d* vVert = &pGeometry->morphTarget->verts[usVertex];
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

int CLuaEngineDefs::EngineDFFGetVertexPosition(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertex);

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
                if (!pGeometry->isValidVertexId(usVertex)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                usVertex--;
                RwV3d* vVert = &pGeometry->morphTarget->verts[usVertex];
                lua_pushnumber(luaVM, vVert->x);
                lua_pushnumber(luaVM, vVert->y);
                lua_pushnumber(luaVM, vVert->z);
                return 3;
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
    ushort uiPolygonId;
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
                if (!pGeometry->isValidTriangleId(uiPolygonId))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uiPolygonId--;
                CClientDFF::SetPolygonPosition(pGeometry, uiPolygonId, vNewPosition);
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
    ushort usPolygon;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usPolygon);

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
                if (pGeometry->isValidTriangleId(usPolygon))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                usPolygon--;
                CVector vecPosition = CClientDFF::GetPolygonPosition(pGeometry, usPolygon);
                lua_pushnumber(luaVM, vecPosition.fX);
                lua_pushnumber(luaVM, vecPosition.fY);
                lua_pushnumber(luaVM, vecPosition.fZ);
                return 3;
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
    ushort usPolygon = NULL;
    ushort vertex1, vertex2, vertex3;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usPolygon);
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

                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                if (!pGeometry->isValidTriangleId(usPolygon))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (vertex1 == vertex2 || vertex1 == vertex3 || vertex2 == vertex3) // prevent set vertices like 1,2,2 - this make no sens
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (!pGeometry->isValidVertexId(vertex1) || !pGeometry->isValidVertexId(vertex2) || !pGeometry->isValidVertexId(vertex3))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                usPolygon--;
                vertex1--;
                vertex2--;
                vertex3--;
                bool result = CClientDFF::SetPolygonVertices(pGeometry, usPolygon, vertex1, vertex2, vertex3);
                lua_pushboolean(luaVM, result);
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
    ushort uiPolygon = NULL;
    ushort uiMaterialId = NULL;

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
                    RpTriangle* pTriangle = &pGeometry->triangles[uiPolygon];
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
    ushort uTriangleId = NULL;
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
                ushort meshId = CClientDFF::GetMeshIdFromPolygonId(pGeometry, uTriangleId);
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

int CLuaEngineDefs::EngineDFFGetPolygonVertices(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort uTriangleId = NULL;
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
                if (!pGeometry->isValidTriangleId(uTriangleId))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                uTriangleId--;
                RpTriangle pTriangle = pGeometry->triangles[uTriangleId];
                lua_pushnumber(luaVM, pTriangle.v[0]);
                lua_pushnumber(luaVM, pTriangle.v[1]);
                lua_pushnumber(luaVM, pTriangle.v[2]);
                return 3;
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

int CLuaEngineDefs::EngineDFFSetPolygonMesh(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort usTriangle = NULL;
    ushort usMesh = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usTriangle);
    argStream.ReadNumber(usMesh);
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
                if (!pGeometry->isValidTriangleId(usTriangle))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                usTriangle--;
                RpTriangle pTriangle = pGeometry->triangles[usTriangle];
                CClientDFF::GeometryDestroyPolygon(pGeometry, usTriangle);
                CClientDFF::CreatePolygon(pGeometry, pTriangle.v[2], pTriangle.v[1], pTriangle.v[0], usMesh);
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

int CLuaEngineDefs::EngineDFFDestroyPolygon(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort uiTriangleId;
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

int CLuaEngineDefs::EngineDFFCreateMesh(lua_State* luaVM)
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
                ushort usMesh = CClientDFF::CreateMesh(pGeometry);
                if (usMesh == 0)
                {
                    lua_pushboolean(luaVM, false);
                }
                else
                {
                    lua_pushnumber(luaVM, usMesh);
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

int CLuaEngineDefs::EngineDFFCreatePolygon(lua_State* luaVM)
{
    CClientDFF* pDFF;
    ushort vertex1, vertex2, vertex3, usMesh;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(vertex1);
    argStream.ReadNumber(vertex2);
    argStream.ReadNumber(vertex3);
    argStream.ReadNumber(usMesh, 1);
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
                if (vertex1 == vertex2 || vertex1 == vertex3 || vertex2 == vertex3)
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (!pGeometry->isValidVertexId(vertex1) || !pGeometry->isValidVertexId(vertex2) || !pGeometry->isValidVertexId(vertex3))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                vertex1--;
                vertex2--;
                vertex3--;
                usMesh--;
                bool result = CClientDFF::CreatePolygon(pGeometry, vertex1, vertex2, vertex3, usMesh);

                if (result)
                    lua_pushnumber(luaVM, pGeometry->triangles_size);
                else
                    lua_pushboolean(luaVM, false);

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
    ushort usVertex = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertex);

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
                usVertex--;
                if ( !pGeometry->isValidVertexId(usVertex) ) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                CClientDFF::GeometryDestroyVertex(pGeometry, usVertex);
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
    ushort usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadNumber(usVertex);

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
                usVertex--;
                if (!pGeometry->isValidVertexId(usVertex)) {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                std::vector < ushort > vecPolygons = CClientDFF::GetPolygonsUsedByVertex(pGeometry, usVertex);
                lua_newtable(luaVM);
                for (ushort i = 0; i < vecPolygons.size(); i++)
                {
                        lua_pushnumber(luaVM, i + 1);
                        lua_pushnumber(luaVM, vecPolygons.at(i) );
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

int CLuaEngineDefs::EngineDFFUseVerticesTool(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString strTool;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(strTool);
    std::vector< ushort > vertices;
    argStream.ReadNumberTable(vertices);

    sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

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
                for (ushort i = 0; i < vertices.size(); i++)
                {
                    if (!pGeometry->isValidVertexId(vertices.at(i)))
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                }

                if (strTool == "remove")
                {

                    lua_pushboolean(luaVM, true);
                    return 1;
                }
                else if (strTool == "makeplanear")
                {
                    SString axis;
                    argStream.ReadString(axis);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    bool result = CClientDFF::VerticesToolMakePlanear(luaVM, pGeometry, vertices, axis);
                    lua_pushboolean(luaVM, result);
                    return 1;
                }
                lua_pushboolean(luaVM, false);
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

int CLuaEngineDefs::EngineDFFUsePolygonsTool(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString strTool;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(strTool);
    std::vector< ushort > polygons;
    argStream.ReadNumberTable(polygons);

    sort(polygons.begin(), polygons.end());
    polygons.erase(unique(polygons.begin(), polygons.end()), polygons.end());

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
                for (ushort i = 0; i < polygons.size(); i++)
                {
                    if (!pGeometry->isValidTriangleId(polygons.at(i)))
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                }

                if (strTool == "remove")
                {
                    lua_pushboolean(luaVM, true);
                    return 1;
                }
                lua_pushboolean(luaVM, false);
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

CVector RotatePointAroundAxis(const CVector& axis, const float radians, const CVector& point)
{
    float matrix[3][3];

    float sn = sinf(radians);
    float cs = cosf(radians);

    float xSin = axis.fX * sn;
    float ySin = axis.fY * sn;
    float zSin = axis.fZ * sn;
    float oneMinusCS = 1.0f - cs;
    float xym = axis.fX * axis.fY * oneMinusCS;
    float xzm = axis.fX * axis.fZ * oneMinusCS;
    float yzm = axis.fY * axis.fZ * oneMinusCS;

    matrix[0][0] = (axis.fX * axis.fX) * oneMinusCS + cs;
    matrix[0][1] = xym + zSin;
    matrix[0][2] = xzm - ySin;
    matrix[1][0] = xym - zSin;
    matrix[1][1] = (axis.fY * axis.fY) * oneMinusCS + cs;
    matrix[1][2] = yzm + xSin;
    matrix[2][0] = xzm + ySin;
    matrix[2][1] = yzm - xSin;
    matrix[2][2] = (axis.fZ * axis.fZ) * oneMinusCS + cs;
    CVector point3D;

    
    point3D.fX = matrix[0][0] * point.fX + matrix[0][1] * point.fY + matrix[0][2] * point.fZ;

    point3D.fY = matrix[1][0] * point.fX + matrix[1][1] * point.fY + matrix[1][2] * point.fZ;

    point3D.fZ = matrix[2][0] * point.fX + matrix[2][1] * point.fY + matrix[2][2] * point.fZ;
    return point3D;
}

int CLuaEngineDefs::EngineDFFTransformVertices(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString strTransform;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(strTransform);
    std::vector< ushort > vertices;
    argStream.ReadNumberTable(vertices);
    if (!argStream.HasErrors())
    {
        if (vertices.empty())
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }

        sort(vertices.begin(), vertices.end());
        vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

        ushort usModelID = pDFF->uimodel;
        if (usModelID != INVALID_MODEL_ID)
        {
            RpClump* pClump = pDFF->GetLoadedClump(usModelID);
            if (pClump)
            {
                RpAtomic* pAtomic = pClump->getAtomic();
                RpGeometry* pGeometry = pAtomic->geometry;
                ushort usMaxVert = pGeometry->vertices_size;
                for (int i = 0; i < vertices.size(); i++)   // check did vertices are fine and descress once
                {
                    ushort id = vertices.at(i);
                    id--;
                    vertices[i] = id;
                    if (id < 0 || id > usMaxVert)
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                }
                if (strTransform == "move")
                {
                    CVector move;
                    argStream.ReadVector3D(move);
                    if (argStream.HasErrors())
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    pDFF->TransformMove(vertices, move);
                    lua_pushboolean(luaVM, true);
                    return 1;
                }
                else if (strTransform == "rotation")
                {
                    CVector rotation;
                    argStream.ReadVector3D(rotation);
                    if (argStream.HasErrors())
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    CVector point;
                    lua_pushvector(luaVM, RotatePointAroundAxis(rotation, 1, point));
                    return 1;
                }
                else if (strTransform == "scale")
                {
                    CVector scale;
                    argStream.ReadVector3D(scale);
                    if (argStream.HasErrors())
                    {
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    pDFF->TransformScale(vertices, scale);
                    lua_pushboolean(luaVM, true);
                    return 1;
                }

                lua_pushboolean(luaVM, false);
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

int CLuaEngineDefs::EngineDFFCreateObject(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString strObject;
    ushort usMesh;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(strObject);
    argStream.ReadNumber(usMesh);
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
                usMesh--;
                if (!pGeometry->header->isValidMeshId(usMesh))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                if (strObject == "plane")
                {
                    CVector2D vecStart, vecEnd;
                    ushort usSegmentLenght, usSegmentWidth;
                    float fHeight;
                    argStream.ReadVector2D(vecStart);
                    argStream.ReadVector2D(vecEnd);
                    argStream.ReadNumber(fHeight);
                    argStream.ReadNumber(usSegmentLenght);
                    argStream.ReadNumber(usSegmentWidth);
                    if (argStream.HasErrors())
                    {
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    if (vecEnd.fX < vecStart.fX || vecEnd.fY < vecStart.fY)
                    {
                        argStream.SetCustomError("End vector, x and y should be bigger then start vector.");
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    if (usSegmentLenght * usSegmentWidth > 32768)
                    {
                        argStream.SetCustomError("Too meny segments, segments lenght * segmnets width should be less than 32768.");
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    if (usSegmentLenght < 2 || usSegmentWidth < 2)
                    {
                        argStream.SetCustomError("Not enough segments, minimum lenght 2 and width 2.");
                        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                        lua_pushboolean(luaVM, false);
                        return 1;
                    }
                    bool ret = CClientDFF::CreateObjectPlane(pGeometry, usMesh, vecStart.fX, vecStart.fY, vecEnd.fX, vecEnd.fY, fHeight, usSegmentLenght, usSegmentWidth);
                    lua_pushboolean(luaVM, true);
                    lua_pushboolean(luaVM, ret);
                    return 2;
                }

                lua_pushboolean(luaVM, false);
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
int CLuaEngineDefs::EngineDFFTransformPolygons(lua_State* luaVM)
{
    CClientDFF* pDFF;
    SString strTransform;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pDFF);
    argStream.ReadString(strTransform);
    std::vector< int > vertices;
    argStream.ReadNumberTable(vertices);
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
                if (strTransform == "move")
                {
                    lua_pushboolean(luaVM, true);
                    return 1;
                }

                lua_pushboolean(luaVM, false);
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
    ushort usModelID = CModelNames::ResolveModelID ( lua_tostring ( luaVM, 1 ) );

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
        ushort usModelID = CModelNames::ResolveModelID ( strModel );
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
            for ( ushort i = 0 ; i < nameList.size () ; i++ )
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
            for ( ushort i = 0 ; i < nameList.size () ; i++ )
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
        lua_newtable(luaVM);
        lua_pushstring(luaVM, "polygonsCount");
        lua_pushnumber(luaVM, pCOL->GetModelPolygonCount());
        lua_settable(luaVM, -3);
        lua_pushstring(luaVM, "verticesCount");
        lua_pushnumber(luaVM, pCOL->GetModelVerticesCount());
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
    ushort usSurfaceId, usVertex;
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
    ushort usVertex;
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
    ushort usPolygon;
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
        CVector position = pCOL->GetTrianglePosition(usPolygon);
        lua_pushvector(luaVM, position);
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
    ushort usVertex;
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
    ushort usPolygon;
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
        ushort vertex1 = NULL;
        ushort vertex2 = NULL;
        ushort vertex3 = NULL;
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
    ushort usPolygon, usVertex1, usVertex2, usVertex3;
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
    ushort usPolygon;
    CVector position;
    ushort day, night=NULL;
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
    ushort vertex1, vertex2, vertex3;
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
        ushort usPolygon = pCOL->CreatePolygon(vertex1, vertex2, vertex3);
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
    ushort usPolygon;
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
        ushort usVertex = pCOL->CreateVertex(vecPosition);
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
    ushort usVertex;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadNumber(usVertex);

    if (!argStream.HasErrors())
    {
        if (usVertex < 0 && usVertex > pCOL->GetModelVerticesCount())
        {
            lua_pushboolean(luaVM, false);
            return 1;
        }
        usVertex--;
        bool result = pCOL->DestroyVertex(usVertex);
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

int CLuaEngineDefs::EngineCOLCreateEmptyCollision(lua_State* luaVM)
{
    SString strFile = "";
    ushort usModel;
    CScriptArgReader argStream(luaVM);
    // Grab the COL filename or data
    argStream.ReadNumber(usModel);

    if (!argStream.HasErrors())
    {
        // Grab the lua main and the resource belonging to this script
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            // Get the resource we belong to
            CResource* pResource = pLuaMain->GetResource();
            if (pResource)
            {
                SString strEmptyBase64 = "Q09MM3wAAABiYXNlAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAXt1G4F7dRuBe3UbgAAAAAAAAAAAAAAAASAAAAAAAAAAAAAAAAAAAAdAAAAHoAAAAAAAAAAAAAAHoAAACAAAAAAAAAAAAAAAAAAAAA";
                SString strFile = SharedUtil::Base64decode(strEmptyBase64);
                bool bIsRawData = CClientColModel::IsCOLData(strFile);
                SString strPath;
                // Is this a legal filepath?
                if (bIsRawData || CResourceManager::ParseResourcePathInput(strFile, pResource, &strPath))
                {
                    // Grab the resource root entity
                    CClientEntity* pRoot = pResource->GetResourceCOLModelRoot();

                    // Create the col model
                    CClientColModel* pCol = new CClientColModel(m_pManager, INVALID_ELEMENT_ID);

                    // Attempt loading the file
                    if (pCol->LoadCol(bIsRawData ? strFile : strPath, bIsRawData))
                    {
                        // Success. Make it a child of the resource collision root
                        pCol->SetParent(pRoot);
                        pCol->usModel = usModel;
                        // Return the created col model
                        lua_pushelement(luaVM, pCol);
                        return 1;
                    }
                    else
                    {
                        // Delete it again. We failed
                        delete pCol;
                        argStream.SetCustomError(bIsRawData ? "raw data" : strFile, "Error loading COL");
                    }
                }
                else
                    argStream.SetCustomError(bIsRawData ? "raw data" : strFile, "Bad file path");
            }
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // We failed for some reason
    lua_pushboolean(luaVM, false);
    return 1;
}


int CLuaEngineDefs::EngineCOLSelectVertices(lua_State* luaVM)
{
    /*
    CClientColModel* pCOL;
    ushort usPolygon;
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
        ushort vertex1 = NULL;
        ushort vertex2 = NULL;
        ushort vertex3 = NULL;
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

    lua_pushboolean(luaVM, false);*/
    return 1;
}

int CLuaEngineDefs::EngineCOLSelectPolygons(lua_State* luaVM)
{
    CClientColModel* pCOL;
    SString select;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pCOL);
    argStream.ReadString(select);

    if (!argStream.HasErrors())
    {
        if (select == "byMaterial")
        {
            ushort usMaterial;
            argStream.ReadNumber(usMaterial);
            if (argStream.HasErrors())
            {
                m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                lua_pushboolean(luaVM, false);
                return 1;
            }
            std::vector < CColTriangleSA > polygons = pCOL->GetAllPolygons();

            lua_newtable(luaVM);
            ushort next = 1;
            for (int i = 0; i < polygons.size(); i++)
            {
                if (polygons.at(i).material == usMaterial)
                {
                    lua_pushnumber(luaVM, next++);
                    lua_pushnumber(luaVM, i + 1);
                    lua_settable(luaVM, -3);
                }
            }
            return 1;
        }
        else if (select == "nearest3d")
        {
            ushort usMaterial;
            CVector vecPosition;
            bool findByPolygonPosition = false;
            if (argStream.NextIsVector3D())
            {
                argStream.ReadVector3D(vecPosition);
            }
            else
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }
            if (argStream.HasErrors())
            {
                m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                lua_pushboolean(luaVM, false);
                return 1;
            }
            std::vector < CColTriangleSA > polygons = pCOL->GetAllPolygons();

            lua_newtable(luaVM);
            float distance = 256; // bigger couse collision bugs
            ushort nearest = 0;
            ushort next = 1;
            for (int i = 0; i < polygons.size(); i++)
            {
                float dis = DistanceBetweenPoints3D(vecPosition, pCOL->GetTrianglePosition(i));
                if (distance > dis)
                {
                    nearest = i + 1;
                    distance = dis;
                }
            }
            lua_pushnumber(luaVM, nearest);
            return 1;
        }
        else if (select == "nearest2d")
        {
            ushort usMaterial;
            CVector2D vecPosition;
            bool findByPolygonPosition = false;
            if (argStream.NextIsVector2D())
            {
                argStream.ReadVector2D(vecPosition);
            }
            else
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }
            if (argStream.HasErrors())
            {
                m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                lua_pushboolean(luaVM, false);
                return 1;
            }
            std::vector < CColTriangleSA > polygons = pCOL->GetAllPolygons();

            lua_newtable(luaVM);
            float distance = 256; // bigger couse collision bugs
            ushort nearest = 0;
            ushort next = 1;
            for (int i = 0; i < polygons.size(); i++)
            {
                float dis = DistanceBetweenPoints2D(vecPosition, pCOL->GetTrianglePosition(i));
                if (distance > dis)
                {
                    nearest = i + 1;
                    distance = dis;
                }
            }
            lua_pushnumber(luaVM, nearest);
            return 1;
        }
        else if (select == "inRange")
        {
            ushort usMaterial;
            CVector vecPosition;
            float fRange;
            bool findByPolygonPosition = false;
            if (argStream.NextIsVector3D())
            {
                argStream.ReadVector3D(vecPosition);
            }
            else if (argStream.NextIsNumber())
            {
                ushort usPolygon;
                argStream.ReadNumber(usPolygon);
                if (pCOL->IsValidPolygonId(--usPolygon))
                {
                    vecPosition = pCOL->GetTrianglePosition(usPolygon);
                }
                else
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
            }
            else
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }
            if (argStream.HasErrors())
            {
                m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                lua_pushboolean(luaVM, false);
                return 1;
            }
            argStream.ReadNumber(fRange);
            if (fRange < 0)
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }

            std::vector < CColTriangleSA > polygons = pCOL->GetAllPolygons();

            lua_newtable(luaVM);
            ushort next = 1;
            for (int i = 0; i < polygons.size(); i++)
            {
                float dis = DistanceBetweenPoints2D(vecPosition, pCOL->GetTrianglePosition(i));
                if (fRange >= dis)
                {
                    lua_pushnumber(luaVM, next++);
                    lua_pushnumber(luaVM, i + 1);
                    lua_settable(luaVM, -3);
                }
            }
            return 1;
        }
        else if (select == "outRange")
        {
            ushort usMaterial;
            CVector vecPosition;
            float fRange;
            bool findByPolygonPosition = false;
            if (argStream.NextIsVector3D())
            {
                argStream.ReadVector3D(vecPosition);
            }
            else if (argStream.NextIsNumber())
            {
                ushort usPolygon;
                argStream.ReadNumber(usPolygon);
                if (pCOL->IsValidPolygonId(--usPolygon))
                {
                    vecPosition = pCOL->GetTrianglePosition(usPolygon);
                }
                else
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
            }
            else
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }
            if (argStream.HasErrors())
            {
                m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
                lua_pushboolean(luaVM, false);
                return 1;
            }
            argStream.ReadNumber(fRange);
            if (fRange < 0)
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }

            std::vector < CColTriangleSA > polygons = pCOL->GetAllPolygons();

            lua_newtable(luaVM);
            ushort next = 1;
            for (int i = 0; i < polygons.size(); i++)
            {
                float dis = DistanceBetweenPoints2D(vecPosition, pCOL->GetTrianglePosition(i));
                if (fRange <= dis)
                {
                    lua_pushnumber(luaVM, next++);
                    lua_pushnumber(luaVM, i + 1);
                    lua_settable(luaVM, -3);
                }
            }
            return 1;
        }
        else if (select == "element")
        {
            ushort usPolygon;
            argStream.ReadNumber(usPolygon);
            usPolygon--;
            if (!pCOL->IsValidPolygonId(usPolygon))
            {
                lua_pushboolean(luaVM, false);
                return 1;
            }
            else
            {
                if (pCOL->SelectElement(luaVM, usPolygon))
                    return 1;
            }
        }
        else if (select == "grow")
        {
            ushort usPolygon;
            lua_newtable(luaVM);
            ushort usNext = 0;
            while (argStream.NextIsNumber())
            {
                argStream.ReadNumber(usPolygon);
                usPolygon--;
                if (!pCOL->IsValidPolygonId(usPolygon))
                {
                    lua_pushboolean(luaVM, false);
                    return 1;
                }
                pCOL->Grow(luaVM, usPolygon, usNext);
            }
            return 1;
        }
        else if (select == "shrink")
        {

        }
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
    ushort textureId=NULL;
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
    CClientTXD* pTXD = NULL;
    ushort textureId = NULL;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTXD);
    argStream.ReadNumber(textureId);

    if (!argStream.HasErrors())
    {
        std::vector< RwTexture* > textures = pTXD->m_ReplacementTextures.textures;
        if (textureId > NULL && textureId <= textures.size())
        {
            RwTexture* texture = textures.at(textureId);
            unsigned char pixels1 = texture->raster->pixels[0];
            unsigned char pixels2 = texture->raster->pixels[1];
            unsigned char pixels3 = texture->raster->pixels[2];
            unsigned char pixels4 = texture->raster->pixels[3];
            abort();
            lua_pushstring(luaVM, "ASDF");
            return 1;
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}