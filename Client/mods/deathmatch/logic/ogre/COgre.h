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

#pragma once

namespace Ogre
{
    class Root;
    class SceneManager;
    class Camera;
    class Material;
    class Vector3;
    class ManualObject;
    class ColourValue;
    class RenderSystem;
    class CompositorWorkspace;
    class Window;
}

class COgre
{
public:
    COgre();
    ~COgre();
    void CreateCamera();
    void ManualObject();
    void loadResources(std::string path, std::string name);
    void CreateDefaultLight();
    void RegisterHlms();
    void CreteSceneObjects();
    Ogre::CompositorWorkspace* SetupCompositor();

private:
    Ogre::Root* m_pRoot;
    Ogre::SceneManager* m_pSceneManager;
    Ogre::Camera* m_pCamera;
    Ogre::RenderSystem* m_pRenderSystem;
    Ogre::Window*       m_pWindow;
};
