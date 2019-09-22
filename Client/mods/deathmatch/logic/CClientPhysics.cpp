/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientPhysics.cpp
 *  PURPOSE:     Effect entity class
 *
 *****************************************************************************/
#include "StdInc.h"

using namespace reactphysics3d;

CClientPhysics::CClientPhysics(CClientManager* pManager, ElementID ID) : ClassInit(this), CClientEntity(ID)
{
    m_pManager = pManager;
    m_pManager->GetPhysicsManager()->AddToList(this);
    SetTypeName("physics");
    Vector3 gravity(0.0f, 0.0f, -9.81);
    m_pDynamicsWorld = new DynamicsWorld(gravity);
    m_pGraphics = g_pCore->GetGraphics();
    m_LastTimeMs = CTickCount::Now();
}


CLuaPhysicsRigidBody* CClientPhysics::CreateRigidBody()
{
    CLuaPhysicsRigidBody* pRigidBody = m_pLuaMain->GetPhysicsRigidBodyManager()->CreateRigidBody(this);
    vecRigidBodies.push_back(pRigidBody);
    return pRigidBody;
}

void CClientPhysics::Update()
{
    CTickCount tickCountNow = CTickCount::Now();

    int iDeltaTimeMs = (int)(tickCountNow - m_LastTimeMs).ToLongLong();
    m_LastTimeMs = tickCountNow;
    const float timeStep = 1.0 / 60.0;
    m_pDynamicsWorld->update(((float)iDeltaTimeMs) / 1000.0f);
    float       angle;
    CMatrix     matrix;
    ProxyShape* pShapeList;

    for (const auto& body : vecRigidBodies)
    {
        body->GetMatrix(matrix);

        pShapeList = body->GetProxyShapesList();
        do
        {
            matrix.SetPosition(matrix.GetPosition() + *(CVector*)&pShapeList->getLocalToBodyTransform().getPosition());
            RenderDebug(pShapeList->getCollisionShape(), matrix);

        } while (pShapeList = pShapeList->getNext());
    }
}

void CClientPhysics::RenderDebug(rp3d::CollisionShape* pShape, CMatrix& matrix)
{
    rp3d::CollisionShapeName eShapeName = pShape->getName();

    float      fLineWidth = 5.0f;
    SColorARGB colorRed(255, 255, 0, 0);
    SColorARGB colorGreen(255, 0, 255, 0);
    SColorARGB colorBlue(255, 0, 255, 0);

    CVector pos = matrix.GetPosition();
    CVector vertexPosition;
    matrix.SetPosition(CVector(0, 0, 0));

    // used if else due switch require declare variables outside
    if (eShapeName == CollisionShapeName::BOX)
    {
        SColorARGB color1(0, 255, 0, 255);
        SColorARGB color2(0, 0, 255, 255);
        BoxShape*  eBox = (BoxShape*)pShape;

        CVector corners[8];
        for (int i = 0; i < 8; i++)
        {
            vertexPosition = *(CVector*)&eBox->getVertexPosition(i);
            corners[i] = matrix.TransformVector(vertexPosition) + pos;
        }

        // horizontal bottom
        m_pGraphics->DrawLine3DQueued(corners[0], corners[1], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[0], corners[3], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[2], corners[3], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[1], corners[2], fLineWidth, colorRed, false);

        // horizontal upper
        m_pGraphics->DrawLine3DQueued(corners[4], corners[5], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[4], corners[7], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[6], corners[7], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[5], corners[6], fLineWidth, colorRed, false);

        // vertical
        m_pGraphics->DrawLine3DQueued(corners[0], corners[4], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[1], corners[5], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[2], corners[6], fLineWidth, colorRed, false);
        m_pGraphics->DrawLine3DQueued(corners[3], corners[7], fLineWidth, colorRed, false);
    }
    else if (eShapeName == CollisionShapeName::SPHERE)
    {
        SphereShape* eShape = (SphereShape*)pShape;
        float        fRadius = eShape->getRadius();
        m_pGraphics->DrawLine3DQueued(CVector(pos.fX, pos.fY, pos.fZ - fRadius / 2), CVector(pos.fX, pos.fY, pos.fZ + fRadius / 2), fLineWidth, colorBlue,
                                      false);
    }
}

CClientPhysics::~CClientPhysics()
{
    Unlink();
}

void CClientPhysics::Unlink()
{
    m_pManager->GetPhysicsManager()->RemoveFromList(this);
}
