/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/luadefs/CLuaRendererDefs.cpp
 *  PURPOSE:     Lua definitions class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

void CLuaRendererDefs::LoadFunctions(void)
{
    std::map<const char*, lua_CFunction> functions{
        {"createRenderer", CreateRenderer},
        {"rendererTestSet", RendererTestSet},
        {"rendererTestGet", RendererTestGet },
    };

    // Add functions
    for (const auto& pair : functions)
    {
        CLuaCFunctions::AddFunction(pair.first, pair.second);
    }
}

void CLuaRendererDefs::AddClass(lua_State* luaVM)
{
    lua_newclass(luaVM);

    lua_classfunction(luaVM, "set", "rendererTestSet");
    lua_classfunction(luaVM, "get", "rendererTestGet");


    lua_registerstaticclass(luaVM, "Renderer");
}

int CLuaRendererDefs::CreateRenderer(lua_State* luaVM)
{
    CClientRenderer* pRenderer = new CClientRenderer(m_pManager, INVALID_ELEMENT_ID);
    lua_pushelement(luaVM, pRenderer);
    return 1;
}

int CLuaRendererDefs::RendererTestSet(lua_State* luaVM)
{
    CClientRenderer* pRenderer;
    int bTest;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pRenderer);
    argStream.ReadNumber(bTest);

    if (!argStream.HasErrors())
    {
        pRenderer->testint = bTest;
        lua_pushboolean(luaVM, true);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // Failed
    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaRendererDefs::RendererTestGet(lua_State* luaVM)
{
    CClientRenderer* pRenderer;
    CScriptArgReader argStream(luaVM);
    argStream.ReadUserData(pRenderer);

    if (!argStream.HasErrors())
    {
        lua_pushnumber(luaVM, pRenderer->testint);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    // Failed
    lua_pushboolean(luaVM, false);
    return 1;
}
