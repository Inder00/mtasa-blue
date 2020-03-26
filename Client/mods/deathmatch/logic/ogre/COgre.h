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
}

class COgre
{
public:
    COgre();
    ~COgre();
    void CreateCamera();
    void CreateTexture();
    void loadResources(std::string path, std::string name);
    void RegisterHlms();

private:
    Ogre::Root* m_pRoot;
    Ogre::SceneManager* m_pSceneManager;
    Ogre::Camera* m_pCamera;
    Ogre::Material*            mat;
};
