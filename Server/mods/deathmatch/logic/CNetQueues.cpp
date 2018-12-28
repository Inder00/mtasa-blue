/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CCommandLineParser.cpp
 *  PURPOSE:     Command line parser class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

using namespace std;

static CPlayerManager*       m_pPlayerManager;

CNetQueues::CNetQueues(void)
{
    m_pPlayerManager = g_pGame->GetPlayerManager();
}

void CNetQueues::FlushAllQueues(void)
{
    FlushElementData();
}

void CNetQueues::FlushElementData(void)
{
    const char* asdf;
    bool bIsSynced;
    CLuaArgument* pCurrentVariable;
    for (auto it = m_elementDataQueue.begin(); it != m_elementDataQueue.end(); it++)
    {
        if (it->second != nullptr && !it->second->IsBeingDeleted())
        {
            pCurrentVariable = it->second->GetCustomData(it->first, false, &bIsSynced);
            if (pCurrentVariable != nullptr && bIsSynced)
            {
                asdf = it->first.data();
                unsigned short usNameLength = static_cast<unsigned short>(strlen(asdf));
                CBitStream     BitStream;
                BitStream.pBitStream->WriteCompressed(usNameLength);
                BitStream.pBitStream->Write(asdf, usNameLength);
                pCurrentVariable->WriteToBitStream(*BitStream.pBitStream);
                m_pPlayerManager->BroadcastOnlyJoined(CElementRPCPacket(it->second, SET_ELEMENT_DATA, *BitStream.pBitStream));

                CPerfStatEventPacketUsage::GetSingleton()->UpdateElementDataUsageOut(asdf, m_pPlayerManager->Count(),
                    BitStream.pBitStream->GetNumberOfBytesUsed());
                CLogger::LogPrintf("Send %s\r\n", asdf);
            }
        }
    }
    m_elementDataQueue.clear();
}
void CNetQueues::AddElementData(CElement* pElement, const char* szName)
{
    m_elementDataQueue[SString("%s",szName)] = pElement;
}
