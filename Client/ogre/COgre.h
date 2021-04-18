/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/COgre.h
 *  PURPOSE:     Header for ogre class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#ifndef COgre_H
#define COgre_H
namespace Ogre
{
    class PixelBox;
}
#include "OgrePrerequisites.h"
#include "Deprecated/OgrePixelBox.h"
#include "Ogre.h"
#include "OgreRoot.h"
#include "Deprecated/OgreRenderTargetListener.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"

#include "OgreHlmsPbs.h"
#include "OgreHlmsUnlit.h"
#include "OgreHlmsManager.h"
#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsUnlitDatablock.h"

#include "OgreMesh2.h"
#include "OgreMeshManager2.h"
#include "OgreItem.h"
#include "Deprecated/OgreRenderWindow.h"
#include "OgreWindow.h"
#include "Compositor/OgreCompositorManager2.h"

//#include "OgreBoxEmitter.h"

#include <iostream>

class COgre : public Ogre::FrameListener
{
public:
    COgre();
    virtual ~COgre();
    virtual void init();
    void loadResources(std::string path, std::string name);

private:
    bool                frameRenderingQueued(const Ogre::FrameEvent& evt);
    Ogre::SceneManager* sceneManager;
    Ogre::SceneNode*    mainCameraNode;
    Ogre::SceneNode*    cubeNode;
    Ogre::MeshPtr       cubeMeshV2;

    Ogre::Quaternion sensorOrientation;
    float            lastTime;
    Ogre::HlmsPbs*   mHlmsPbs;
    Ogre::HlmsUnlit* mHlmsUnlit;
};

#endif            // COgre_H
