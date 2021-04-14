/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/core/CCoreBasicInterface.h
 *  PURPOSE:     Core interface with most basic functionality
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

class CCoreBasicInterface
{
public:
    virtual HWND GetHookedWindow() = 0;
};
