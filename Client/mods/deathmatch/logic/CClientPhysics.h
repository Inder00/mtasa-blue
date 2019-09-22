/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientEffect.h
 *  PURPOSE:     Effect entity
 *
 *****************************************************************************/

#pragma once

#include "reactphysics3d.h"

class CLuaPhysicsRigidBody;
class CClientManager;

class CClientPhysics : public CClientEntity
{
    DECLARE_CLASS(CClientPhysics, CClientEntity)
public:
    CClientPhysics(CClientManager* pManager, ElementID ID);
    ~CClientPhysics();
    void Unlink();
    void GetPosition(CVector& vecPosition) const {};
    void SetPosition(const CVector& vecPosition){};

    void SetLuaMain(CLuaMain* pLuaMain) { m_pLuaMain = pLuaMain; }

    void Update();
    void RenderDebug(rp3d::CollisionShape* eShapeName, CMatrix& matrix);
    rp3d::RigidBody*      CreateWorldRigidBody() { return m_pDynamicsWorld->createRigidBody(rp3d::Transform::identity()); }
    CLuaPhysicsRigidBody* CreateRigidBody();




    rp3d::RigidBody* m_pPlane;



    eClientEntityType GetType() const { return CCLIENTPHYSICS; };

    rp3d::DynamicsWorld* m_pDynamicsWorld;

    std::vector<CLuaPhysicsRigidBody*> vecRigidBodies;
    uint                               previousFrameTime;
    CTickCount                         m_LastTimeMs;
    int                                m_iTimeMsBetweenCalls;
    uint                               m_uiNumSends;
    CGraphicsInterface*                m_pGraphics;
    CLuaMain*                          m_pLuaMain;
};
