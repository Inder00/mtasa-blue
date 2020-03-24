/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        core/CAssetsManager.cpp
 *  PURPOSE:     Asset control class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#undef PI
#include "Ogre/include/OgreArchiveManager.h"
#include "Ogre/include/OgreCamera.h"
#include "Ogre/include/OgreConfigFile.h"
#include "Ogre/include/OgreRoot.h"
#include "Ogre/include/OgreWindow.h"

#include "Ogre/include/OgreHlmsManager.h"

#include "Ogre/include/Compositor/OgreCompositorManager2.h"

#include "Ogre/include/OgreWindowEventUtilities.h"

CAssetsManager::CAssetsManager()
{
    ambientColor = D3DCOLOR_ARGB(255, 150, 150, 150);
    Ogre::Root* root = new Ogre::Root("", "", "Ogre.log");
    Ogre::Window*     window = root->initialise(true, "Tutorial 00: Basic");
}

CAssetsManager::~CAssetsManager()
{
}

CAssetInstance* CAssetsManager::GetRenderGroup(unsigned int idx)
{
    if (!RenderGroupExists(idx))
    {
        m_renderingGroups.insert({idx, new CAssetInstance()});
    }
    return m_renderingGroups.at(idx);
}

DWORD CAssetsManager::GetAmbientColor()
{
    return ambientColor;
}
