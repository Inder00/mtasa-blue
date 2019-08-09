/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientColPolygon.h
 *  PURPOSE:     Polygon-shaped collision entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

class CClientColSpline : public CClientColShape
{
    DECLARE_CLASS(CClientColSpline, CClientColShape)
public:
    CClientColSpline(CClientManager* pManager, ElementID ID, std::vector<CVector> vecPointList, float fWidth);

    virtual CSphere GetWorldBoundingSphere();
    virtual void    DebugRender(const CVector& vecPosition, float fDrawRadius);

    eColShapeType GetShapeType() { return COLSHAPE_LINE; }

    bool DoHitDetection(const CVector& vecNowPosition, float fRadius);

    void SetPosition(const CVector& vecPosition);

protected:
    CVector              m_vecStart, m_vecEnd;
    bool                 m_bRoundStart, m_bRoundEnd;
    float                m_fWidth;
    bool IsInBounds(CVector vecPoint);

    float m_fRadius;
};
