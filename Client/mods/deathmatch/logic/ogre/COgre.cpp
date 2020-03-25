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

#ifdef PI
    #undef PI
#endif

#include "COgre.h"
#include "Ogre/include/Ogre.h"
#include "Ogre/include/OgreRoot.h"
#include "Ogre/include/OgreMaterial.h"
#include "Ogre/include/OgreMaterialManager.h"
#include "Ogre/include/OgreResourceGroupManager.h"
#include "Ogre/include/OgreId.h"
#include "Ogre/include/OgreImage2.h"
#include "Ogre/include/OgreCamera.h"
#include "Ogre/include/OgreWindow.h"
#include "Ogre/include/OgreMeshManager2.h"
#include "Ogre/include/OgreMeshManager.h"
#include "Ogre/include/OgreEntity.h"
#include "Ogre/include/OgreTechnique.h"
#include "Ogre/include/OgrePrerequisites.h"
#include "Ogre/include/Compositor/OgreCompositorManager2.h"
#include "Ogre/include/OgreRenderOperation.h"
#include "ogre/include/OgreVertexIndexData.h"
#include "ogre/include/OgreMesh.h"
#include "ogre/include/OgreMesh2.h"
#include "ogre/include/OgreManualObject.h"
#include "ogre/include/OgreManualObject2.h"
#include "ogre/include/OgreAlignedAllocator.h"
#include "ogre/include/OgreHlms.h"
#include "ogre/include/OgreHlmsManager.h"
#include "ogre/include/OgreDynLib.h"

#include "OgreHlmsUnlit/include/OgreHlmsUnlit.h"

#include "RenderSystem_Direct3D11/include/OgreD3D11RenderSystem.h"

COgre::COgre()
{
    Ogre::Root*         m_pRoot = new Ogre::Root("", "", "Ogre.log");
    Ogre::RenderSystem* renderSystem = new Ogre::D3D11RenderSystem();

    m_pRoot->setRenderSystem(renderSystem);
    m_pRoot->initialise(false);
    Ogre::NameValuePairList params;

    Ogre::MaterialManager::getSingletonPtr()->create("default", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::Window* window = m_pRoot->createRenderWindow("MTA:SA", 1000, 1000, false, &params);
    RegisterHlms();
    loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/textures/", "textures");
    loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/shaders/", "shaders");
    m_pRoot->getHlmsManager()->useDefaultDatablockFrom(Ogre::HlmsTypes::HLMS_UNLIT);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::v1::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 4500, 4500, 10, 10, true, 1, 5,
                                                      5, Ogre::Vector3::UNIT_Z);

    m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, 1, "ExampleInstance");

    Ogre::SceneNode* pNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();

    Ogre::v1::Entity* pPlaneEnt = m_pSceneManager->createEntity("plane");

    pPlaneEnt->setMaterialName("GrassMaterial");
    // pNode->attachObject(pPlaneEnt);

    CreateCamera();
    Ogre::Light* l = m_pSceneManager->createLight();
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDiffuseColour(Ogre::ColourValue::White);
    l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
    Ogre::SceneNode* ln = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    ln->setDirection(Ogre::Vector3(0.55, -0.3, 0.75).normalisedCopy());
    ln->attachObject(l);
    m_pSceneManager->getRenderQueue()->setRenderQueueMode(5, Ogre::RenderQueue::V1_FAST);


    Ogre::v1::MeshManager::getSingletonPtr()->createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 50, 50, 20, 20, true, 1, 5,
                                                          5,
                                                          Ogre::Vector3::UNIT_Z);

    Ogre::v1::Entity* entPlano = m_pSceneManager->createEntity("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    entPlano->setRenderQueueGroup(5);
    //ln->attachObject(entPlano);

    // Setup a basic compositor with a blue clear colour
    Ogre::CompositorManager2* compositorManager = m_pRoot->getCompositorManager2();
    const Ogre::String        workspaceName("Demo Workspace");
    const Ogre::ColourValue   backgroundColour(0.2f, 0.4f, 0.6f);
    compositorManager->createBasicWorkspaceDef(workspaceName, backgroundColour, Ogre::IdString());
    compositorManager->addWorkspace(m_pSceneManager, window->getTexture(), m_pCamera, workspaceName, true);

    Ogre::ManualObject* myManualObject = m_pSceneManager->createManualObject();
    Ogre::SceneNode*    myManualObjectNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();

    //CreateTexture();
    m_pRoot->renderOneFrame();
}

void COgre::RegisterHlms()
{
    Ogre::Hlms* hlmsUnlit = new Ogre::HlmsUnlit(nullptr, 0);
    Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);

    //Ogre::Archive* archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Pbs/" + shaderSyntax, "FileSystem", true);
    //Ogre::HlmsPbs* hlmsPbs = new Ogre::HlmsPbs(archivePbs, &library);
    //Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);
}

void COgre::loadResources(std::string path, std::string name)
{
    Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup(name);
    Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(path, "FileSystem", name, false);
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(name, false);
    Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup(name);
}

void COgre::CreateCamera()
{
    m_pCamera = m_pSceneManager->createCamera("Main Camera");
    m_pCamera->setPosition(Ogre::Vector3(0, 5, 15));
    m_pCamera->lookAt(Ogre::Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(0.2f);
    m_pCamera->setFarClipDistance(1000.0f);
    m_pCamera->setAutoAspectRatio(true);
}

void COgre::CreateTexture()
{
    Ogre::ManualObject* myManualObject = m_pSceneManager->createManualObject();
    Ogre::SceneNode*    myManualObjectNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    // NOTE: The second parameter to the create method is the resource group the material will be added to.
    // If the group you name does not exist (in your resources.cfg file) the library will assert() and your program will crash
    Ogre::MaterialPtr myManualObjectMaterial =
        Ogre::MaterialManager::getSingleton().create("manual1Material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    myManualObjectMaterial->setReceiveShadows(false);

    //myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0, 0, 1, 0);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0, 0, 1);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0, 0, 1);
    //myManualObjectMaterial->dispose();            // dispose pointer, not the material

    myManualObject->begin("manual1Material", Ogre::OT_LINE_LIST);
    myManualObject->position(-0.2, -0.2, 0.0);
    myManualObject->position(0.2, -0.2, 0.0);
    myManualObject->position(0.2, 0.2, 0.0);
    myManualObject->position(-0.2, 0.2, 0.0);

    myManualObject->index(0);
    myManualObject->index(1);
    myManualObject->index(2);
    myManualObject->index(3);
    myManualObject->index(0);

    // etc
    myManualObject->end();

    myManualObjectNode->attachObject(myManualObject);
}


COgre::~COgre()
{
}
