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

#pragma once
#include "CLuaDefs.h"

class CLuaEngineDefs : public CLuaDefs
{
public:
    static void LoadFunctions ( void );
    static void AddClass ( lua_State* luaVM );

    LUA_DECLARE ( EngineLoadDFF );
    LUA_DECLARE ( EngineLoadTXD );
    LUA_DECLARE ( EngineLoadCOL );
    LUA_DECLARE ( EngineImportTXD );
    LUA_DECLARE ( EngineReplaceCOL );
    LUA_DECLARE ( EngineRestoreCOL );
    LUA_DECLARE ( EngineReplaceModel );
    LUA_DECLARE ( EngineRestoreModel );
    LUA_DECLARE ( EngineReplaceMatchingAtomics );
    LUA_DECLARE ( EngineReplaceWheelAtomics );
    LUA_DECLARE ( EnginePositionAtomic );
    LUA_DECLARE ( EnginePositionSeats );
    LUA_DECLARE ( EngineAddAllAtomics );
    LUA_DECLARE ( EngineReplaceVehiclePart );
    LUA_DECLARE ( EngineGetModelLODDistance );
    LUA_DECLARE ( EngineSetModelLODDistance );
    LUA_DECLARE ( EngineSetAsynchronousLoading );
    LUA_DECLARE ( EngineApplyShaderToWorldTexture );
    LUA_DECLARE ( EngineRemoveShaderFromWorldTexture );
    LUA_DECLARE ( EngineGetModelNameFromID );
    LUA_DECLARE ( EngineGetModelIDFromName );
    LUA_DECLARE ( EngineGetModelTextureNames );
    LUA_DECLARE ( EngineGetVisibleTextureNames );
    LUA_DECLARE(EngineDFFTEST);
    LUA_DECLARE(EngineDFFGetInfo);
    LUA_DECLARE(EngineDFFGetFrameInfo);
    LUA_DECLARE(EngineDFFGetPolygons);
    LUA_DECLARE(EngineDFFGetPolygonInfo);
    LUA_DECLARE(EngineDFFGetVertices);
    LUA_DECLARE(EngineDFFSetVertexPosition);
    LUA_DECLARE(EngineDFFGetMaterialInfo);
    LUA_DECLARE(EngineDFFDestroyVertex);
    LUA_DECLARE(EngineDFFSetPolygonVertices);
    LUA_DECLARE(EngineDFFSetCenter);
    LUA_DECLARE(EngineDFFSetPolygonMaterial);
    LUA_DECLARE(EngineDFFSetGeometry);
    LUA_DECLARE(EngineDFFToString);
    LUA_DECLARE(EngineDFFGetPolygonConnectedToVertex);
    LUA_DECLARE(EngineDFFDestroyPolygon);
    LUA_DECLARE(EngineDFFGetMeshInfo);
    LUA_DECLARE(EngineDFFSetMaterialColor);
    LUA_DECLARE(EngineDFFSetMaterialLighting);
    LUA_DECLARE(EngineDFFSetTextureName);
    LUA_DECLARE(EngineDFFAddTexture);
    LUA_DECLARE(EngineDFFFlipPolygon);
    LUA_DECLARE(EngineDFFCreatePolygon);
    LUA_DECLARE(EngineDFFSelectVertices);
    LUA_DECLARE(EngineDFFCreateVertex);
    LUA_DECLARE(EngineDFFGetPolygonPosition);
    LUA_DECLARE(EngineDFFSetPolygonPosition);
    LUA_DECLARE(EngineDFFSetInterpolation);
    LUA_DECLARE(EngineDFFGetPolygonMesh);
    LUA_DECLARE(EngineDFFCreateLight);
    LUA_DECLARE(EngineDFFSetVertexUV);
    LUA_DECLARE(EngineDFFSetTextureProperties);

    LUA_DECLARE(EngineCOLGetInfo);
    LUA_DECLARE(EngineCOLSetPolygonSurface);
    LUA_DECLARE(EngineCOLGetVertexPosition);
    LUA_DECLARE(EngineCOLSetVertexPosition);
    LUA_DECLARE(EngineCOLGetPolygonConnectedVertices);
    LUA_DECLARE(EngineCOLSetPolygonLighting);
    LUA_DECLARE(EngineCOLSetPolygonConnectedVertices);
    LUA_DECLARE(EngineCOLGetPolygonPosition);
    LUA_DECLARE(EngineCOLCreateVertex);
    LUA_DECLARE(EngineCOLCreatePolygon);
    LUA_DECLARE(EngineCOLDestroyVertex);
    LUA_DECLARE(EngineCOLDestroyPolygon);

    LUA_DECLARE(EngineTXDGetTexturesCount);
    LUA_DECLARE(EngineTXDGetTextureInfo);
    LUA_DECLARE(EngineTXDGetTexturePixels);

private: 
    static void AddEngineColClass ( lua_State* luaVM );
    static void AddEngineTxdClass ( lua_State* luaVM );
    static void AddEngineDffClass ( lua_State* luaVM );
};
