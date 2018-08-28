/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CLoadStringPacket.cpp
 *  PURPOSE:     Console message echo packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

bool CLoadStringPacket::Write(NetBitStreamInterface& BitStream) const
{
    // Not too short?
    size_t sizeMessage = m_strCode.length();
    if (sizeMessage >= MIN_LOADSTRING_LENGTH)
    {
        BitStream.Write(m_usID);
        BitStream.WriteString(m_strCode);
        return true;
    }

    return false;
}
