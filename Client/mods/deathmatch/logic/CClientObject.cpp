/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientObject.cpp
 *  PURPOSE:     Physical object entity class
 *
 *****************************************************************************/

#include <StdInc.h>

#define MTA_BUILDINGS
#define CCLIENTOBJECT_MAX 250

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

CClientObject::CClientObject(CClientManager* pManager, ElementID ID, unsigned short usModel, bool bLowLod)
    : ClassInit(this), CClientStreamElement(bLowLod ? pManager->GetObjectLodStreamer() : pManager->GetObjectStreamer(), ID), m_bIsLowLod(bLowLod)
{
    // Init
    m_pManager = pManager;
    m_pObjectManager = pManager->GetObjectManager();
    m_pModelRequester = pManager->GetModelRequestManager();

    m_pObject = NULL;
    m_usModel = usModel;

    SetTypeName("object");

    m_usModel = usModel;
    m_bIsVisible = true;
    m_bIsFrozen = false;
    m_bUsesCollision = true;
    m_ucAlpha = 255;
    m_vecScale = CVector(1.0f, 1.0f, 1.0f);
    m_fHealth = 1000.0f;
    m_bBreakingDisabled = false;
    m_bRespawnEnabled = true;
    m_fMass = -1.0f;
    m_fTurnMass = -1.0f;
    m_fAirResistance = -1.0f;
    m_fElasticity = -1.0f;
    m_fBuoyancyConstant = -1.0f;
    m_vecCenterOfMass = CVector(0.0f, 0.0f, 0.0f);

    m_pModelInfo = g_pGame->GetModelInfo(usModel);

    // Add this object to the list
    m_pObjectManager->AddToList(this);

    if (m_bIsLowLod)
        m_pManager->OnLowLODElementCreated();

    if (m_ComponentData.empty())
    {
        // grab our map of components
        std::map<SString, SObjectFrame> componentMap = GetComponentMap();
        // get our beginning
        std::map<SString, SObjectFrame>::iterator iter = componentMap.begin();
        // loop through all the components.... we don't care about the RwFrame we just want the names.
        for (; iter != componentMap.end(); iter++)
        {
            const SString&       strName = iter->first;
            const SObjectFrame& frame = iter->second;

            SObjectComponentData objectComponentData;

            // Find parent component name
            if (!frame.frameList.empty())
            {
                RwFrame* pParentRwFrame = frame.frameList.back();
                for (std::map<SString, SObjectFrame>::const_iterator iter2 = componentMap.begin(); iter2 != componentMap.end(); iter2++)
                {
                    if (iter2->second.pFrame == pParentRwFrame)
                    {
                        objectComponentData.m_strParentName = iter2->first;
                        break;
                    }
                }
            }

            // Grab our start position
            GetComponentPosition((*iter).first, objectComponentData.m_vecComponentPosition);
            GetComponentRotation((*iter).first, objectComponentData.m_vecComponentRotation);
            GetComponentScale((*iter).first, objectComponentData.m_vecComponentScale);

            // copy it into our original positions
            objectComponentData.m_vecOriginalComponentPosition = objectComponentData.m_vecComponentPosition;
            objectComponentData.m_vecOriginalComponentRotation = objectComponentData.m_vecComponentRotation;
            objectComponentData.m_vecOriginalComponentScale = objectComponentData.m_vecComponentScale;

            // insert it into our component data list
            m_ComponentData.insert(std::pair<SString, SObjectComponentData>((*iter).first, objectComponentData));

            // # prefix means hidden by default.
            if ((*iter).first[0] == '#')
            {
                SetComponentVisible((*iter).first, false);
            }
        }
    }
}

void CClientObject::ConvertComponentScaleBase(const SString& objectComponent, CVector& vecScale, EComponentBaseType inputBase, EComponentBaseType outputBase)
{
    if (inputBase != outputBase)
    {
        CMatrix matTemp(CVector(), CVector(), vecScale);
        ConvertComponentMatrixBase(objectComponent, matTemp, inputBase, outputBase);
        vecScale = matTemp.GetScale();
    }
}

bool CClientObject::GetComponentScale(const SString& objectComponent, CVector& vecScale, EComponentBaseType outputBase)
{
    if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
    {
        // fill our rotation from the cached rotation
        vecScale = m_ComponentData[objectComponent].m_vecComponentScale;

        // Convert to required base
        ConvertComponentScaleBase(objectComponent, vecScale, EComponentBase::PARENT, outputBase);
        return true;
    }
    return false;
}

void CClientObject::ConvertComponentRotationBase(const SString& objectComponent, CVector& vecRotation, EComponentBaseType inputBase,
    EComponentBaseType outputBase)
{
    if (inputBase != outputBase)
    {
        CMatrix matTemp(CVector(), vecRotation);
        ConvertComponentMatrixBase(objectComponent, matTemp, inputBase, outputBase);
        vecRotation = matTemp.GetRotation();
    }
}

bool CClientObject::GetComponentRotation(const SString& objectComponent, CVector& vecRotation, EComponentBaseType outputBase)
{
    if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
    {
        // fill our rotation from the cached rotation
        vecRotation = m_ComponentData[objectComponent].m_vecComponentRotation;

        // Convert to required base
        ConvertComponentRotationBase(objectComponent, vecRotation, EComponentBase::PARENT, outputBase);
        return true;
    }
    return false;
}

void CClientObject::ConvertComponentPositionBase(const SString& objectComponent, CVector& vecPosition, EComponentBaseType inputBase,
    EComponentBaseType outputBase)
{
    if (inputBase != outputBase)
    {
        CMatrix matTemp(vecPosition);
        ConvertComponentMatrixBase(objectComponent, matTemp, inputBase, outputBase);
        vecPosition = matTemp.GetPosition();
    }
}

void CClientObject::GetComponentParentToRootMatrix(const SString& objectComponent, CMatrix& matOutParentToRoot)
{
    // Get first parent
    SObjectComponentData* pComponentData = MapFind(m_ComponentData, objectComponent);
    if (pComponentData)
    {
        pComponentData = MapFind(m_ComponentData, pComponentData->m_strParentName);
    }

    // Combine transforms of parent components (limit to 10 in case of problems)
    CMatrix matCombo;
    for (uint i = 0; pComponentData && i < 10; i++)
    {
        CMatrix matFrame(pComponentData->m_vecComponentPosition, pComponentData->m_vecComponentRotation, pComponentData->m_vecComponentScale);
        matCombo = matCombo * matFrame;
        pComponentData = MapFind(m_ComponentData, pComponentData->m_strParentName);
    }

    matOutParentToRoot = matCombo;
}


void CClientObject::ConvertComponentMatrixBase(const SString& objectComponent, CMatrix& matOrientation, EComponentBaseType inputBase,
    EComponentBaseType outputBase)
{
    if (inputBase == outputBase)
        return;

    if (inputBase == EComponentBaseType::PARENT)
    {
        if (outputBase == EComponentBaseType::ROOT)
        {
            // Parent relative to root relative
            CMatrix matParentToRoot;
            GetComponentParentToRootMatrix(objectComponent, matParentToRoot);
            matOrientation = matOrientation * matParentToRoot;
        }
        else if (outputBase == EComponentBaseType::WORLD)
        {
            // Parent relative to world
            CMatrix matParentToRoot;
            GetComponentParentToRootMatrix(objectComponent, matParentToRoot);
            matOrientation = matOrientation * matParentToRoot;

            CMatrix matRootToWorld;
            GetMatrix(matRootToWorld);
            matOrientation = matOrientation * matRootToWorld;
        }
    }
    else if (inputBase == EComponentBaseType::ROOT)
    {
        if (outputBase == EComponentBaseType::PARENT)
        {
            // Root relative to parent relative
            CMatrix matParentToRoot;
            GetComponentParentToRootMatrix(objectComponent, matParentToRoot);
            matOrientation = matOrientation * matParentToRoot.Inverse();
        }
        else if (outputBase == EComponentBaseType::WORLD)
        {
            // Root relative to world
            CMatrix matRootToWorld;
            GetMatrix(matRootToWorld);
            matOrientation = matOrientation * matRootToWorld;
        }
    }
    else if (inputBase == EComponentBaseType::WORLD)
    {
        if (outputBase == EComponentBaseType::PARENT)
        {
            // World to parent relative
            CMatrix matRootToWorld;
            GetMatrix(matRootToWorld);
            matOrientation = matOrientation * matRootToWorld.Inverse();

            CMatrix matParentToRoot;
            GetComponentParentToRootMatrix(objectComponent, matParentToRoot);
            matOrientation = matOrientation * matParentToRoot.Inverse();
        }
        else if (outputBase == EComponentBaseType::ROOT)
        {
            // World to root relative
            CMatrix matRootToWorld;
            GetMatrix(matRootToWorld);
            matOrientation = matOrientation * matRootToWorld.Inverse();
        }
    }
}

bool CClientObject::SetComponentVisible(const SString& objectComponent, bool bVisible)
{
    if (m_pObject)
    {
        if (m_pObject->SetComponentVisible(objectComponent, bVisible))
        {
            // update our cache
            m_ComponentData[objectComponent].m_bVisible = bVisible;

            // set our visibility on the model
            m_pObject->SetComponentVisible(objectComponent, bVisible);
            return true;
        }
    }
    else
    {
        if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
        {
            // store our visible variable to the cached data
            m_ComponentData[objectComponent].m_bVisible = bVisible;
            return true;
        }
    }
    return false;
}

bool CClientObject::GetComponentVisible(const SString& objectComponent, bool& bVisible)
{
    if (m_pObject)
    {
        // fill our visible variable from the actual position
        return m_pObject->GetComponentVisible(objectComponent, bVisible);
    }
    else
    {
        if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
        {
            // fill our visible variable from the cached data
            bVisible = m_ComponentData[objectComponent].m_bVisible;
            return true;
        }
    }
    return false;
}

bool CClientObject::ResetComponentScale(const SString& objectComponent)
{
    // set our rotation on the model
    if (SetComponentScale(objectComponent, m_ComponentData[objectComponent].m_vecOriginalComponentScale))
    {
        // update our cache
        m_ComponentData[objectComponent].m_bScaleChanged = false;
        return true;
    }
    return false;
}
bool CClientObject::ResetComponentRotation(const SString& objectComponent)
{
    // set our rotation on the model
    if (SetComponentRotation(objectComponent, m_ComponentData[objectComponent].m_vecOriginalComponentRotation))
    {
        // update our cache
        m_ComponentData[objectComponent].m_bRotationChanged = false;
        return true;
    }
    return false;
}
bool CClientObject::ResetComponentPosition(const SString& objectComponent)
{
    // set our position on the model
    if (SetComponentPosition(objectComponent, m_ComponentData[objectComponent].m_vecOriginalComponentPosition))
    {
        // update our cache
        m_ComponentData[objectComponent].m_bPositionChanged = false;
        return true;
    }
    return false;
}

bool CClientObject::SetComponentPosition(const SString& objectComponent, CVector vecPosition, EComponentBaseType inputBase)
{
    // Ensure position is parent relative
    ConvertComponentPositionBase(objectComponent, vecPosition, inputBase, EComponentBase::PARENT);

    if (m_pObject)
    {
        // set our position on the model
        if (m_pObject->SetComponentPosition(objectComponent, vecPosition))
        {
            // update our cache
            m_ComponentData[objectComponent].m_vecComponentPosition = vecPosition;
            m_ComponentData[objectComponent].m_bPositionChanged = true;

            return true;
        }
    }
    else
    {
        if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
        {
            // update our cache
            m_ComponentData[objectComponent].m_vecComponentPosition = vecPosition;
            m_ComponentData[objectComponent].m_bPositionChanged = true;
            return true;
        }
    }
    return false;
}


bool CClientObject::SetComponentRotation(const SString& objectComponent, CVector vecRotation, EComponentBaseType inputBase)
{
    // Ensure rotation is parent relative
    ConvertComponentRotationBase(objectComponent, vecRotation, inputBase, EComponentBase::PARENT);

    if (m_pObject)
    {
        // set our rotation on the model
        if (m_pObject->SetComponentRotation(objectComponent, vecRotation))
        {
            // update our cache
            m_ComponentData[objectComponent].m_vecComponentRotation = vecRotation;
            m_ComponentData[objectComponent].m_bRotationChanged = true;

            return true;
        }
    }
    else
    {
        if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
        {
            // update our cache
            m_ComponentData[objectComponent].m_vecComponentRotation = vecRotation;
            m_ComponentData[objectComponent].m_bRotationChanged = true;
            return true;
        }
    }
    return false;
}

bool CClientObject::SetComponentScale(const SString& objectComponent, CVector vecScale, EComponentBaseType inputBase)
{
    // Ensure scale is parent relative
    ConvertComponentScaleBase(objectComponent, vecScale, inputBase, EComponentBase::PARENT);

    if (m_pObject)
    {
        // set our rotation on the model
        if (m_pObject->SetComponentScale(objectComponent, vecScale))
        {
            // update our cache
            m_ComponentData[objectComponent].m_vecComponentScale = vecScale;
            m_ComponentData[objectComponent].m_bScaleChanged = true;

            return true;
        }
    }
    else
    {
        if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
        {
            // update our cache
            m_ComponentData[objectComponent].m_vecComponentScale = vecScale;
            m_ComponentData[objectComponent].m_bScaleChanged = true;
            return true;
        }
    }
    return false;
}

bool CClientObject::GetComponentPosition(const SString& objectComponent, CVector& vecPosition, EComponentBaseType outputBase)
{
    if (m_pObject)
    {
        // fill our position from the actual position
        if (m_pObject->GetComponentPosition(objectComponent, vecPosition))
        {
            // Convert to required base
            ConvertComponentPositionBase(objectComponent, vecPosition, EComponentBase::PARENT, outputBase);
            return true;
        }
    }
    else
    {
        if (m_ComponentData.find(objectComponent) != m_ComponentData.end())
        {
            // fill our position from the cached position
            vecPosition = m_ComponentData[objectComponent].m_vecComponentPosition;

            // Convert to required base
            ConvertComponentPositionBase(objectComponent, vecPosition, EComponentBase::PARENT, outputBase);
            return true;
        }
    }
    return false;
}

CClientObject::~CClientObject(void)
{
    // Unrequest whatever we've requested or we'll crash in unlucky situations
    m_pModelRequester->Cancel(this, false);

    // Detach us from anything
    AttachTo(NULL);

    // Destroy the object
    Destroy();

    // Remove us from the list
    Unlink();

    if (m_bIsLowLod)
        m_pManager->OnLowLODElementDestroyed();
}

void CClientObject::Unlink(void)
{
    m_pObjectManager->RemoveFromLists(this);
    g_pClientGame->GetObjectRespawner()->Unreference(this);

    // Remove LowLod refs in others
    SetLowLodObject(NULL);
    while (!m_HighLodObjectList.empty())
        m_HighLodObjectList[0]->SetLowLodObject(NULL);
}

void CClientObject::GetPosition(CVector& vecPosition) const
{
    if (m_pObject)
    {
        vecPosition = *m_pObject->GetPosition();
    }
    else if (m_pAttachedToEntity)
    {
        m_pAttachedToEntity->GetPosition(vecPosition);
        vecPosition += m_vecAttachedPosition;
    }
    else
    {
        vecPosition = m_vecPosition;
    }
}

void CClientObject::SetPosition(const CVector& vecPosition)
{
    // Move the object
    if (m_pObject)
    {
        CVector vecRot;
        GetRotationRadians(vecRot);
        m_pObject->Teleport(vecPosition.fX, vecPosition.fY, vecPosition.fZ);
#ifndef MTA_BUILDINGS
        m_pObject->ProcessCollision();
#endif
        m_pObject->SetupLighting();
        SetRotationRadians(vecRot);
    }

    if (m_vecPosition != vecPosition)
    {
        // Store the position in our datastruct
        m_vecPosition = vecPosition;

        // Update our streaming position
        UpdateStreamPosition(vecPosition);
    }
}

void CClientObject::GetRotationDegrees(CVector& vecRotation) const
{
    GetRotationRadians(vecRotation);
    ConvertRadiansToDegrees(vecRotation);
}

void CClientObject::GetRotationRadians(CVector& vecRotation) const
{
    if (m_pObject && m_pAttachedToEntity)            // Temp fix for static objects->
    {
        // We've been returning the rotation that got set last so far (::m_vecRotation)..
        //   but we need to get the real rotation for when the game moves the objects..
        CMatrix matTemp;
        m_pObject->GetMatrix(&matTemp);
        vecRotation = matTemp.GetRotation();
    }
    else
    {
        vecRotation = m_vecRotation;
    }
}

void CClientObject::SetRotationDegrees(const CVector& vecRotation)
{
    // Convert from degrees to radians
    CVector vecTemp;
    vecTemp.fX = vecRotation.fX * 3.1415926535897932384626433832795f / 180.0f;
    vecTemp.fY = vecRotation.fY * 3.1415926535897932384626433832795f / 180.0f;
    vecTemp.fZ = vecRotation.fZ * 3.1415926535897932384626433832795f / 180.0f;

    SetRotationRadians(vecTemp);
}

void CClientObject::UpdateComponents()
{
    if (m_pObject)
    {
        m_pObject->UpdateComponents();
        if (m_ComponentData.empty())
        {
            // grab our map of components
            std::map<SString, SObjectFrame> componentMap = m_pObject->GetComponentMap();
            // get our beginning
            std::map<SString, SObjectFrame>::iterator iter = componentMap.begin();
            // loop through all the components.... we don't care about the RwFrame we just want the names.
            for (; iter != componentMap.end(); iter++)
            {
                const SString&       strName = iter->first;
                const SObjectFrame& frame = iter->second;

                SObjectComponentData objectComponentData;

                // Find parent component name
                if (!frame.frameList.empty())
                {
                    RwFrame* pParentRwFrame = frame.frameList.back();
                    for (std::map<SString, SObjectFrame>::const_iterator iter2 = componentMap.begin(); iter2 != componentMap.end(); iter2++)
                    {
                        if (iter2->second.pFrame == pParentRwFrame)
                        {
                            objectComponentData.m_strParentName = iter2->first;
                            break;
                        }
                    }
                }

                // Grab our start position
                GetComponentPosition((*iter).first, objectComponentData.m_vecComponentPosition);
                GetComponentRotation((*iter).first, objectComponentData.m_vecComponentRotation);
                GetComponentScale((*iter).first, objectComponentData.m_vecComponentScale);

                // copy it into our original positions
                objectComponentData.m_vecOriginalComponentPosition = objectComponentData.m_vecComponentPosition;
                objectComponentData.m_vecOriginalComponentRotation = objectComponentData.m_vecComponentRotation;
                objectComponentData.m_vecOriginalComponentScale = objectComponentData.m_vecComponentScale;

                // insert it into our component data list
                m_ComponentData.insert(std::pair<SString, SObjectComponentData>((*iter).first, objectComponentData));

                // # prefix means hidden by default.
                if ((*iter).first[0] == '#')
                {
                    SetComponentVisible((*iter).first, false);
                }
            }
        }
        // Grab our component data
        std::map<SString, SObjectComponentData>::iterator iter = m_ComponentData.begin();
        // Loop through our component data
        for (; iter != m_ComponentData.end(); iter++)
        {
            // store our string in a temporary variable
            SString strTemp = (*iter).first;
            // get our poisition and rotation and store it into
            // GetComponentPosition ( strTemp, (*iter).second.m_vecComponentPosition );
            // GetComponentRotation ( strTemp, (*iter).second.m_vecComponentRotation );
            // is our position changed?
            if ((*iter).second.m_bPositionChanged)
            {
                // Make sure it's different
                if ((*iter).second.m_vecOriginalComponentPosition != (*iter).second.m_vecComponentPosition)
                {
                    // apply our new position
                    SetComponentPosition(strTemp, (*iter).second.m_vecComponentPosition);
                }
            }
            // is our rotation changed?
            if ((*iter).second.m_bRotationChanged)
            {
                // Make sure it's different
                if ((*iter).second.m_vecOriginalComponentRotation != (*iter).second.m_vecComponentRotation)
                {
                    // apple our new rotation
                    SetComponentRotation(strTemp, (*iter).second.m_vecComponentRotation);
                }
            }
            // is our scale changed?
            if ((*iter).second.m_bScaleChanged)
            {
                // Make sure it's different
                if ((*iter).second.m_vecOriginalComponentScale != (*iter).second.m_vecComponentScale)
                {
                    // apple our new scale
                    SetComponentScale(strTemp, (*iter).second.m_vecComponentScale);
                }
            }
            // set our visibility
            SetComponentVisible(strTemp, (*iter).second.m_bVisible);
        }
    }

}

void CClientObject::SetRotationRadians(const CVector& vecRotation)
{
    if (m_pObject)
    {
        m_pObject->SetOrientation(vecRotation.fX, vecRotation.fY, vecRotation.fZ);
#ifndef MTA_BUILDINGS
        m_pObject->ProcessCollision();
#endif
        m_pObject->SetupLighting();
    }

    // Store it in our datastruct
    m_vecRotation = vecRotation;
}

void CClientObject::AttachTo(CClientEntity* pEntity)
{
    CClientEntity::AttachTo(pEntity);

    if (m_pAttachedToEntity)
    {
        DoAttaching();
        UpdateStreamPosition(m_vecPosition);
    }
}

void CClientObject::GetOrientation(CVector& vecPosition, CVector& vecRotationRadians)
{
    GetPosition(vecPosition);
    GetRotationRadians(vecRotationRadians);
}

void CClientObject::SetOrientation(const CVector& vecPosition, const CVector& vecRotationRadians)
{
    if (m_vecPosition != vecPosition)
    {
        // Store the position in our datastruct
        m_vecPosition = vecPosition;

        // Update our streaming position
        UpdateStreamPosition(vecPosition);
    }

    // Update our internal data
    m_vecPosition = vecPosition;
    m_vecRotation = vecRotationRadians;

    // Eventually move the object
    if (m_pObject)
    {
        m_pObject->Teleport(vecPosition.fX, vecPosition.fY, vecPosition.fZ);
        m_pObject->SetOrientation(vecRotationRadians.fX, vecRotationRadians.fY, vecRotationRadians.fZ);
#ifndef MTA_BUILDINGS
        m_pObject->ProcessCollision();
#endif
        m_pObject->SetupLighting();
    }
}

void CClientObject::ModelRequestCallback(CModelInfo* pModelInfo)
{
    // Create our object
    Create();
}

float CClientObject::GetDistanceFromCentreOfMassToBaseOfModel(void)
{
    if (m_pObject)
    {
        return m_pObject->GetDistanceFromCentreOfMassToBaseOfModel();
    }
    else
    {
        return 0;
    }
}

void CClientObject::SetVisible(bool bVisible)
{
    m_bIsVisible = bVisible;
    UpdateVisibility();
}

// Call this when m_bIsVisible, m_IsHiddenLowLod or m_pObject is changed
void CClientObject::UpdateVisibility(void)
{
    if (m_pObject)
    {
        m_pObject->SetVisible(m_bIsVisible && !m_IsHiddenLowLod);
    }
}

void CClientObject::SetModel(unsigned short usModel)
{
    // Valid model ID?
    if (CClientObjectManager::IsValidModel(usModel))
    {
        // Destroy current model
        Destroy();

        // Set the new model ID and recreate the model
        m_usModel = usModel;
        m_pModelInfo = g_pGame->GetModelInfo(usModel);
        UpdateSpatialData();

        // Request the new model so we can recreate when it's done
        if (m_pModelRequester->Request(usModel, this))
        {
            Create();
        }
    }
}

bool CClientObject::IsLowLod(void)
{
    return m_bIsLowLod;
}

bool CClientObject::SetLowLodObject(CClientObject* pNewLowLodObject)
{
    // This object has to be high lod
    if (m_bIsLowLod)
        return false;

    // Set or clear?
    if (!pNewLowLodObject)
    {
        // Check if already clear
        if (!m_pLowLodObject)
            return false;

        // Verify link
        assert(ListContains(m_pLowLodObject->m_HighLodObjectList, this));

        // Clear there and here
        ListRemove(m_pLowLodObject->m_HighLodObjectList, this);
        m_pLowLodObject = NULL;
        return true;
    }
    else
    {
        // new object has to be low lod
        if (!pNewLowLodObject->m_bIsLowLod)
            return false;

        // Remove any previous link
        SetLowLodObject(NULL);

        // Make new link
        m_pLowLodObject = pNewLowLodObject;
        pNewLowLodObject->m_HighLodObjectList.push_back(this);
        return true;
    }
}

CClientObject* CClientObject::GetLowLodObject(void)
{
    if (m_bIsLowLod)
        return NULL;
    return m_pLowLodObject;
}

void CClientObject::Render(void)
{
    if (m_pObject)
    {
        m_pObject->Render();
    }
}

void CClientObject::SetFrozen(bool bFrozen)
{
    m_bIsFrozen = bFrozen;

    if (m_pObject)
    {
        m_pObject->SetFrozen(bFrozen);
    }

    // Reset speed if we frozing object
    if (bFrozen)
    {
        // Reset speed only if object is actually moving
        CVector vecZero;
        CVector vecSpeed;

        GetMoveSpeed(vecSpeed);
        if (vecZero != vecSpeed)
        {
            SetMoveSpeed(vecZero);
        }

        GetTurnSpeed(vecSpeed);
        if (vecZero != vecSpeed)
        {
            SetTurnSpeed(vecZero);
        }
    }
}

void CClientObject::SetAlpha(unsigned char ucAlpha)
{
    if (m_pObject)
    {
        m_pObject->SetAlpha(ucAlpha);
    }
    m_ucAlpha = ucAlpha;
}

void CClientObject::GetScale(CVector& vecScale) const
{
    if (m_pObject)
    {
        vecScale = *m_pObject->GetScale();
    }
    else
    {
        vecScale = m_vecScale;
    }
}

void CClientObject::SetScale(const CVector& vecScale)
{
    if (m_pObject)
    {
        m_pObject->SetScale(vecScale.fX, vecScale.fY, vecScale.fZ);
    }
    m_vecScale = vecScale;
}

void CClientObject::SetCollisionEnabled(bool bCollisionEnabled)
{
    if (m_pObject)
    {
        m_pObject->SetUsesCollision(bCollisionEnabled);
    }

    m_bUsesCollision = bCollisionEnabled;
}

float CClientObject::GetHealth(void)
{
    if (m_pObject)
    {
        return m_pObject->GetHealth();
    }

    return m_fHealth;
}

void CClientObject::SetHealth(float fHealth)
{
    if (m_pObject)
    {
        m_pObject->SetHealth(fHealth);
    }

    m_fHealth = fHealth;
}

void CClientObject::StreamIn(bool bInstantly)
{
    // Don't stream the object in, if respawn is disabled and the object is broken
    if (!m_bRespawnEnabled && m_fHealth == 0.0f)
        return;

    // We need to load now?
    if (bInstantly)
    {
        // Request the model blocking
        if (m_pModelRequester->RequestBlocking(m_usModel, "CClientObject::StreamIn - bInstantly"))
        {
            // Create us
            Create();
        }
        else
            NotifyUnableToCreate();
    }
    else
    {
        // Request the model async
        if (m_pModelRequester->Request(m_usModel, this))
        {
            // Create us now if we already had it loaded
            Create();
        }
        else
            NotifyUnableToCreate();
    }
}

void CClientObject::StreamOut(void)
{
    // Save the health
    if (m_pObject)
    {
        // If respawn is enabled, reset the health
        if (m_bRespawnEnabled && m_fHealth == 0.0f)
            m_fHealth = 1000.0f;
        else
            m_fHealth = m_pObject->GetHealth();
    }

    // Destroy the object.
    Destroy();

    // Cancel anything we might've requested.
    m_pModelRequester->Cancel(this, true);
}

// Don't call this function directly by lua functions
void CClientObject::ReCreate(void)
{
    m_fHealth = 1000.0f;

    if (m_pObject)
        Destroy();

    Create();
}

void CClientObject::Create(void)
{
    // Not already created an object?
    if (!m_pObject)
    {
        // Check again that the limit isn't reached. We are required to do so because
        // we load async. The streamer isn't always aware of our limits.
        if (IsLowLod() ? !CClientObjectManager::StaticIsLowLodObjectLimitReached() : !CClientObjectManager::StaticIsObjectLimitReached())
        {
            // Add a reference to the object
            m_pModelInfo->ModelAddRef(BLOCKING, "CClientObject::Create");

            // If the new object is not breakable, allow it into the vertical line test
            g_pMultiplayer->AllowCreatedObjectsInVerticalLineTest(!CClientObjectManager::IsBreakableModel(m_usModel));

            // Create the object
            m_pObject = g_pGame->GetPools()->AddObject(this, m_usModel, m_bIsLowLod, m_bBreakingDisabled);

            // Restore default behaviour
            g_pMultiplayer->AllowCreatedObjectsInVerticalLineTest(false);

            if (m_pObject)
            {
                // Put our pointer in its stored pointer
                m_pObject->SetStoredPointer(this);

                // Apply our data to the object
                m_pObject->Teleport(m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ);
                m_pObject->SetOrientation(m_vecRotation.fX, m_vecRotation.fY, m_vecRotation.fZ);
                #ifndef MTA_BUILDINGS
                m_pObject->ProcessCollision();
                #endif
                m_pObject->SetupLighting();
                m_pObject->SetFrozen(m_bIsFrozen);

                UpdateVisibility();
                if (!m_bUsesCollision)
                    SetCollisionEnabled(false);
                if (m_vecScale.fX != 1.0f || m_vecScale.fY != 1.0f || m_vecScale.fZ != 1.0f)
                    SetScale(m_vecScale);
                m_pObject->SetAreaCode(m_ucInterior);
                SetAlpha(m_ucAlpha);
                m_pObject->SetHealth(m_fHealth);

                // Set object properties
                if (m_fMass != -1.0f)
                    m_pObject->SetMass(m_fMass);
                if (m_fTurnMass != -1.0f)
                    m_pObject->SetTurnMass(m_fTurnMass);
                if (m_fAirResistance != -1.0f)
                    m_pObject->SetAirResistance(m_fAirResistance);
                if (m_fElasticity != -1.0f)
                    m_pObject->SetElasticity(m_fElasticity);
                if (m_fBuoyancyConstant != -1.0f)
                    m_pObject->SetBuoyancyConstant(m_fBuoyancyConstant);
                if (m_vecCenterOfMass.fX != 0.0f || m_vecCenterOfMass.fY != 0.0f || m_vecCenterOfMass.fZ != 0.0f)
                    m_pObject->SetCenterOfMass(m_vecCenterOfMass);

                // Reattach to an entity + any entities attached to this
                ReattachEntities();

                // Validate this entity again
                m_pManager->RestoreEntity(this);

                if (m_ComponentData.empty())
                {
                    // grab our map of components
                    std::map<SString, SObjectFrame> componentMap = m_pObject->GetComponentMap();
                    // get our beginning
                    std::map<SString, SObjectFrame>::iterator iter = componentMap.begin();
                    // loop through all the components.... we don't care about the RwFrame we just want the names.
                    for (; iter != componentMap.end(); iter++)
                    {
                        const SString&       strName = iter->first;
                        const SObjectFrame& frame = iter->second;

                        SObjectComponentData objectComponentData;

                        // Find parent component name
                        if (!frame.frameList.empty())
                        {
                            RwFrame* pParentRwFrame = frame.frameList.back();
                            for (std::map<SString, SObjectFrame>::const_iterator iter2 = componentMap.begin(); iter2 != componentMap.end(); iter2++)
                            {
                                if (iter2->second.pFrame == pParentRwFrame)
                                {
                                    objectComponentData.m_strParentName = iter2->first;
                                    break;
                                }
                            }
                        }

                        // Grab our start position
                        GetComponentPosition((*iter).first, objectComponentData.m_vecComponentPosition);
                        GetComponentRotation((*iter).first, objectComponentData.m_vecComponentRotation);
                        GetComponentScale((*iter).first, objectComponentData.m_vecComponentScale);

                        // copy it into our original positions
                        objectComponentData.m_vecOriginalComponentPosition = objectComponentData.m_vecComponentPosition;
                        objectComponentData.m_vecOriginalComponentRotation = objectComponentData.m_vecComponentRotation;
                        objectComponentData.m_vecOriginalComponentScale = objectComponentData.m_vecComponentScale;

                        // insert it into our component data list
                        m_ComponentData.insert(std::pair<SString, SObjectComponentData>((*iter).first, objectComponentData));

                        // # prefix means hidden by default.
                        if ((*iter).first[0] == '#')
                        {
                            SetComponentVisible((*iter).first, false);
                        }
                    }
                }
                // Grab our component data
                std::map<SString, SObjectComponentData>::iterator iter = m_ComponentData.begin();
                // Loop through our component data
                for (; iter != m_ComponentData.end(); iter++)
                {
                    // store our string in a temporary variable
                    SString strTemp = (*iter).first;
                    // get our poisition and rotation and store it into
                    // GetComponentPosition ( strTemp, (*iter).second.m_vecComponentPosition );
                    // GetComponentRotation ( strTemp, (*iter).second.m_vecComponentRotation );
                    // is our position changed?
                    if ((*iter).second.m_bPositionChanged)
                    {
                        // Make sure it's different
                        if ((*iter).second.m_vecOriginalComponentPosition != (*iter).second.m_vecComponentPosition)
                        {
                            // apply our new position
                            SetComponentPosition(strTemp, (*iter).second.m_vecComponentPosition);
                        }
                    }
                    // is our rotation changed?
                    if ((*iter).second.m_bRotationChanged)
                    {
                        // Make sure it's different
                        if ((*iter).second.m_vecOriginalComponentRotation != (*iter).second.m_vecComponentRotation)
                        {
                            // apple our new rotation
                            SetComponentRotation(strTemp, (*iter).second.m_vecComponentRotation);
                        }
                    }
                    // is our scale changed?
                    if ((*iter).second.m_bScaleChanged)
                    {
                        // Make sure it's different
                        if ((*iter).second.m_vecOriginalComponentScale != (*iter).second.m_vecComponentScale)
                        {
                            // apple our new scale
                            SetComponentScale(strTemp, (*iter).second.m_vecComponentScale);
                        }
                    }
                    // set our visibility
                    SetComponentVisible(strTemp, (*iter).second.m_bVisible);
                }
                // Tell the streamer we've created this object
                NotifyCreate();

                // Done
                return;
            }
            else
            {
                // Remove our reference to the object again
                m_pModelInfo->RemoveRef();
            }
        }

        // Tell the streamer we could not create it
        NotifyUnableToCreate();
    }
}

void CClientObject::Destroy(void)
{
    // If the object exists
    if (m_pObject)
    {
        // Invalidate
        m_pManager->InvalidateEntity(this);

        // Destroy the object
        g_pGame->GetPools()->RemoveObject(m_pObject);
        m_pObject = NULL;

        // Remove our reference to its model
        m_pModelInfo->RemoveRef();

        NotifyDestroy();
    }
}

void CClientObject::NotifyCreate(void)
{
    m_pObjectManager->OnCreation(this);
    CClientStreamElement::NotifyCreate();
}

void CClientObject::NotifyDestroy(void)
{
    m_pObjectManager->OnDestruction(this);
}

void CClientObject::StreamedInPulse(void)
{
    // Some things to do if low LOD object
    if (m_bIsLowLod)
    {
        // Manually update attaching in case other object is streamed out
        DoAttaching();

        // Be hidden if all HighLodObjects are fully visible
        m_IsHiddenLowLod = true;
        if (m_HighLodObjectList.empty())
            m_IsHiddenLowLod = false;
        for (std::vector<CClientObject*>::iterator iter = m_HighLodObjectList.begin(); iter != m_HighLodObjectList.end(); ++iter)
        {
            CObject* pObject = (*iter)->m_pObject;
            if (!pObject || !pObject->IsFullyVisible())
            {
                m_IsHiddenLowLod = false;
                break;
            }
        }

        UpdateVisibility();
    }
    else
    {
        // Fixed attachment bug #9339 where [object1] -> [object2] -> [vehicle] causes positional lag for [object1]
        if (m_pAttachedToEntity && m_pAttachedToEntity->GetAttachedTo())
        {
            DoAttaching();
        }
    }

    // Are we not frozen
    if (!m_bIsFrozen)
    {
        // Grab our actual position (as GTA moves it too)
        CVector vecPosition = *m_pObject->GetPosition();

        // Has it moved without MTA knowing?
        if (vecPosition != m_vecPosition)
        {
            m_vecPosition = vecPosition;

            // Update our streaming position
            UpdateStreamPosition(m_vecPosition);
        }
    }
}

void CClientObject::GetMoveSpeed(CVector& vecMoveSpeed) const
{
    if (m_pObject)
    {
        m_pObject->GetMoveSpeed(&vecMoveSpeed);
    }
    else
    {
        vecMoveSpeed = m_vecMoveSpeed;
    }
}

void CClientObject::SetMoveSpeed(const CVector& vecMoveSpeed)
{
    if (m_pObject)
    {
        m_pObject->SetMoveSpeed(const_cast<CVector*>(&vecMoveSpeed));
    }
    m_vecMoveSpeed = vecMoveSpeed;
}

void CClientObject::GetTurnSpeed(CVector& vecTurnSpeed) const
{
    if (m_pObject)
    {
        m_pObject->GetTurnSpeed(&vecTurnSpeed);
    }
    else
    {
        vecTurnSpeed = m_vecTurnSpeed;
    }
}

void CClientObject::SetTurnSpeed(const CVector& vecTurnSpeed)
{
    if (m_pObject)
    {
        m_pObject->SetTurnSpeed(const_cast<CVector*>(&vecTurnSpeed));
    }
    m_vecTurnSpeed = vecTurnSpeed;
}

CSphere CClientObject::GetWorldBoundingSphere(void)
{
    CSphere     sphere;
    CModelInfo* pModelInfo = g_pGame->GetModelInfo(GetModel());
    if (pModelInfo)
    {
        CBoundingBox* pBoundingBox = pModelInfo->GetBoundingBox();
        if (pBoundingBox)
        {
            sphere.vecPosition = pBoundingBox->vecBoundOffset;
            sphere.fRadius = pBoundingBox->fRadius;
        }
    }
    sphere.vecPosition += GetStreamPosition();
    return sphere;
}

bool CClientObject::IsBreakable(bool bCheckModelList)
{
    if (!bCheckModelList)
        return !m_bBreakingDisabled;

    return (CClientObjectManager::IsBreakableModel(m_usModel) && !m_bBreakingDisabled);
}

bool CClientObject::SetBreakable(bool bBreakable)
{
    bool bDisableBreaking = !bBreakable;
    // Are we breakable and have we changed
    if (CClientObjectManager::IsBreakableModel(m_usModel) && m_bBreakingDisabled != bDisableBreaking)
    {
        m_bBreakingDisabled = bDisableBreaking;
        // We can't use ReCreate directly (otherwise the game will crash)
        g_pClientGame->GetObjectRespawner()->Respawn(this);
        return true;
    }
    return false;
}

bool CClientObject::Break(void)
{
    // Are we breakable?
    if (m_pObject && CClientObjectManager::IsBreakableModel(m_usModel) && !m_bBreakingDisabled)
    {
        m_pObject->Break();
        return true;
    }
    return false;
}

float CClientObject::GetMass(void)
{
    if (m_pObject)
        return m_pObject->GetMass();

    return m_fMass;
}

void CClientObject::SetMass(float fMass)
{
    if (m_pObject)
        m_pObject->SetMass(fMass);

    m_fMass = fMass;
}

float CClientObject::GetTurnMass(void)
{
    if (m_pObject)
        return m_pObject->GetTurnMass();

    return m_fTurnMass;
}

void CClientObject::SetTurnMass(float fTurnMass)
{
    if (m_pObject)
        m_pObject->SetTurnMass(fTurnMass);

    m_fTurnMass = fTurnMass;
}

float CClientObject::GetAirResistance(void)
{
    if (m_pObject)
        return m_pObject->GetAirResistance();

    return m_fAirResistance;
}

void CClientObject::SetAirResistance(float fAirResistance)
{
    if (m_pObject)
        m_pObject->SetAirResistance(fAirResistance);

    m_fAirResistance = fAirResistance;
}

float CClientObject::GetElasticity(void)
{
    if (m_pObject)
        return m_pObject->GetElasticity();

    return m_fElasticity;
}

void CClientObject::SetElasticity(float fElasticity)
{
    if (m_pObject)
        m_pObject->SetElasticity(fElasticity);

    m_fElasticity = fElasticity;
}

float CClientObject::GetBuoyancyConstant(void)
{
    if (m_pObject)
        return m_pObject->GetBuoyancyConstant();

    return m_fBuoyancyConstant;
}

void CClientObject::SetBuoyancyConstant(float fBuoyancyConstant)
{
    if (m_pObject)
        m_pObject->SetBuoyancyConstant(fBuoyancyConstant);

    m_fBuoyancyConstant = fBuoyancyConstant;
}

void CClientObject::GetCenterOfMass(CVector& vecCenterOfMass) const
{
    if (m_pObject)
        m_pObject->GetCenterOfMass(vecCenterOfMass);
    else
        vecCenterOfMass = m_vecCenterOfMass;
}

void CClientObject::SetCenterOfMass(const CVector& vecCenterOfMass)
{
    if (m_pObject)
        m_pObject->SetCenterOfMass(const_cast<CVector&>(vecCenterOfMass));

    m_vecCenterOfMass = vecCenterOfMass;
}

void CClientObject::SetVisibleInAllDimensions(bool bVisible, unsigned short usNewDimension)
{
    m_bVisibleInAllDimensions = bVisible;

    // Stream-in/out the object as needed
    this->SetDimension(bVisible ? g_pClientGame->GetLocalPlayer()->GetDimension() : usNewDimension);
}
