/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/COgre.cpp
 *  PURPOSE:     Ogre class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include <StdInc.h>
#include "COgre.h"

#undef PI
#include "Ogre/include/OgreRoot.h"
#include "Ogre/include/OgreWindow.h"
#include "RenderSystem_Direct3D11/include/OgreD3D11RenderSystem.h"

COgre::COgre()
{
     Ogre::Root* root = new Ogre::Root("", "", "Ogre.log");
     Ogre::RenderSystem* renderSystem = new Ogre::D3D11RenderSystem();
     root->setRenderSystem(renderSystem);
     Ogre::NameValuePairList params;
     root->initialise(false);
     Ogre::Window* window = root->createRenderWindow("SA-MP 0.4.0", 800, 600, false, &params);

}

COgre::~COgre()
{

}
