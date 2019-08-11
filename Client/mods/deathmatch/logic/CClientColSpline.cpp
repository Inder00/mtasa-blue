/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientColSpline.cpp
 *  PURPOSE:     Spline-shaped collision entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

using namespace SplineLib;

CClientColSpline::CClientColSpline(CClientManager* pManager, ElementID ID, std::vector<CVector> vecPointList, float fWidth)
    : ClassInit(this), CClientColShape(pManager, ID)
{
    m_pManager = pManager;
    m_vecPosition = CVector(0, 0, 0);

    const int size = vecPointList.size();
    const int numPoints = sizeof(size) / sizeof(vecPointList[0]);

    cSpline3 splines[numPoints + 1];

    int numSplines = SplinesFromPoints(numPoints, (Vec3f*)vecPointList.data(), numPoints + 1, splines);

    int   index;
    Vec3f qp;
    qp.x = 0;
    qp.y = 0;
    qp.z = 0;
    float t = FindClosestPoint(qp, numSplines, splines, &index);

    Vec3f cp = Position(splines[index], t);

    g_pCore->GetConsole()->Printf("cp %.2f %.2f %.f2", cp.x, cp.y, cp.z);
    m_fWidth = fWidth;

    // That's only to speed up things by not checking the polygon collision,
    // if the point is not even in the bounds
    m_fRadius = 0;
}

bool CClientColSpline::DoHitDetection(const CVector& vecNowPosition, float fRadius)
{
    if (!IsInBounds(vecNowPosition))
        return false;

    g_pCore->GetConsole()->Print("DoHitDetection");
    bool collides = false;

    return collides;
}

void CClientColSpline::SetPosition(const CVector& vecPosition)
{
    g_pCore->GetConsole()->Print("SetPosition");
    CVector vecDifference = m_vecPosition - vecPosition;
    m_vecStart -= vecDifference;
    m_vecEnd -= vecDifference;

    m_vecPosition = vecPosition;
    UpdateSpatialData();
    // Add queued collider refresh for v1.1
}

bool CClientColSpline::IsInBounds(CVector vecPoint)
{
    g_pCore->GetConsole()->Print("IsInBounds");
    float fDistanceX = vecPoint.fX - m_vecPosition.fX;
    float fDistanceY = vecPoint.fY - m_vecPosition.fY;

    float fDist = sqrt(fDistanceX * fDistanceX + fDistanceY * fDistanceY);

    return fDist <= m_fRadius;
}

CSphere CClientColSpline::GetWorldBoundingSphere()
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
void CClientColSpline::DebugRender(const CVector& vecPosition, float fDrawRadius)
{
    g_pCore->GetConsole()->Print("render line");
    SColorARGB          color(151, 51, 255, 0);
    float               fLineWidth = 4.f + pow(m_fRadius, 0.5f);
    CGraphicsInterface* pGraphics = g_pCore->GetGraphics();

    pGraphics->DrawLine3DQueued(m_vecStart, m_vecEnd, fLineWidth, color, false);
}
