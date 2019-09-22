/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/logic/lua/CLuaPhysicsRigidBody.cpp
 *  PURPOSE:     Lua rigid body class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include <StdInc.h>
#include "reactphysics3d.h"

using namespace reactphysics3d;

#define RadiansToDegrees(radians) radians * 180.0 / PI
#define DegreesToRadians(radians) radians* PI / 180.0;
CVector QuaternionToEuler(Quaternion q)
{
    double q0 = q.w;
    double q1 = q.x;
    double q2 = q.y;
    double q3 = q.z;

    CVector radAngles;
    radAngles.fX = (float)std::atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (std::pow(q1, 2) + std::pow(q2, 2)));
    radAngles.fY = (float)std::asin(2 * (q0 * q2 - q3 * q1));
    radAngles.fZ = (float)std::atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (std::pow(q2, 2) + std::pow(q3, 2)));

    return radAngles;
}

CLuaPhysicsRigidBody::CLuaPhysicsRigidBody(CClientPhysics* pPhysics, const CVector& vec)
{
    m_pRigidBody = pPhysics->CreateWorldRigidBody();
    m_uiScriptID = CIdArray::PopUniqueId(this, EIdClass::PHYSICS_RIGIDBODY);
}

CLuaPhysicsRigidBody::~CLuaPhysicsRigidBody()
{
    RemoveScriptID();
}

void CLuaPhysicsRigidBody::RemoveScriptID()
{
    if (m_uiScriptID != INVALID_ARRAY_ID)
    {
        CIdArray::PushUniqueId(this, EIdClass::PHYSICS_RIGIDBODY, m_uiScriptID);
        m_uiScriptID = INVALID_ARRAY_ID;
    }
}

CLuaPhysicsRigidBody* CLuaPhysicsRigidBody::GetFromScriptID(unsigned int uiScriptID)
{
    CLuaPhysicsRigidBody* pLuaRigidBody = (CLuaPhysicsRigidBody*)CIdArray::FindEntry(uiScriptID, EIdClass::PHYSICS_RIGIDBODY);
    return pLuaRigidBody;
}

void CLuaPhysicsRigidBody::CreateBox(const CVector& size, float fMass)
{
    const Vector3         halfExtents(size.fX, size.fY, size.fZ);
    BoxShape*             box = new BoxShape(halfExtents);
    Transform             transform(Vector3(0,0,0), Quaternion::identity());
    m_pRigidBody->addCollisionShape(box, Transform::identity(), decimal(fMass));
}

void CLuaPhysicsRigidBody::CreateSphere(float fRadius, float fMass)
{
    SphereShape* sphere = new SphereShape(decimal(fRadius));
    Transform    transform(Vector3(0, 0, 0), Quaternion::identity());
    m_pRigidBody->addCollisionShape(sphere, Transform::identity(), decimal(fMass));
}

void CLuaPhysicsRigidBody::SetPosition(CVector vecPosition)
{
    auto transform = m_pRigidBody->getTransform();
    transform.setPosition(Vector3(vecPosition.fX, vecPosition.fY, vecPosition.fZ));
    m_pRigidBody->setTransform(transform);
}

void CLuaPhysicsRigidBody::SetType(rp3d::BodyType eType)
{
    m_pRigidBody->setType(eType);
}

void CLuaPhysicsRigidBody::GetMatrix(CMatrix& matrix)
{
    matrix.SetPosition(*(CVector*)&m_pRigidBody->getTransform().getPosition());
    matrix.SetRotation(QuaternionToEuler(m_pRigidBody->getTransform().getOrientation()));
    matrix.SetScale(CVector(1.0f, 1.0f, 1.0f));
}
