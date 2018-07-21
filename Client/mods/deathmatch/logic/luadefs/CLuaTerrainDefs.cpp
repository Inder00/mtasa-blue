/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/luadefs/CLuaTerrainDefs.cpp
*  PURPOSE:     Lua definitions class
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include "StdInc.h"
#include "CClientTerrain.h"
#include <SharedUtil.Crypto.h>

void CLuaTerrainDefs::LoadFunctions(void)
{
    CLuaCFunctions::AddFunction("createTerrain", CreateTerrain);
    CLuaCFunctions::AddFunction("terrainDrawPreview", DrawPreview);
    CLuaCFunctions::AddFunction("terrainGetProperties", TerrainGetProperties);
    CLuaCFunctions::AddFunction("terrainSelect", TerrainSelect);
    CLuaCFunctions::AddFunction("terrainBuild", TerrainBuild);
    //CLuaCFunctions::AddFunction("terrainDeform", TerrainDeform);
    //CLuaCFunctions::AddFunction("terrainPaint", TerrainPaint);
    //CLuaCFunctions::AddFunction("terrainLightPaint", TerrainPaint);
    //CLuaCFunctions::AddFunction("terrainBuild", TerrainBuild);
    //CLuaCFunctions::AddFunction("terrainGetProperties", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainSave", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainLoad", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainAddRoad", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainApplyHeightMap", TerrainGetPreview);
    //CLuaCFunctions::AddFunction("terrainSetTexture", TerrainGetPreview);
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
    bool            bDrawVertices, bDrawPolygons, bDrawVerticesId;
    float           fDrawDistance;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTerrain);
    argStream.ReadNumber(fDrawDistance);
    argStream.ReadBool(bDrawVertices);
    argStream.ReadBool(bDrawPolygons);
    argStream.ReadBool(bDrawVerticesId);

    if (!argStream.HasErrors())
    {
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            if (pTerrain)
            {
                pTerrain->DrawPreview(fDrawDistance, bDrawVertices, bDrawPolygons, bDrawVerticesId);
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

int CLuaTerrainDefs::TerrainGetProperties(lua_State* luaVM)
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

int CLuaTerrainDefs::TerrainBuild(lua_State* luaVM)
{
    CClientTerrain* pTerrain;
    SString strModelName;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTerrain);
    argStream.ReadString(strModelName);
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
                SString strEmptyBase64 = "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";
                SString strFile = SharedUtil::Base64decode(strEmptyBase64);

                // Create a DFF element
                CClientDFF* pDFF = new CClientDFF(m_pManager, INVALID_ELEMENT_ID);

                // Try to load the DFF file
                if (pDFF->LoadDFF(strFile, true))
                {
                    // Success loading the file. Set parent to DFF root
                    pDFF->SetParent(pResource->GetResourceDFFRoot());

                    // Return the DFF
                    if (strModelName != NULL)
                    {
                        ushort usModelID = CModelNames::ResolveModelID(strModelName);
                        if (usModelID != INVALID_MODEL_ID)
                        {
                            pDFF->m_usModel = usModelID;
                        }
                    }
                    RpClump* pClump = pDFF->GetClump();
                    RpAtomic* pAtomic = pClump->getAtomic();
                    RpGeometry* pGeometry = pAtomic->geometry;
                    pGeometry->morphTarget->boundingSphere.radius = 10.0f;
                    CVector asd1(-1, 2, 3);
                    CVector asd2(6, 3, 5);
                    CVector asd3(1, -9, 4);
                    CVector asd4(-1, 4, 2);

                    g_pCore->GetConsole()->Printf("pre %i %i", pGeometry->vertices_size, pGeometry->triangles_size);
                    CClientDFF::CreateVertex(pGeometry, asd1);
                    CClientDFF::CreateVertex(pGeometry, asd2);
                    CClientDFF::CreateVertex(pGeometry, asd3);
                    CClientDFF::CreateVertex(pGeometry, asd4);
                    CClientDFF::CreatePolygon(pGeometry, 1,3,2,2);
                    //CClientDFF::CreatePolygon(pGeometry, 3,4,5,1);

                    for (int i = 0; i < pGeometry->triangles_size; i++)
                    {
                        RpTriangle a = pGeometry->triangles[i];
                        g_pCore->GetConsole()->Printf("triangle id %i : %i %i %i",i, a.v[0], a.v[1], a.v[2]);
                    }

                    g_pCore->GetConsole()->Printf("post %i %i", pGeometry->vertices_size, pGeometry->triangles_size);
                    lua_pushelement(luaVM, pDFF);
                    return 1;
                }
            }
        }
    }
    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // We failed
    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaTerrainDefs::TerrainSelect(lua_State* luaVM)
{
    CClientTerrain* pTerrain;
    eSelectTool     eTool;
    eSelectType     eType;

    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pTerrain);
    argStream.ReadEnumString(eTool);
    argStream.ReadEnumString(eType);
        
    if (!argStream.HasErrors())
    {
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine(luaVM);
        if (pLuaMain)
        {
            if (pTerrain)
            {
                std::vector<TerrainSelection*> tempSelectedVertices;

                std::vector<TerrainVertex*> vecVertices = pTerrain->GetVertices();
                std::vector<TerrainPolygon*> vecPolygons = pTerrain->GetPolygons();

                switch (eTool)
                {
                case SELECT_TOOL_BYVERTEXID:
                    while (argStream.NextIsNumber() || argStream.NextIsTable())
                    {
                        if (argStream.NextIsNumber())
                        {
                            int vertexId;
                            argStream.ReadNumber(vertexId);
                            if (vertexId <= 0 || vertexId >= vecVertices.size())
                            {
                                lua_pushnumber(luaVM, 3);
                                lua_pushboolean(luaVM, false);
                                return 2;
                            }
                            else
                            {
                                TerrainSelection* pSelect = new TerrainSelection;
                                pSelect->power = 100;
                                pSelect->vertex = vecVertices.at(vertexId - 1);
                                tempSelectedVertices.push_back(pSelect);
                            }
                        }
                        else
                        {
                            std::vector<float> outList;
                            argStream.ReadNumberTable(outList);
                            if (outList.size() == 2)
                            {
                                int vertexId = (int)outList.at(0);
                                if (vertexId <= 0 || vertexId >= vecVertices.size())
                                {
                                    lua_pushnumber(luaVM, 3);
                                    lua_pushboolean(luaVM, false);
                                    return 2;
                                }
                                else
                                {
                                    TerrainSelection* pSelect = new TerrainSelection;
                                    pSelect->power = outList.at(1);
                                    pSelect->vertex = vecVertices.at(vertexId - 1);
                                    tempSelectedVertices.push_back(pSelect);
                                }
                            }
                            else
                            {
                                lua_pushnumber(luaVM, 4);
                                lua_pushboolean(luaVM, false);
                                return 2;
                            }
                        }
                        
                    }
                    break;
                case SELECT_TOOL_BYPOLYGONID:

                    break;
                case SELECT_TOOL_NEAREST:

                    break;
                case SELECT_TOOL_INRANGE:

                    break;
                case SELECT_TOOL_INRANGESOFT:

                    break;
                case SELECT_TOOL_GROW:

                    break;
                case SELECT_TOOL_SHRINK:

                    break;

                }

                sort(tempSelectedVertices.begin(), tempSelectedVertices.end());
                tempSelectedVertices.erase(unique(tempSelectedVertices.begin(), tempSelectedVertices.end()), tempSelectedVertices.end());

                if (tempSelectedVertices.size() == 0)
                {
                    lua_pushnumber(luaVM, 2);
                    lua_pushboolean(luaVM, false);
                    return 2;
                }
                else
                {
                    // @TODO, make that tempSelectedVertices is added to final selected list
                    lua_pushboolean(luaVM, true);
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
