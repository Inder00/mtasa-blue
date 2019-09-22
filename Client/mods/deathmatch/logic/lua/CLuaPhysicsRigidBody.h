/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/logic/lua/CLuaTimer.h
 *  PURPOSE:     Lua timer class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CLuaPhysicsRigidBody;

#pragma once

// Define includes
#include "LuaCommon.h"
#include "CLuaArguments.h"

class CLuaPhysicsRigidBody
{
public:
    CLuaPhysicsRigidBody(CClientPhysics* pPhysics, const CVector& vec = CVector());
    ~CLuaPhysicsRigidBody();

    void RemoveScriptID();
/*
    CTickCount GetStartTime() const { return m_llStartTime; };
    void       SetStartTime(CTickCount llStartTime) { m_llStartTime = llStartTime; };

    unsigned int GetRepeats() const { return m_uiRepeats; };
    void         SetRepeats(unsigned int uiRepeats) { m_uiRepeats = uiRepeats; }*/

    uint               GetScriptID() const { return m_uiScriptID; }
    static CLuaPhysicsRigidBody* GetFromScriptID(unsigned int uiScriptID);

    void CreateBox(const CVector& size, float fMass);
    void CreateSphere(float fRadius, float fMass);
    void GetMatrix(CMatrix& matrix);
    void SetPosition(CVector vecPosition);
    void SetType(rp3d::BodyType eType);

    rp3d::ProxyShape* GetProxyShapesList() { return m_pRigidBody->getProxyShapesList(); };

private:
    uint            m_uiScriptID;

    rp3d::RigidBody* m_pRigidBody;
};
