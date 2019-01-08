/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientRendererManager.h
 *  PURPOSE:     PointLights entity manager class header
 *
 *****************************************************************************/

#pragma once

class CClientRendererManager
{
    friend class CClientManager;
    friend class CClientRenderer;

public:
    CClientRendererManager(CClientManager* pManager);
    ~CClientRendererManager(void);


    std::list<CClientRenderer*>::const_iterator IterBegin(void) { return m_List.begin(); };
    std::list<CClientRenderer*>::const_iterator IterEnd(void) { return m_List.end(); };

    void DoPulse();
private:
    void AddToList(CClientRenderer* pRenderer) { m_List.push_back(pRenderer); };
    void RemoveFromList(CClientRenderer* pRenderer);
    void DeleteAll();

private:
    CClientManager* m_pManager;

    std::list<CClientRenderer*> m_List;
};
