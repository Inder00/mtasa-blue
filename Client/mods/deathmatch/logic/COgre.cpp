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
#include "Ogre/include/OgreMaterial.h"
#include "Ogre/include/OgreMaterialManager.h"
#include "Ogre/include/OgreId.h"
#include "Ogre/include/OgreCamera.h"
#include "Ogre/include/OgreWindow.h"
#include "Ogre/include/OgreMeshManager2.h"
#include "Ogre/include/OgreMeshManager.h"
#include "Ogre/include/OgreEntity.h"
#include "Ogre/include/OgreTechnique.h"
#include "Ogre/include/OgrePrerequisites.h"
#include "Ogre/include/Compositor/OgreCompositorManager2.h"
#include "RenderSystem_Direct3D11/include/OgreD3D11RenderSystem.h"

COgre::COgre()
{
     Ogre::Root* root = new Ogre::Root("", "", "Ogre.log");
     Ogre::RenderSystem* renderSystem = new Ogre::D3D11RenderSystem();
     root->setRenderSystem(renderSystem);
     Ogre::NameValuePairList params;
     root->initialise(false);
     Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(".", "FileSystem", "General");
     Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("default");
     Ogre::MaterialManager::getSingletonPtr()->create("default", "default");
     Ogre::Window* window = root->createRenderWindow("SA-MP 0.4.0", 1000, 1000, false, &params);

     //Ogre::Material* mat = Ogre::MaterialManager::getSingleton().create("matPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME).getPointer();
     //Ogre::TextureUnitState* tuisTexture = mat->getTechnique(0)->getPass(0)->createTextureUnitState("UV_Checker.png");
     Ogre::Plane plane;
     plane.normal = Ogre::Vector3::UNIT_Y;
     plane.d = 0;
     Ogre::v1::MeshManager::getSingleton().createPlane("plane", "default", plane, 4500, 4500, 10, 10, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
     
         // Create SceneManager
     const size_t  numThreads = 1u;
     Ogre::SceneManager* sceneManager = root->createSceneManager(Ogre::ST_GENERIC, numThreads, "ExampleInstance");

     Ogre::SceneNode*    pNode = sceneManager->getRootSceneNode()->createChildSceneNode();
     // Create & setup camera
     Ogre::Camera* camera = sceneManager->createCamera("Main Camera");
     
     Ogre::v1::Entity* pPlaneEnt = sceneManager->createEntity("plane");
     //pPlaneEnt->setMaterialName("matPlane");
     pNode->attachObject(pPlaneEnt);

     Ogre::Light* l = sceneManager->createLight();
     l->setType(Ogre::Light::LT_DIRECTIONAL);
     l->setDiffuseColour(Ogre::ColourValue::White);
     l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
     Ogre::SceneNode* ln = sceneManager->getRootSceneNode()->createChildSceneNode();
     ln->setDirection(Ogre::Vector3(0.55, -0.3, 0.75).normalisedCopy());
     ln->attachObject(l);

     // Position it at 500 in Z direction
     camera->setPosition(Ogre::Vector3(0, 50, 30));
     // Look back along -Z
     camera->lookAt(Ogre::Vector3(0, 0, 0));
     camera->setNearClipDistance(0.2f);
     camera->setFarClipDistance(1000.0f);
     camera->setAutoAspectRatio(true);

         // Setup a basic compositor with a blue clear colour
     Ogre::CompositorManager2* compositorManager = root->getCompositorManager2();
     const Ogre::String        workspaceName("Demo Workspace");
     const Ogre::ColourValue   backgroundColour(0.2f, 0.4f, 0.6f);
     compositorManager->createBasicWorkspaceDef(workspaceName, backgroundColour, Ogre::IdString());
     compositorManager->addWorkspace(sceneManager, window->getTexture(), camera, workspaceName, true);
     root->renderOneFrame();
}

COgre::~COgre()
{

}
