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
#include <ogre/include/OgreMesh2Serializer.h>

COgre::COgre()
{
}

COgre::~COgre()
{
}

void COgre::init()
{
    Root* root = new Root("", "");

    // Install RenderSystem Plugin
    D3D11Plugin* d3dPlugin = new D3D11Plugin();
    root->installPlugin(d3dPlugin);

    // Use the first available Renderer
    RenderSystem* renderSys = root->getAvailableRenderers()[0];
    root->setRenderSystem(renderSys);

    // Initialize Root
    root->initialise(false);
    root->addFrameListener(this);

    // Initialize renderWindow
    NameValuePairList params;
    params["gamma"] = "true";

    Window* renderWindow = root->createRenderWindow("OgreTest", 1280, 720, false, &params);

    // Create the SceneManager
    sceneManager = root->createSceneManager(ST_GENERIC, 4, "SceneManager");
    sceneManager->setAmbientLight(ColourValue(0.5, 0.5, 0.5), ColourValue(0.5, 0.5, 0.5), Vector3(0,0,-1));            // Set ambient lighting

                                                                                                                       // Create the MainCamera
    Camera* mainCamera = sceneManager->createCamera("Camera");
    mainCamera->setAutoAspectRatio(true);
    mainCamera->setNearClipDistance(0.01);
    mainCamera->setFarClipDistance(1000.0);
    // And attach it to a SceneNode
    mainCameraNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    mainCamera->detachFromParent();
    mainCameraNode->attachObject(mainCamera);
    mainCamera->setPosition(0, 15, 15);
    mainCamera->setDirection(Vector3(0, 0, -15) - mainCamera->getPosition());
    ResourcePtr asd = MeshManager::getSingleton().createResource("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // Create a directional Light
    Light* directionalLight = sceneManager->createLight();
    directionalLight->setDiffuseColour(1, 1, 1);
    directionalLight->setType(Light::LT_DIRECTIONAL);
    SceneNode* lightNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(directionalLight);
    directionalLight->setDirection(Vector3(-1, -1, -1));
    directionalLight->setPowerScale(1);

    // Add media folder
    //loadResources("D:\\MTA SA\\OGRE\\", "textures");
    //loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/shaders/", "shaders");
    //loadResources("D:/mtablue/mtasa-blue/Bin/ogretest/meshes/", "meshes");

    //// Create a basic Workspace
    root->getCompositorManager2()->createBasicWorkspaceDef("sceneworkspace", ColourValue::Blue);
    CompositorWorkspace* workspace =
        root->getCompositorManager2()->addWorkspace(sceneManager, renderWindow->getTexture(), mainCamera, "sceneworkspace", true);
    
    // register HLMS
    String rootHlmsFolder = "D:/MTA SA/OGRE/";
    // mName = "D:/MTA SA/OGRE/Hlms/Unlit/HLSL"
    // For retrieval of the paths to the different folders needed
    
    {
        ArchiveVec archiveUnlitLibraryFolders;
        mHlmsUnlit = new HlmsUnlit(nullptr, &archiveUnlitLibraryFolders);
        Root::getSingleton().getHlmsManager()->registerHlms(mHlmsUnlit);
    }

    {
        ArchiveVec archivePbsLibraryFolders;
        mHlmsPbs = new HlmsPbs(nullptr, &archivePbsLibraryFolders);
        Root::getSingleton().getHlmsManager()->registerHlms(mHlmsPbs);
    }

    // configure shadow quality
    mHlmsPbs->setShadowSettings(HlmsPbs::PCF_4x4);

    //// Get the cube Mesh
    //v1::MeshPtr cubeMesh = v1::MeshManager::getSingletonPtr()->load("cube.mesh", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //cubeMeshV2 = MeshManager::getSingleton().createManual("cubeV2.mesh", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //// Import the v1 mesh to v2 format
    //cubeMeshV2->importV1(cubeMesh.get(), true, true, true);
    //cubeMesh->unload();

    //// create a datablock (material)
    //String            datablockName = "CubeMat";
    //HlmsPbsDatablock* cubeDatablock = static_cast<HlmsPbsDatablock*>(
    //    mHlmsPbs->createDatablock(datablockName, datablockName, HlmsMacroblock(), HlmsBlendblock(), HlmsParamVec()));

    //// set the diffuse texture
   /* Ogre::TexturePtr rttTexture =
        Ogre::TextureManager::getSingleton().createManual("RttTex", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,
                                                          mWindow->getWidth(), mWindow->getHeight(), 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);*/

    //cubeDatablock->setTexture(PBSM_DIFFUSE, diffuseTexture);

    // set some values
    //cubeDatablock->setDiffuse(Vector3(1, 1, 1));
    //cubeDatablock->setFresnel(Vector3::UNIT_SCALE * 0.1, false);
    //cubeDatablock->setSpecular(Vector3(0, 0, 0));
    //cubeDatablock->setRoughness(0.9);
    //ent->getSubEntity(0)->setMaterialName("mtastaff.png", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //ent->setMaterial(diffuseTexture);
    //// Create a Cube
    //Item* cubeItem = sceneManager->createItem(cubeMeshV2);
    //cubeNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    //cubeNode->attachObject(cubeItem);
    //cubeNode->setScale(Vector3(0.6, 0.25, 1.5));
    //// cubeNode->scale( Vector3::UNIT_SCALE*0.2 );
    //cubeNode->setPosition(0, 0, 0);
    //cubeItem->setDatablock(cubeDatablock);

    // some child cubes to make it look like a plane
    //{
    //    Item*      cubeItem = sceneManager->createItem(cubeMeshV2);
    //    SceneNode* childCubeNode = cubeNode->createChildSceneNode();
    //    childCubeNode->attachObject(cubeItem);
    //    childCubeNode->scale(Vector3(2, 0.1, 0.4));
    //    cubeItem->setDatablock(cubeDatablock);
    //}
    //{
    //    Item*      cubeItem = sceneManager->createItem(cubeMeshV2);
    //    SceneNode* childCubeNode = cubeNode->createChildSceneNode();
    //    childCubeNode->attachObject(cubeItem);
    //    childCubeNode->scale(Vector3(0.1, 2, 1));
    //    cubeItem->setDatablock(cubeDatablock);
    //}

    Ogre::MeshPtr mesh = MeshManager::getSingleton().createManual("ground2", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::SubMesh* subMesh = mesh->createSubMesh();
    Ogre::VertexElement2Vec vertexElements;
    vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_POSITION));

    Ogre::VertexBufferPacked* vertexBuffer = nullptr;
    std::vector<Vector3>      tri_vertices = {{0, 0, 0}, {10, 0, 0}, {10, 10, 0}, {0, 10, 0}};
    std::vector<int>          indices = {0, 1, 2, 3};
    vertexBuffer = renderSys->getVaoManager()->createVertexBuffer(vertexElements, 4, Ogre::BT_IMMUTABLE, tri_vertices.data(), true);
    Ogre::VertexBufferPackedVec vertexBuffers;
    vertexBuffers.push_back(vertexBuffer);

    Ogre::IndexBufferPacked* index_buffer =
        renderSys->getVaoManager()->createIndexBuffer(Ogre::IndexBufferPacked::IT_32BIT, 12, Ogre::BT_IMMUTABLE, indices.data(), true);
    Ogre::VertexArrayObject* vao = renderSys->getVaoManager()->createVertexArrayObject(vertexBuffers, index_buffer, Ogre::OT_TRIANGLE_LIST);

    subMesh->mVao[Ogre::VpNormal].push_back(vao);
    subMesh->mVao[Ogre::VpShadow].push_back(vao);

    auto testNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    Item* testplane =  sceneManager->createItem(mesh);
    testNode->attachObject(testplane);

    Ogre::TexturePtr myTexture = Ogre::TextureManager::getSingletonPtr()->createManual(
        "MyTexture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 128, 128, 0, Ogre::PF_A8R8G8B8, Ogre::TU_DYNAMIC_WRITE_ONLY);

    cubeDatablock->setTexture(Ogre::PBSM_DIFFUSE, texLocation.xIdx, texLocation.texture);
    root->startRendering();
}

void COgre::loadResources(std::string path, std::string name)
{
    ResourceGroupManager::getSingletonPtr()->createResourceGroup(name);
    ResourceGroupManager::getSingletonPtr()->addResourceLocation(path, "FileSystem", name, false);
    ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(name, false);
    ResourceGroupManager::getSingletonPtr()->loadResourceGroup(name);
}

bool COgre::frameRenderingQueued(const FrameEvent& evt)
{
    //cubeNode->rotate(Quaternion(Radian(Degree(50 * evt.timeSinceLastFrame).valueRadians()), Vector3::UNIT_Y));

    return true;
}
