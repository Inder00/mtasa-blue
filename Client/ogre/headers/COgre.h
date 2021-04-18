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

class COgre : public FrameListener, public COgreBase
{
public:
    COgre();
    ~COgre();
    void init();
    void loadResources(std::string path, std::string name);

private:
    bool          frameRenderingQueued(const FrameEvent& evt);
    SceneManager* sceneManager;
    SceneNode*    mainCameraNode;
    SceneNode*    cubeNode;
    MeshPtr       cubeMeshV2;

    Quaternion sensorOrientation;
    float      lastTime;
    HlmsPbs*   mHlmsPbs;
    HlmsUnlit* mHlmsUnlit;
};
