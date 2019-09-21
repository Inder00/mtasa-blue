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
    dynamicsWorld = new DynamicsWorld(gravity);

    m_pGraphics = g_pCore->GetGraphics();
    m_LastTimeMs = CTickCount::Now();

    Vector3    position(10.0, 5.0, 0.0);
    Quaternion orientation = Quaternion::identity();
    Transform  transform(position, orientation);

    // Mass of the collision shape (in kilograms)
    decimal mass = decimal(4.0);

    // Add the collision shape to the rigid body
    ProxyShape* proxyShape;

    Quaternion quaternion1 = Quaternion::identity();
    Transform  transform1(Vector3(), quaternion1);

    RigidBody* plane = dynamicsWorld->createRigidBody(transform1);
    plane->enableGravity(false);
    plane->setType(BodyType::STATIC);

    const Vector3 halfExtents(30, 30, 4.0);
    BoxShape*     box = new BoxShape(halfExtents);

    Transform transformIdentity = Transform::identity();
    transformIdentity.setPosition(Vector3(15, 15, 0));
    plane->addCollisionShape(box, transformIdentity, decimal(1.0));

    vecRigidBodies.push_back(plane);

    for (int i = 0; i < 10; i++)
    {
        SpawnBox(CVector(1, 1, 1), CVector(0, 0.5f, 10 * i + 50));
    }
    for (int i = 0; i < 10; i++)
    {
        SpawnBox(CVector(2, 2, 2), CVector(0, 0, 10 * i + 10));
    }

    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            SpawnBox(CVector(1, 1, 1), CVector(k-5, i-5, 500));
        }
    }
}

void CClientPhysics::SpawnBox(CVector size, CVector position)
{
    const Vector3 halfExtents(size.fX, size.fY, size.fZ);
    BoxShape*     box = new BoxShape(halfExtents);
    Transform     transform(Vector3(position.fX, position.fY, position.fZ), Quaternion::identity());
    RigidBody*    body = dynamicsWorld->createRigidBody(transform);
    body->addCollisionShape(box, Transform::identity(), decimal(1.0));
    vecRigidBodies.push_back(body);
}

CVector QuaternionToEuler(Quaternion q)
{
    double q0 = q.w;
    double q1 = q.y;
    double q2 = q.x;
    double q3 = q.z;

    CVector radAngles;
    radAngles.fX = (float)std::atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (std::pow(q1, 2) + std::pow(q2, 2)));
    radAngles.fY = (float)std::asin(2 * (q0 * q2 - q3 * q1));
    radAngles.fZ = (float)std::atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (std::pow(q2, 2) + std::pow(q3, 2)));

    return radAngles;
}

#define RadiansToDegrees(radians) radians * 180.0 / 3.141592
void CClientPhysics::Update()
{
    CTickCount tickCountNow = CTickCount::Now();

    int iDeltaTimeMs = (int)(tickCountNow - m_LastTimeMs).ToLongLong();
    m_LastTimeMs = tickCountNow;
    const float timeStep = 1.0 / 60.0;
    const float deg2rad = 57.2957795f;
    dynamicsWorld->update(((float)iDeltaTimeMs) / 1000.0f);
    int         i = 0;
    Vector3     vec;
    float       angle;
    CMatrix     matrix;
    float       buffer[16];
    ProxyShape* pShapeList;
    for (const auto& body : vecRigidBodies)
    {
        matrix.SetPosition(*(CVector*)&body->getTransform().getPosition());
        matrix.SetRotation(QuaternionToEuler(body->getTransform().getOrientation()));

        pShapeList = body->getProxyShapesList();
        do
        {
            RenderDebug(pShapeList->getCollisionShape(), matrix);

        } while (pShapeList = pShapeList->getNext());

        // g_pCore->GetConsole()->Printf("update %i: %.2f, %.2f, %.2f, Velocity: %.2f, %.2f, %.2f", i, (float)vec1.x, (float)vec1.y, (float)vec1.z,
        // (float)vec2.x,
        //                              (float)vec2.y, (float)vec2.z);
        i++;
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
    matrix.SetPosition(CVector(0, 0, 0));
    // used if else due switch require declare variables outside
    if (eShapeName == CollisionShapeName::BOX)
    {
        SColorARGB color1(0, 255, 0, 255);
        SColorARGB color2(0, 0, 255, 255);
        BoxShape*  eBox = (BoxShape*)pShape;
        Vector3    extent = eBox->getExtent();

        CVector corners[8];
        for (int i = 0; i < 8; i++)
        {
            corners[i] = matrix.TransformVector(*(CVector*)&eBox->getVertexPosition(i)) + pos;
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
