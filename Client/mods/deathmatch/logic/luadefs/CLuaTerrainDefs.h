/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/luadefs/CLuaTerrainDefs.h
*  PURPOSE:     Lua definitions class
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#pragma once
#include "CLuaDefs.h"

class CLuaTerrainDefs : public CLuaDefs
{
public:
    static void LoadFunctions(void);
    static void AddClass(lua_State* luaVM);

    LUA_DECLARE(CreateTerrain);
    LUA_DECLARE(TerrainDeform);
    LUA_DECLARE(TerrainPaint);
    LUA_DECLARE(TerrainBuild);
    LUA_DECLARE(TerrainGetPreview);
};
