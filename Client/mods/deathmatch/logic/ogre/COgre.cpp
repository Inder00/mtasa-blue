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
#include "Ogre/include/OgreCodec.h"
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
#include "ogre/include/OgreTextureGpuManager.h"
#include "ogre/include/OgreDynLib.h"
#include "ogre/include/OgreTextureFilters.h"
#include "ogre/include/OgreRectangle2D2.h"

#include "D:\mtablue\mtasa-blue\vendor\ogre\include\Compositor\OgreCompositorWorkspace.h"

#include "RenderSystem_Direct3D11/include/OgreD3D11Plugin.h"
#include "OgreHlmsUnlit/include/OgreHlmsUnlit.h"
#include "OgreHlmsPbs/include/OgreHlmsPbs.h"
#include "OgreHlmsPbs/include/OgreHlmsPbsDatablock.h"

#include "RenderSystem_Direct3D11/include/OgreD3D11RenderSystem.h"

void createHlmsFromMaterial(const Ogre::String materialName);
COgre::COgre()
{

    m_pRoot = new Ogre::Root("", "", "Ogre.log");
    Ogre::D3D11Plugin* plugin = new Ogre::D3D11Plugin();
    Ogre::Root::getSingleton().installPlugin(plugin);
    plugin->initialise();

    m_pRenderSystem = m_pRoot->getRenderSystemByName("Direct3D11 Rendering Subsystem");
    m_pRoot->setRenderSystem(m_pRenderSystem);

    m_pRoot->initialise(false);
    Ogre::NameValuePairList params;
    params.insert(Ogre::NameValuePairList::value_type("resolution", "800x600"));
    params.insert(Ogre::NameValuePairList::value_type("fullscreen", "false"));
    params.insert(Ogre::NameValuePairList::value_type("vsync", "false"));

    m_pWindow = m_pRoot->createRenderWindow("MTA:SA", 800, 600, false, &params);

    RegisterHlms();
    loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/textures/", "textures");
    loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/shaders/", "shaders");
    loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/meshes/", "meshes");

    //m_pRoot->getHlmsManager()->useDefaultDatablockFrom(Ogre::HlmsTypes::HLMS_PBS);


    m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, 1, "ExampleInstance");
    m_pRoot->_pushCurrentSceneManager(m_pSceneManager);
    CreateCamera();
    CreateDefaultLight();
    CreteSceneObjects();
    ManualObject();

    auto b = m_pSceneManager->createEntity("WoodPallet.mesh", "meshes");
    Ogre::SceneNode* pNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::SCENE_DYNAMIC);

    pNode->attachObject(b);

    auto a = SetupCompositor();


    Ogre::ManualObject* manualLine = m_pSceneManager->createManualObject();
    m_pSceneManager->getRootSceneNode()->attachObject(manualLine);
    manualLine->clear();
    manualLine->begin("lineMat", Ogre::OperationType::OT_LINE_LIST);
    manualLine->position(Ogre::Vector3(0, 0, 0));
    manualLine->position(Ogre::Vector3(100, 100, 100));

    manualLine->position(0, 0, 0.0);
    manualLine->position(100, 100, 0.0);
    manualLine->position(0, 100, 0.0);
    manualLine->position(100, 0, 0.0);

    manualLine->index(0);
    manualLine->index(1);
    manualLine->index(2);
    manualLine->index(3);
    manualLine->index(0);
    manualLine->end();

    m_pRenderSystem->updateCompositorManager(m_pRoot->getCompositorManager2());
    while (true)
    {
        Ogre::WindowEventUtilities::messagePump();
        a->setEnabled(true);
        m_pRoot->renderOneFrame();
        m_pCamera->setFOVy(Ogre::Radian(180));
        a->setEnabled(false);
    }
}

Ogre::CompositorWorkspace* COgre::SetupCompositor()
{
    Ogre::CompositorManager2* compositorManager = m_pRoot->getCompositorManager2();

    const Ogre::String workspaceName("Demo Workspace");
    if (!compositorManager->hasWorkspaceDefinition(workspaceName))
    {
        compositorManager->createBasicWorkspaceDef(workspaceName, Ogre::ColourValue(0.2f, 0.5f, 0.8f));
    }

    return compositorManager->addWorkspace(m_pSceneManager, m_pWindow->getTexture(), m_pCamera, workspaceName, true);
}

void createHlmsFromMaterial(const Ogre::String materialName)
{
    // load the material
    Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(materialName);

    // check datablock does not already exists
    Ogre::HlmsManager*   hlmsManager = Ogre::Root::getSingleton().getHlmsManager();
    Ogre::HlmsDatablock* block = hlmsManager->getDatablockNoDefault(materialName);
    if (block == NULL)
    {
        if (mat.isNull() == false)
        {
            Ogre::HlmsPbs*          hlmsPbs = dynamic_cast<Ogre::HlmsPbs*>(Ogre::Root::getSingleton().getHlmsManager()->getHlms(Ogre::HLMS_PBS));
            Ogre::HlmsPbsDatablock* datablock = static_cast<Ogre::HlmsPbsDatablock*>(
                hlmsPbs->createDatablock(materialName, materialName, Ogre::HlmsMacroblock(), Ogre::HlmsBlendblock(), Ogre::HlmsParamVec()));

            datablock->setSpecular(Ogre::Vector3(0.2));
            datablock->setRoughness(0.8);
            datablock->setFresnel(Ogre::Vector3(0.015), false);

            Ogre::Technique* matTech = mat->getBestTechnique();

            if (matTech == NULL)
            {
                // if best technique is not valid just grab the first one
                Ogre::Material::TechniqueIterator techItr = mat->getTechniqueIterator();
                if (techItr.hasMoreElements())
                {
                    matTech = techItr.getNext();
                }
            }

            if (matTech)
            {
                Ogre::Technique::PassIterator passItr = matTech->getPassIterator();
                while (passItr.hasMoreElements())
                {
                    // itterate through all defined textures in this pass. Currently assume they are all the diffuse texture
                    Ogre::Pass::TextureUnitStateIterator texItr = passItr.getNext()->getTextureUnitStateIterator();
                    while (texItr.hasMoreElements())
                    {
                        Ogre::TextureUnitState*                   tex = texItr.getNext();
                        Ogre::TextureGpuManager* textureMgr = Ogre::Root::getSingletonPtr()->getRenderSystem()->getTextureGpuManager();
                        Ogre::TextureGpu*                         texLoc = textureMgr->createOrRetrieveTexture(
                            tex->getFrameTextureName(0), Ogre::GpuPageOutStrategy::Discard, Ogre::TextureFlags::PrefersLoadingFromFileAsSRGB,
                            Ogre::TextureTypes::TypeCube, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
                            Ogre::TextureFilter::TypeGenerateDefaultMipmaps);
                        datablock->setTexture(Ogre::PBSM_DIFFUSE, texLoc);
                    }
                }
            }
        }
    }
}

void COgre::CreteSceneObjects()
{
    createHlmsFromMaterial("RockWall");
    createHlmsFromMaterial("BaseWhite");
    createHlmsFromMaterial("WoodPallet");
    createHlmsFromMaterial("lineMat");

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::v1::MeshManager::getSingletonPtr()->createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 5, 50, 20, 20, true, 1, 5,
                                                          5, Ogre::Vector3::UNIT_Z);

    Ogre::v1::Entity* plane1 = m_pSceneManager->createEntity("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::v1::Entity* plane2 = m_pSceneManager->createEntity("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::SceneNode*  pNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::SCENE_DYNAMIC);
    pNode->attachObject(plane1);
    pNode->attachObject(plane2);
    plane1->setDatablock("RockWall");
    plane2->setDatablock("BaseWhite");
}

void COgre::RegisterHlms()
{
    Ogre::String hlmsFolder = "I:/ogre-next-master/Scripts/BuildScripts/output/Ogre/ogre-next/Samples/Media/";
    Ogre::String shadingLanguage = "HLSL";
    auto hlmsManager = Ogre::Root::getSingleton().getHlmsManager();

    // Shader library
    auto library = Ogre::ArchiveVec();

    // Common archive
    auto archiveLibrary = Ogre::ArchiveManager::getSingleton().load(hlmsFolder + "Hlms\\Common\\" + shadingLanguage, "FileSystem", true);
    auto archiveLibraryAny = Ogre::ArchiveManager::getSingleton().load(hlmsFolder + "Hlms\\Common\\Any", "FileSystem", true);

    // Unlit archive
    auto archiveUnlitAny = Ogre::ArchiveManager::getSingleton().load(hlmsFolder + "Hlms\\Unlit\\Any", "FileSystem", true);
    auto archiveUnlit = Ogre::ArchiveManager::getSingleton().load(hlmsFolder + "Hlms\\Unlit\\" + shadingLanguage, "FileSystem", true);

    // PBS archive
    auto archivePbsAny = Ogre::ArchiveManager::getSingleton().load(hlmsFolder + "Hlms\\Pbs\\Any", "FileSystem", true);
    auto archivePbs = Ogre::ArchiveManager::getSingleton().load(hlmsFolder + "Hlms\\Pbs\\" + shadingLanguage, "FileSystem", true);

    // Push Common and Unlit archives to library
    library.push_back(archiveLibrary);
    library.push_back(archiveLibraryAny);
    library.push_back(archiveUnlitAny);
    library.push_back(archiveUnlit);

    // HLMS Unlit
    auto hlmsUnlit = new Ogre::HlmsUnlit(archiveUnlit, &library);

    // Keep the Common and push the Pbs archives
    library.pop_back();
    library.pop_back();
    library.push_back(archivePbsAny);
    library.push_back(archivePbs);

    // HLMS PBS
    auto hlmsPbs = new Ogre::HlmsPbs(archivePbs, &library);

    bool supportsNoOverwriteOnTextureBuffers;
    m_pRenderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV", &supportsNoOverwriteOnTextureBuffers);

    if (!supportsNoOverwriteOnTextureBuffers)
    {
        hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
        hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
    }

    // Register HLMS
    hlmsManager->registerHlms(hlmsUnlit);
    hlmsManager->registerHlms(hlmsPbs);
}

void COgre::loadResources(std::string path, std::string name)
{
    Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup(name);
    Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(path, "FileSystem", name, false);
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(name, false);
    Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup(name);
}

void COgre::CreateDefaultLight()
{
    Ogre::Light* l = m_pSceneManager->createLight();
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDiffuseColour(Ogre::ColourValue::White);
    l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
    Ogre::SceneNode* ln = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    ln->setDirection(Ogre::Vector3(0.55, -0.3, 0.75).normalisedCopy());
    ln->attachObject(l);

    m_pSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5), Ogre::ColourValue(0.6, 0.6, 0.6), Ogre::Vector3(1.0));
}

void COgre::CreateCamera()
{
    m_pCamera = m_pSceneManager->createCamera("Main Camera");

    // Position it at 500 in Z direction
    m_pCamera->setPosition(Ogre::Vector3(0, 5, 15));
    // Look back along -Z
    m_pCamera->lookAt(Ogre::Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(0.2f);
    m_pCamera->setFarClipDistance(1000.0f);
    m_pCamera->setAutoAspectRatio(true);
}

void COgre::ManualObject()
{
    Ogre::ManualObject* myManualObject = m_pSceneManager->createManualObject();
    Ogre::SceneNode*    myManualObjectNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    // NOTE: The second parameter to the create method is the resource group the material will be added to.
    // If the group you name does not exist (in your resources.cfg file) the library will assert() and your program will crash
    //Ogre::MaterialPtr myManualObjectMaterial =
    //    Ogre::MaterialManager::getSingleton().create("manual1Material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //myManualObjectMaterial->setReceiveShadows(false);

    ////myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
    //myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0, 0, 1, 0);
    //myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0, 0, 1);
    //myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0, 0, 1);
    ////myManualObjectMaterial->dispose();            // dispose pointer, not the material

    myManualObject->begin("RockWall", Ogre::OT_LINE_LIST);
    myManualObject->position(-0.2, -0.2, 0.0);
    myManualObject->position(0.2, -10, 0.0);
    myManualObject->position(0.2, 10, 0.0);
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
