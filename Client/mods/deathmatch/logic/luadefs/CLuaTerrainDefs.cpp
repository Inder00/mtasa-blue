/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/luadefs/CLuaColShapeDefs.cpp
*  PURPOSE:     Lua definitions class
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include "StdInc.h"

void CLuaTerrainDefs::LoadFunctions(void)
{
    CLuaCFunctions::AddFunction("createTerrain", CreateTerrain);
    //CLuaCFunctions::AddFunction("terrainDeform", TerrainDeform);
    //CLuaCFunctions::AddFunction("terrainPaint", TerrainPaint);
    //CLuaCFunctions::AddFunction("terrainBuild", TerrainBuild);
    //CLuaCFunctions::AddFunction("terrainGetPreview", TerrainGetPreview);
}

void CLuaTerrainDefs::AddClass(lua_State* luaVM)
{
    lua_newclass(luaVM);

    //lua_classfunction(luaVM, "Circle", "createColCircle");
    //lua_classvariable(luaVM, "shapeType", nullptr, "getColShapeType");

    lua_registerclass(luaVM, "Terrain", "Element");
}

int CLuaTerrainDefs::CreateTerrain(lua_State* luaVM)
{
    // element terrain = createTerrain( float sizeX, float sizeY, int meshDensity, string meshType, table textures, table modelsIDs [, string defaultTexture ] )
    CVector2D        vecSize;
    ushort           sMeshDensity;
    SString          StrMeshType;
    // textures
    // modelsIDs
    SString         defaultTexture;
    CScriptArgReader argStream(luaVM);
    argStream.ReadVector2D(vecSize);
    argStream.ReadNumber(sMeshDensity);
    argStream.ReadString(StrMeshType, "default");

    if (!argStream.HasErrors())
    {
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            CResource* pResource = pLuaMain->GetResource();
            if (pResource)
            {
                // Create it and return it
                CClientTerrain* pTerrain = CStaticFunctionDefinitions::CreateTerrain(*pResource);
                /*if (pTerrain)
                {
                    CElementGroup* pGroup = pResource->GetElementGroup();
                    if (pGroup)
                    {
                        pGroup->Add(pTerrain);
                    }
                    lua_pushelement(luaVM, pTerrain);
                    return 1;
                }*/
            }
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}
