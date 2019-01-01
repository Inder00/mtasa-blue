/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/game/CObject.h
 *  PURPOSE:     Object entity interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPhysical.h"

class CPed;
class CObject;
class CColModel;

struct SObjectFrame
{
    SObjectFrame(RwFrame* pFrame = NULL, bool bReadOnly = true) : pFrame(pFrame), bReadOnly(bReadOnly) {}

    RwFrame*              pFrame;
    bool                  bReadOnly;
    std::vector<RwFrame*> frameList;            // Frames from root to parent
};

class CVehicle;
class CPed;
class CObjectSAInterface;

class CObject : public virtual CPhysical
{
public:
    virtual ~CObject(void){};

    virtual CObjectSAInterface* GetObjectInterface(void) = 0;

    virtual void  Explode(void) = 0;
    virtual void  Break(void) = 0;
    virtual void  SetHealth(float fHealth) = 0;
    virtual float GetHealth(void) = 0;
    virtual void  SetModelIndex(unsigned long ulModel) = 0;

    virtual void          SetAlpha(unsigned char ucAlpha) = 0;
    virtual unsigned char GetAlpha() = 0;

    virtual bool IsAGangTag() const = 0;
    virtual bool IsGlass() = 0;

    virtual void     SetScale(float fX, float fY, float fZ) = 0;
    virtual CVector* GetScale() = 0;
    virtual void     ResetScale() = 0;
    virtual void     UpdateComponents() = 0;
    virtual bool                              SetComponentRotation(const SString& vehicleComponent, const CVector& vecRotation) = 0;
    virtual bool                              GetComponentRotation(const SString& vehicleComponent, CVector& vecRotation) = 0;
    virtual bool                              SetComponentPosition(const SString& vehicleComponent, const CVector& vecPosition) = 0;
    virtual bool                              GetComponentPosition(const SString& vehicleComponent, CVector& vecPositionModelling) = 0;
    virtual bool                              SetComponentScale(const SString& vehicleComponent, const CVector& vecScale) = 0;
    virtual bool                              GetComponentScale(const SString& vehicleComponent, CVector& vecScaleModelling) = 0;
    virtual bool                              IsComponentPresent(const SString& vehicleComponent) = 0;
    virtual bool                              SetComponentMatrix(const SString& vehicleComponent, const CMatrix& matOrientation) = 0;
    virtual bool                              GetComponentMatrix(const SString& vehicleComponent, CMatrix& matOutOrientation) = 0;
    virtual bool                              GetComponentParentToRootMatrix(const SString& vehicleComponent, CMatrix& matOutParentToRoot) = 0;
    virtual bool                              SetComponentVisible(const SString& vehicleComponent, bool bVisible) = 0;
    virtual bool                              GetComponentVisible(const SString& vehicleComponent, bool& bVisible) = 0;
    virtual std::map<SString, SObjectFrame>& GetComponentMap(void) = 0;
};
