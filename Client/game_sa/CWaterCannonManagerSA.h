/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/CFireManagerSA.h
 *  PURPOSE:     Header file for fire manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <game/CWaterCannonManager.h>
#include "Common.h"
#include "CWaterCannonSA.h"

#define FUNC_ExtinguishPoint            0x539450

#define FUNC_StartFire                  0x48EC30
#define FUNC_StartFire_Vec              0x539F00 // ##SA##

#define ARRAY_CFire             (VAR_CFireCount + 4)

#define CLASS_CFireManager      0xB71F80 //##SA##

#define DEFAULT_FIRE_PARTICLE_SIZE      1.8

#define MAX_WATER_CANNONS               3 //##SA##

class CWaterCannonManagerSA : public CWaterCannonManager
{
private:
    CWaterCannonSA* Fires[MAX_WATER_CANNONS];

public:
    // constructor
    CWaterCannonManagerSA();
    ~CWaterCannonManagerSA();

    //VOID   ExtinguishPoint(CVector& vecPosition, float fRadius);

};
