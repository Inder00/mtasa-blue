/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/CCamSA.h
 *  PURPOSE:     Header file for camera entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <game/CWaterCannon.h>
#include "CEntitySA.h"
#include "CAutomobileSA.h"
#include "CPedSA.h"

struct CWaterCannonSAInterface : public CWaterCannonInterface
{
    int     m_nId;
    short   m_nSectionsCount;
    short   _pad;
    int     m_nCreationTime;
    CVector m_avecPoints[64];
    char    m_anSectionState[32];
    char    m_audio[144];            // CAEWaterCannonAudioEntity
    char    field_3BC[16];
};


static_assert(sizeof(CWaterCannonSAInterface) == 0x3CC, "Invalid size for CWaterCannonSAInterface");

class CWaterCannonSA : public CWaterCannon
{
private:
    CWaterCannonSAInterface* m_pInterface;

public:
    CWaterCannonSA(CWaterCannonSAInterface* pInterface) { m_pInterface = pInterface; }
    CWaterCannonSAInterface* GetInterface() { return m_pInterface; }
};
