/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/game/CWorld.h
 *  PURPOSE:     Game world interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once
#include <CVector.h>


class CWaterCannonInterface
{
public:
};

class CWaterCannon
{
public:
    virtual CWaterCannonInterface* GetInterface() = 0;
};
