/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/CObjectSA.cpp
 *  PURPOSE:     Object entity
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#include "gamesa_renderware.h"

//#define MTA_USE_BUILDINGS_AS_OBJECTS

// GTA uses this to pass to CFileLoader::LoadObjectInstance the info it wants to load
struct CFileObjectInstance
{
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;
    float rr;            // = 1
    DWORD modelId;
    DWORD areaNumber;
    long  flags;            // = -1
};


namespace
{
    void CMatrixToRwMatrix(const CMatrix& mat, RwMatrix& rwOutMatrix)
    {
        rwOutMatrix.right = (RwV3d&)mat.vRight;
        rwOutMatrix.up = (RwV3d&)mat.vFront;
        rwOutMatrix.at = (RwV3d&)mat.vUp;
        rwOutMatrix.pos = (RwV3d&)mat.vPos;
    }

    void RwMatrixToCMatrix(const RwMatrix& rwMatrix, CMatrix& matOut)
    {
        matOut.vRight = (CVector&)rwMatrix.right;
        matOut.vFront = (CVector&)rwMatrix.up;
        matOut.vUp = (CVector&)rwMatrix.at;
        matOut.vPos = (CVector&)rwMatrix.pos;
    }

    void RwMatrixGetRotation(const RwMatrix& rwMatrix, CVector& vecOutRotation)
    {
        CMatrix matTemp;
        RwMatrixToCMatrix(rwMatrix, matTemp);
        vecOutRotation = matTemp.GetRotation();
    }

    void RwMatrixSetRotation(RwMatrix& rwInOutMatrix, const CVector& vecRotation)
    {
        CMatrix matTemp;
        RwMatrixToCMatrix(rwInOutMatrix, matTemp);
        matTemp.SetRotation(vecRotation);
        rwInOutMatrix.right = (RwV3d&)matTemp.vRight;
        rwInOutMatrix.up = (RwV3d&)matTemp.vFront;
        rwInOutMatrix.at = (RwV3d&)matTemp.vUp;
    }

    void RwMatrixGetPosition(const RwMatrix& rwMatrix, CVector& vecOutPosition) { vecOutPosition = (CVector&)rwMatrix.pos; }

    void RwMatrixSetPosition(RwMatrix& rwInOutMatrix, const CVector& vecPosition) { rwInOutMatrix.pos = (RwV3d&)vecPosition; }

    void RwMatrixGetScale(const RwMatrix& rwMatrix, CVector& vecOutScale)
    {
        CMatrix matTemp;
        RwMatrixToCMatrix(rwMatrix, matTemp);
        vecOutScale = matTemp.GetScale();
    }

    void RwMatrixSetScale(RwMatrix& rwInOutMatrix, const CVector& vecScale)
    {
        CMatrix matTemp;
        RwMatrixToCMatrix(rwInOutMatrix, matTemp);
        matTemp.SetScale(vecScale);
        rwInOutMatrix.right = (RwV3d&)matTemp.vRight;
        rwInOutMatrix.up = (RwV3d&)matTemp.vFront;
        rwInOutMatrix.at = (RwV3d&)matTemp.vUp;
    }

    bool ClumpDumpCB(RpAtomic* pAtomic, void* data)
    {
        CObjectSA* pObjectSA = (CObjectSA*)data;
        RwFrame*    pFrame = RpGetFrame(pAtomic);
        pObjectSA->AddComponent(pFrame, false);
        // g_pCore->GetConsole()->Print ( SString ( "Atomic:%08x  Frame:%08x %s", pAtomic, pFrame, pFrame ? pFrame->szName : "" ) );
        // OutputDebugLine ( SString ( "Atomic:%08x  Frame:%08x %s", pAtomic, pFrame, pFrame ? pFrame->szName : "" ) );
        return true;
    }

    void ClumpDump(RpClump* pClump, CObjectSA* pObjectSA)
    {
        // get the clump's frame
        RwFrame* pFrame = RpGetFrame(pClump);
        // OutputDebugLine ( SStringX ( "--------------------------------" ) );
        // OutputDebugLine ( SString ( "Clump:%08x  Frame:%08x %s", pClump, pFrame, pFrame ? pFrame->szName : "" ) );
        // g_pCore->GetConsole()->Print ( SStringX ( "--------------------------------" ) );
        // g_pCore->GetConsole()->Print ( SString ( "Clump:%08x  Frame:%08x %s", pClump, pFrame, pFrame ? pFrame->szName : "" ) );
        // Do for all atomics
        RpClumpForAllAtomics(pClump, ClumpDumpCB, pObjectSA);
    }

    // Recursive RwFrame children searching function
    void RwFrameDump(RwFrame* parent, CObjectSA* pObjectSA)
    {
        RwFrame* ret = parent->child;
        while (ret != NULL)
        {
            // recurse into the child
            if (ret->child != NULL)
            {
                RwFrameDump(ret, pObjectSA);
            }
            // don't re-add, check ret for validity, if it has an empty string at this point it isn't a variant or it's already added
            if (pObjectSA->IsComponentPresent(ret->szName) == false && ret->szName != "")
            {
                pObjectSA->AddComponent(ret, true);
            }
            ret = ret->next;
        }
    }

    void ObjectDump(CObjectSA* pObjectSA)
    {
        if (pObjectSA->GetInterface()->m_pRwObject != nullptr)
        {
            // This grabs 90% of the frames
            ClumpDump(pObjectSA->GetInterface()->m_pRwObject, pObjectSA);
            // This grabs the rest which aren't always copied to the Model Info in the interface ( usually markers for things like NOS )
            RwFrameDump(RpGetFrame((RpClump*)pGame->GetModelInfo(pObjectSA->GetModelIndex())->GetRwObject()), pObjectSA);
        }
    }

    RwObject* __cdecl GetAllAtomicObjectCB(struct RwObject* object, void* data)
    {
        std::vector<RwObject*>& result = *((std::vector<RwObject*>*)data);
        result.push_back(object);
        return object;
    }

    // Get all atomics for this frame (even if they are invisible)
    void GetAllAtomicObjects(RwFrame* frame, std::vector<RwObject*>& result) { RwFrameForAllObjects(frame, (void*)GetAllAtomicObjectCB, &result); }
}            // namespace


CObjectSA::CObjectSA(CObjectSAInterface* objectInterface)
{
    DEBUG_TRACE("CObjectSA::CObjectSA(CObjectSAInterface * objectInterface)");
    this->SetInterface(objectInterface);
    m_ucAlpha = 255;

    // Setup some flags
    this->BeingDeleted = FALSE;
    this->DoNotRemoveFromGame = FALSE;

    if (m_pInterface)
    {
        ResetScale();
        CheckForGangTag();
        m_pInterface->bStreamingDontDelete = true;
    }
}

CObjectSA::CObjectSA(DWORD dwModel, bool bBreakingDisabled)
{
    DEBUG_TRACE("CObjectSA::CObjectSA( DWORD dwModel )");

    CWorldSA* world = (CWorldSA*)pGame->GetWorld();

    DWORD dwThis = 0;

#ifdef MTA_USE_BUILDINGS_AS_OBJECTS

    DWORD               dwFunc = 0x538090;            // CFileLoader__LoadObjectInstance
    CFileObjectInstance fileLoader;
    MemSetFast(&fileLoader, 0, sizeof(CFileObjectInstance));
    fileLoader.modelId = dwModel;
    fileLoader.rr = 1;
    fileLoader.areaNumber = 0;
    fileLoader.flags = -1;

    _asm
    {
        push    0
        lea     ecx, fileLoader
        push    ecx
        call    dwFunc
        add     esp, 8
        mov     dwThis, eax
    }

    this->SetInterface((CEntitySAInterface*)dwThis);

    MemPutFast<DWORD>(0xBCC0E0, dwThis);
    MemPutFast<DWORD>(0xBCC0D8, 1);

    dwFunc = 0x404DE0;            // CIplStore__SetupRelatedIpls
    DWORD dwTemp = 0;
    char  szTemp[255];
    strcpy(szTemp, "moo");

    _asm
    {
        push    0xBCC0E0
        push    -1
        lea     eax, szTemp
        push    eax
        call    dwFunc
        add     esp, 0xC
        mov     dwTemp, eax
    }

    dwFunc = 0x5B51E0;            // AddBuildingInstancesToWorld
    _asm
    {
        push    dwTemp
        call    dwFunc
        add     esp, 4
    }

    dwFunc = 0x405110;            // CIplStore__RemoveRelatedIpls
    _asm
    {
        push    -1
        call    dwFunc
        add     esp, 4
    }

    // VITAL to get colmodels to appear
    // this gets the level for a colmodel (colmodel+40)
    dwFunc = 0x4107A0;
    _asm
    {
        mov     eax, dwModel
        mov     eax, 0xA9B0C8[eax*4]
        mov     eax, [eax+20]
        movzx   eax, byte ptr [eax+40]
        push    eax
        call    dwFunc
        add     esp, 4
    }

#else

    DWORD CObjectCreate = FUNC_CObject_Create;
    DWORD dwObjectPtr = 0;
    _asm
    {
        push    1
        push    dwModel
        call    CObjectCreate
        add     esp, 8
        mov     dwObjectPtr, eax
    }
    if (dwObjectPtr)
    {
        this->SetInterface((CEntitySAInterface*)dwObjectPtr);

        world->Add(m_pInterface, CObject_Constructor);

        // Setup some flags
        this->BeingDeleted = FALSE;
        this->DoNotRemoveFromGame = FALSE;
        MemPutFast<BYTE>(dwObjectPtr + 316, 6);
        if (bBreakingDisabled)
        {
            // Set our immunities
            // Sum of all flags checked @ CPhysical__CanPhysicalBeDamaged
            CObjectSAInterface* pObjectSAInterface = GetObjectInterface();
            pObjectSAInterface->bBulletProof = true;
            pObjectSAInterface->bFireProof = true;
            pObjectSAInterface->bCollisionProof = true;
            pObjectSAInterface->bMeeleProof = true;
            pObjectSAInterface->bExplosionProof = true;
        }
        m_pInterface->bStreamingDontDelete = true;
    }
    else
    {
        // The exception handler doesn't work for some reason, so do this
        this->SetInterface(NULL);
    }
#endif

    this->internalID = pGame->GetPools()->GetObjectRef((DWORD*)this->GetInterface());

    m_ucAlpha = 255;

    if (m_pInterface)
    {
        ResetScale();
        CheckForGangTag();

        m_ExtraFrames.clear();

        ObjectDump(this);
    }
}

CObjectSA::~CObjectSA()
{
    DEBUG_TRACE("CObjectSA::~CObjectSA( )");
    // OutputDebugString("Attempting to destroy Object\n");
    if (!this->BeingDeleted && DoNotRemoveFromGame == false)
    {
        DWORD dwInterface = (DWORD)this->GetInterface();
        if (dwInterface)
        {
            if ((DWORD)this->GetInterface()->vtbl != VTBL_CPlaceable)
            {
                CWorldSA* world = (CWorldSA*)pGame->GetWorld();
                world->Remove(this->GetInterface(), CObject_Destructor);

                DWORD dwFunc = this->GetInterface()->vtbl->SCALAR_DELETING_DESTRUCTOR;            // we use the vtbl so we can be type independent
                _asm
                {
                    mov     ecx, dwInterface
                    push    1            // delete too
                    call    dwFunc
                }

#ifdef MTA_USE_BUILDINGS_AS_OBJECTS
                DWORD dwModelID = this->internalInterface->m_nModelIndex;
                // REMOVE ref to colstore thingy
                dwFunc = 0x4107D0;
                _asm
                {
                    mov     eax, dwModelID
                    mov     eax, 0xA9B0C8[eax*4]
                    mov     eax, [eax+20]
                    movzx   eax, byte ptr [eax+40]
                    push    eax
                    call    dwFunc
                    add     esp, 4
                }
#endif
            }
        }

        this->BeingDeleted = true;
        ((CPoolsSA*)pGame->GetPools())->RemoveObject((CObject*)(CObjectSA*)this);

        // OutputDebugString("Destroying Object\n");
    }
}

void CObjectSA::Explode()
{
    DWORD dwFunc = FUNC_CObject_Explode;
    DWORD dwThis = (DWORD)this->GetInterface();

    _asm
    {
        mov     ecx, dwThis
        call    dwFunc
    }
}

void CObjectSA::Break()
{
    DWORD dwFunc = 0x5A0D90;
    DWORD dwThis = (DWORD)GetInterface();

    float fHitVelocity = 1000.0f;            // has no direct influence, but should be high enough to trigger the break (effect)

    _asm
    {
        push    32h // most cases: between 30 and 37
        push    0 // colliding entity. To ignore it, we can set it to 0
        push    0B73710h // vecCollisionImpactVelocity
        push    0 // vecCollisionLastPos
        push    fHitVelocity
        mov     ecx, dwThis
        call    dwFunc
    }

    if (IsGlass())
    {
        float fX = 0.0f;
        float fY = 0.0f;
        float fZ = 0.0f;
        dwFunc = FUNC_CGlass_WindowRespondsToCollision;

        _asm
        {
            push 0
            push fZ
            push fY
            push fX
            push 0
            push 0
            push 0
            push fHitVelocity
            push dwThis
            call dwFunc
            add esp, 24h
        }
    }
}

void CObjectSA::SetHealth(float fHealth)
{
    static_cast<CObjectSAInterface*>(this->GetInterface())->fHealth = fHealth;
}

float CObjectSA::GetHealth(void)
{
    return static_cast<CObjectSAInterface*>(this->GetInterface())->fHealth;
}

void CObjectSA::SetModelIndex(unsigned long ulModel)
{
    // Delete any existing RwObject first
    DWORD dwFunc = this->GetInterface()->vtbl->DeleteRwObject;
    DWORD dwThis = (DWORD)this->GetInterface();
    _asm
        {
        mov     ecx, dwThis
        call    dwFunc
        }

    // Jax: I'm not sure if using the vtbl is right (as ped and vehicle dont), but it works
    dwFunc = this->GetInterface()->vtbl->SetModelIndex;
    _asm
        {
        mov     ecx, dwThis
        push    ulModel
        call    dwFunc
        }

    CheckForGangTag();
}

void CObjectSA::CheckForGangTag()
{
    switch (GetModelIndex())
    {
        case 1524:
        case 1525:
        case 1526:
        case 1527:
        case 1528:
        case 1529:
        case 1530:
        case 1531:
            m_bIsAGangTag = true;
            break;
        default:
            m_bIsAGangTag = false;
            break;
    }
}

bool CObjectSA::IsGlass()
{
    DWORD dwFunc = 0x46A760;
    DWORD dwThis = (DWORD)GetInterface();
    bool  bResult;

    _asm
    {
        push dwThis
        call dwFunc
        mov bResult, al
        add esp, 4
    }
    return bResult;
}

void CObjectSA::SetScale(float fX, float fY, float fZ)
{
    m_vecScale = CVector(fX, fY, fZ);
    GetObjectInterface()->bUpdateScale = true;
    GetObjectInterface()->fScale = std::max(fX, std::max(fY, fZ));
}

CVector* CObjectSA::GetScale()
{
    return &m_vecScale;
}

void CObjectSA::ResetScale()
{
    SetScale(1.0f, 1.0f, 1.0f);
}

void CObjectSA::UpdateComponents(void)
{
    m_ExtraFrames.clear();
    ObjectDump(this);
    FinalizeFramesList();
}


SObjectFrame* CObjectSA::GetObjectComponent(const SString& objectComponent)
{
    return MapFind(m_ExtraFrames, objectComponent);
}

bool CObjectSA::SetComponentRotation(const SString& objectComponent, const CVector& vecRotation)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixSetRotation(pComponent->pFrame->ltm, vecRotation);
        return true;
    }
    return false;
}

bool CObjectSA::GetComponentRotation(const SString& objectComponent, CVector& vecRotation)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixGetRotation(pComponent->pFrame->ltm, vecRotation);
        return true;
    }
    return false;
}

bool CObjectSA::SetComponentPosition(const SString& objectComponent, const CVector& vecPosition)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixSetPosition(pComponent->pFrame->ltm, vecPosition);
        return true;
    }
    return false;
}

bool CObjectSA::GetComponentPosition(const SString& objectComponent, CVector& vecPositionModelling)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixGetPosition(pComponent->pFrame->ltm, vecPositionModelling);
        return true;
    }
    return false;
}

bool CObjectSA::SetComponentScale(const SString& objectComponent, const CVector& vecScale)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixSetScale(pComponent->pFrame->ltm, vecScale);
        return true;
    }
    return false;
}

bool CObjectSA::GetComponentScale(const SString& objectComponent, CVector& vecScaleModelling)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixGetScale(pComponent->pFrame->ltm, vecScaleModelling);
        return true;
    }
    return false;
}

bool CObjectSA::IsComponentPresent(const SString& objectComponent)
{
    return GetObjectComponent(objectComponent) != NULL;
}

bool CObjectSA::GetComponentMatrix(const SString& objectComponent, CMatrix& matOutOrientation)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    // Check validty
    if (pComponent && pComponent->pFrame != NULL)
    {
        RwMatrixToCMatrix(pComponent->pFrame->ltm, matOutOrientation);
        return true;
    }
    return false;
}

bool CObjectSA::SetComponentMatrix(const SString& objectComponent, const CMatrix& matOrientation)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    // Check validty
    if (pComponent && pComponent->pFrame != NULL)
    {
        CMatrixToRwMatrix(matOrientation, pComponent->pFrame->ltm);
        return true;
    }
    return false;
}

// Get transform from component parent to the model root
bool CObjectSA::GetComponentParentToRootMatrix(const SString& objectComponent, CMatrix& matOutParentToRoot)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    // Check validty
    if (pComponent && pComponent->pFrame != NULL)
    {
        // Calc root to parent transform
        CMatrix matCombo;
        for (uint i = 0; i < pComponent->frameList.size(); i++)
        {
            RwFrame* pFrame = pComponent->frameList[i];
            if (pFrame)
            {
                CMatrix matFrame;
                RwMatrixToCMatrix(pFrame->ltm, matFrame);
                matCombo = matFrame * matCombo;
            }
        }
        matOutParentToRoot = matCombo;
        return true;
    }
    return false;
}

void CObjectSA::AddComponent(RwFrame* pFrame, bool bReadOnly)
{
    // if the frame is invalid we don't want to be here
    if (!pFrame)
        return;
    // if the frame already exists ignore it
    if (IsComponentPresent(pFrame->szName) || pFrame->szName == "")
        return;

    SString strName = pFrame->szName;
    SObjectFrame frame = SObjectFrame(pFrame, bReadOnly);
    // insert our new frame
    m_ExtraFrames.insert(std::pair<SString, SObjectFrame>(strName, frame));
}

void CObjectSA::FinalizeFramesList(void)
{
    // For each frame, make list of parent frames
    std::map<SString, SObjectFrame>::iterator iter = m_ExtraFrames.begin();
    for (; iter != m_ExtraFrames.end(); ++iter)
    {
        SObjectFrame& vehicleFrame = iter->second;
        dassert(vehicleFrame.frameList.empty());
        vehicleFrame.frameList.clear();

        // Get frame list from parent component down to the root
        RwFrame* pParent = (RwFrame*)vehicleFrame.pFrame->object.parent;
        for (; pParent && pParent != pParent->root; pParent = (RwFrame*)pParent->object.parent)
        {
            // Get parent frame by name from our list instead of the RwFrame structure
            SObjectFrame* parentObjectFrame = GetObjectComponent(pParent->szName);
            if (parentObjectFrame && parentObjectFrame->pFrame != NULL)
            {
                vehicleFrame.frameList.insert(vehicleFrame.frameList.begin(), parentObjectFrame->pFrame);
            }
        }
    }
}

bool CObjectSA::SetComponentVisible(const SString& objectComponent, bool bRequestVisible)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    // Check validty
    if (pComponent && pComponent->pFrame != NULL && pComponent->bReadOnly == false)
    {
        RwFrame* pFrame = pComponent->pFrame;
        // Get all atomics for this component - Usually one, or two if there is a damaged version
        std::vector<RwObject*> atomicList;
        GetAllAtomicObjects(pFrame, atomicList);

        // Count number currently visible
        uint uiNumAtomicsCurrentlyVisible = 0;
        for (uint i = 0; i < atomicList.size(); i++)
            if (atomicList[i]->flags & 0x04)
                uiNumAtomicsCurrentlyVisible++;

        if (bRequestVisible && uiNumAtomicsCurrentlyVisible == 0)
        {
            // Make atomic (undamaged version) visible. TODO - Check if damaged version should be made visible instead
            for (uint i = 0; i < atomicList.size(); i++)
            {
                RwObject* pAtomic = atomicList[i];
                int       AtomicId = pGame->GetVisibilityPlugins()->GetAtomicId(pAtomic);

                if (!(AtomicId & ATOMIC_ID_FLAG_TWO_VERSIONS_DAMAGED))
                {
                    // Either only one version, or two versions and this is the undamaged one
                    pAtomic->flags |= 0x04;
                }
            }
        }
        else if (!bRequestVisible && uiNumAtomicsCurrentlyVisible > 0)
        {
            // Make all atomics invisible
            for (uint i = 0; i < atomicList.size(); i++)
                atomicList[i]->flags &= ~0x05;            // Mimic what GTA seems to do - Not sure what the bottom bit is for
        }
        return true;
    }
    return false;
}

bool CObjectSA::GetComponentVisible(const SString& objectComponent, bool& bOutVisible)
{
    SObjectFrame* pComponent = GetObjectComponent(objectComponent);
    // Check validty
    if (pComponent && pComponent->pFrame != NULL && pComponent->bReadOnly == false)
    {
        RwFrame* pFrame = pComponent->pFrame;
        // Get all atomics for this component - Usually one, or two if there is a damaged version
        std::vector<RwObject*> atomicList;
        GetAllAtomicObjects(pFrame, atomicList);

        // Count number currently visible
        uint uiNumAtomicsCurrentlyVisible = 0;
        for (uint i = 0; i < atomicList.size(); i++)
            if (atomicList[i]->flags & 0x04)
                uiNumAtomicsCurrentlyVisible++;

        // Set result
        bOutVisible = (uiNumAtomicsCurrentlyVisible > 0);
        return true;
    }
    return false;
}
