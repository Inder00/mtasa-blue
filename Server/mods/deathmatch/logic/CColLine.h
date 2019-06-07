/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CColTube.h
 *  PURPOSE:     Tube-shaped collision entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CColShape.h"

class CColLine : public CColShape
{
public:
    CColLine(CColManager* pManager, CElement* pParent, const CVector& vecPosition, float fRadius, float fHeight);

    virtual CSphere GetWorldBoundingSphere();

    eColShapeType GetShapeType() { return COLSHAPE_LINE; }
    bool          DoHitDetection(const CVector& vecNowPosition);

    float GetRadius() { return m_fRadius; };


protected:
    bool ReadSpecialData(const int iLine) override;

    float m_fRadius;
    float m_fHeight;
};
