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

class CClientManager;

class CClientPhysics : public CClientEntity
{
    DECLARE_CLASS(CClientPhysics, CClientEntity)
public:
    CClientPhysics(CClientManager* pManager, ElementID ID);
    ~CClientPhysics();
    void Unlink();
    void SpawnBox(CVector size, CVector position);
    void Update();
    void RenderDebug(rp3d::CollisionShape* eShapeName, CMatrix& matrix);

    void GetPosition(CVector& vecPosition) const {};
    void SetPosition(const CVector& vecPosition){};

    eClientEntityType GetType() const { return CCLIENTPHYSICS; };

    rp3d::DynamicsWorld* dynamicsWorld;

    std::vector<rp3d::RigidBody*> vecRigidBodies;
    uint       previousFrameTime;
    CTickCount m_LastTimeMs;
    int        m_iTimeMsBetweenCalls;
    uint       m_uiNumSends;
    CGraphicsInterface*           m_pGraphics;
};
