/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientColModel.h
 *  PURPOSE:     Model collision (.col file) entity class
 *
 *****************************************************************************/

#pragma once

#include <list>
#include "CClientEntity.h"
#include "CClientRendererManager.h"

class CClientRenderer : public CClientEntity
{
    DECLARE_CLASS(CClientRenderer, CClientEntity)
public:
    CClientRenderer(class CClientManager* pManager, ElementID ID);
    ~CClientRenderer(void);

    eClientEntityType GetType(void) const { return CCLIENTRENDERER; }

    // Sorta a hack that these are required by CClientEntity...
    void Unlink(void){};
    void GetPosition(CVector& vecPosition) const {};
    void SetPosition(const CVector& vecPosition){};

    void DoPulse();

    int testint = 3;
private:
    CClientRendererManager* m_pRendererManager;
};
