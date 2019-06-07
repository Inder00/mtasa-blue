/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientColPolygon.cpp
 *  PURPOSE:     Polygon-shaped collision entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

CClientColLine::CClientColLine(CClientManager* pManager, ElementID ID, CVector vecStart, CVector vecEnd,
                               bool bRoundStart, bool bRoundEnd, float fWidth)
    : ClassInit(this), CClientColShape(pManager, ID)
{
    m_pManager = pManager;
    m_vecPosition = (vecStart + vecEnd) / 2;

    g_pCore->GetConsole()->Printf("a %.2f %.2f %.f2", vecStart.fX, vecStart.fY, vecStart.fZ);
    g_pCore->GetConsole()->Printf("b %.2f %.2f %.f2", vecEnd.fX, vecEnd.fY, vecEnd.fZ);
    g_pCore->GetConsole()->Printf("a+b/2 %.2f %.2f %.f2", m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ);
    m_vecStart = vecStart;
    m_vecEnd = vecEnd;
    m_bRoundStart = bRoundStart;
    m_bRoundEnd = bRoundEnd;
    m_fWidth = fWidth;

    // That's only to speed up things by not checking the polygon collision,
    // if the point is not even in the bounds
    m_fRadius = 0;
}

bool CClientColLine::DoHitDetection(const CVector& vecNowPosition, float fRadius)
{
    if (!IsInBounds(vecNowPosition))
        return false;

    g_pCore->GetConsole()->Print("DoHitDetection");
    bool collides = false;

    return collides;
}

void CClientColLine::SetPosition(const CVector& vecPosition)
{
    g_pCore->GetConsole()->Print("SetPosition");
    CVector vecDifference = m_vecPosition - vecPosition;
    m_vecStart -= vecDifference;
    m_vecEnd -= vecDifference;

    m_vecPosition = vecPosition;
    UpdateSpatialData();
    // Add queued collider refresh for v1.1
}

bool CClientColLine::IsInBounds(CVector vecPoint)
{
    g_pCore->GetConsole()->Print("IsInBounds");
    float fDistanceX = vecPoint.fX - m_vecPosition.fX;
    float fDistanceY = vecPoint.fY - m_vecPosition.fY;

    float fDist = sqrt(fDistanceX * fDistanceX + fDistanceY * fDistanceY);

    return fDist <= m_fRadius;
}

CSphere CClientColLine::GetWorldBoundingSphere()
{
    g_pCore->GetConsole()->Print("GetWorldBoundingSphere");
    CSphere sphere;
    sphere.vecPosition = m_vecPosition;
    sphere.fRadius = m_fRadius;
    return sphere;
}

//
// Draw wireframe line
//
void CClientColLine::DebugRender(const CVector& vecPosition, float fDrawRadius)
{
    g_pCore->GetConsole()->Print("render line");
    SColorARGB          color(151, 51, 255, 0);
    float               fLineWidth = 4.f + pow(m_fRadius, 0.5f);
    CGraphicsInterface* pGraphics = g_pCore->GetGraphics();

    pGraphics->DrawLine3DQueued(m_vecStart, m_vecEnd, fLineWidth, color, false);
}
