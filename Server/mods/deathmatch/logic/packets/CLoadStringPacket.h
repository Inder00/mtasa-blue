/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CConsoleEchoPacket.h
 *  PURPOSE:     Console message echo packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPacket.h"
#include "../../Config.h"

class CLoadStringPacket : public CPacket
{
public:
    CLoadStringPacket(const char* szMessage, unsigned short usNetID)
    { 
        m_strCode.AssignLeft(szMessage, MAX_LOADSTRING_LENGTH); 
        m_usID = usNetID;
    }

    ePacketID               GetPacketID(void) const { return PACKET_ID_PLAYER_LOADSTRING; };
    unsigned long           GetFlags(void) const { return PACKET_LOW_PRIORITY | PACKET_RELIABLE | PACKET_SEQUENCED; };
    virtual ePacketOrdering GetPacketOrdering(void) const { return PACKET_ORDERING_CHAT; }

    bool Write(NetBitStreamInterface& BitStream) const;

private:
    unsigned short m_usID;
    SString m_strCode;
};
