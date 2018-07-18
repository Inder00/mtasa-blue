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
#include "CClientTerrain.h"

void CLuaTerrainDefs::LoadFunctions(void)
{
    CLuaCFunctions::AddFunction("createTerrain", CreateTerrain);
    CLuaCFunctions::AddFunction("terrainDrawPreview", DrawPreview);
    CLuaCFunctions::AddFunction("terrainGetProperties", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainSelect", TerrainDeform);
    //CLuaCFunctions::AddFunction("terrainDeform", TerrainDeform);
    //CLuaCFunctions::AddFunction("terrainPaint", TerrainPaint);
    //CLuaCFunctions::AddFunction("terrainLightPaint", TerrainPaint);
    //CLuaCFunctions::AddFunction("terrainBuild", TerrainBuild);
    //CLuaCFunctions::AddFunction("terrainGetProperties", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainSave", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainLoad", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainAddRoad", TerrainGetPreview);
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
    // element terrain = createTerrain( float sizeX, float sizeY, int meshDensity, string meshType, table textures, table modelsIDs [, string defaultTexture = "grass" ] )
    CVector2D        vecSize;
    CVector2D        vecMeshDensity;
    SString          strMeshType;
    SString          strDefaultTexture;
    // textures
    // modelsIDs
    SString          StrMeshType;
    CScriptArgReader argStream(luaVM);
    argStream.ReadVector2D(vecSize);
    argStream.ReadVector2D(vecMeshDensity);
    argStream.ReadString(strMeshType);
    argStream.ReadString(strDefaultTexture, "grass");

    if (!argStream.HasErrors())
    {
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            CResource* pResource = pLuaMain->GetResource();
            if (pResource)
            {
                CClientTerrain* pTerrain = CStaticFunctionDefinitions::CreateTerrain(*pResource);
                if (pTerrain)
                {
                    CElementGroup* pGroup = pResource->GetElementGroup();
                    if (pGroup)
                    {
                        pGroup->Add(pTerrain);
                    }
                    pTerrain->SetMeshType(strMeshType);
                    pTerrain->SetDensity(vecMeshDensity);
                    pTerrain->SetSize(vecSize);
                    pTerrain->SetDefaultTexture(strDefaultTexture);
                    pTerrain->BuildMesh();
                    lua_pushelement(luaVM, pTerrain);
                    return 1;
                }
            }
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaTerrainDefs::DrawPreview(lua_State* luaVM)
{
    CClientTerrain* pTerrain;
    bool            bDrawVertices;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTerrain);
    argStream.ReadBool(bDrawVertices);

    if (!argStream.HasErrors())
    {
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            if (pTerrain)
            {
                pTerrain->DrawPreview(bDrawVertices);
                lua_pushboolean(luaVM, true);
                return 1;
            }
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaTerrainDefs::TerrainGetPreview(lua_State* luaVM)
{
    CClientTerrain* pTerrain;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTerrain);

    if (!argStream.HasErrors())
    {
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            if (pTerrain)
            {
                
                lua_pushstring(luaVM, pTerrain->GetMeshType());
                return 1;
            }
        }
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}
