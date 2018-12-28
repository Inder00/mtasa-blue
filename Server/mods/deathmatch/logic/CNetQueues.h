/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CNetQueues.h
 *  PURPOSE:     Todo
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

class CNetQueues
{
public:
    CNetQueues(void);

    void FlushAllQueues(void);
    
    void AddElementData(CElement* pElement, const char* szName);
    void FlushElementData(void);


private:
    std::map<SString, CElement*> m_elementDataQueue;
};
