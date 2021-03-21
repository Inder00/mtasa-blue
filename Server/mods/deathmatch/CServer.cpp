/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/CServer.cpp
 *  PURPOSE:     Server interface handler class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#define ALLOC_STATS_MODULE_NAME "deathmatch"
#include "SharedUtil.hpp"
#include "SharedUtil.Thread.h"
#include "SharedUtil.IntervalCounter.h"
#include "SharedUtil.IntervalCounter.hpp"
#if defined(MTA_DEBUG)
    #include "SharedUtil.Tests.hpp"
#endif

CServerInterface* g_pServerInterface = NULL;
CNetServer*       g_pNetServer = NULL;
CNetServer*       g_pRealNetServer = NULL;

class UpdateListener : public efsw::FileWatchListener
{
public:
    UpdateListener() {}

    void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename = "")
    {
        switch (action)
        {
            case efsw::Actions::Add:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added" << std::endl;
                break;
            case efsw::Actions::Delete:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete" << std::endl;
                break;
            case efsw::Actions::Modified:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
                break;
            case efsw::Actions::Moved:
                std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from (" << oldFilename << ")" << std::endl;
                break;
            default:
                std::cout << "Should never happen!" << std::endl;
        }
    }
};

CServer::CServer()
{
    efsw::FileWatcher* fileWatcher = new efsw::FileWatcher();

    // Create the instance of your efsw::FileWatcherListener implementation
    UpdateListener* listener = new UpdateListener();

    // Add a folder to watch, and get the efsw::WatchID
    // It will watch the /tmp folder recursively ( the third parameter indicates that is recursive )
    // Reporting the files and directories changes to the instance of the listener
    efsw::WatchID watchID = fileWatcher->addWatch("./", listener, true);

    // Adds another directory to watch. This time as non-recursive.
    efsw::WatchID watchID2 = fileWatcher->addWatch("/usr", listener, false);

    // Start watching asynchronously the directories
    fileWatcher->watch();

    // Remove the second watcher added
    // You can also call removeWatch by passing the watch path ( it must end with an slash or backslash in windows, since that's how internally it's saved )
    fileWatcher->removeWatch(watchID2);

    // Init
    m_pServerInterface = NULL;
    m_pGame = NULL;
}

CServer::~CServer()
{
}

void CServer::ServerInitialize(CServerInterface* pServerInterface)
{
    m_pServerInterface = pServerInterface;
    g_pServerInterface = pServerInterface;
    g_pNetServer = pServerInterface->GetNetwork();
    g_pRealNetServer = g_pNetServer;
    #if defined(MTA_DEBUG)
    SharedUtil_Tests();
    #endif
}

bool CServer::ServerStartup(int iArgumentCount, char* szArguments[])
{
    if (!m_pGame)
    {
        m_pGame = new CGame;
        return m_pGame->Start(iArgumentCount, szArguments);
    }

    return false;
}

void CServer::ServerShutdown()
{
    if (m_pGame)
    {
        delete m_pGame;
        m_pGame = NULL;
    }
}

void CServer::GetTag(char* szInfoTag, int iInfoTag)
{
    if (m_pGame)
    {
        m_pGame->GetTag(szInfoTag, iInfoTag);
    }
}

void CServer::HandleInput(char* szCommand)
{
    if (m_pGame)
    {
        m_pGame->HandleInput(szCommand);
    }
}

void CServer::DoPulse()
{
    UNCLOCK(" Top", " Idle");
    if (m_pGame)
    {
        CLOCK(" Top", "Game->DoPulse");
        m_pGame->DoPulse();
        UNCLOCK(" Top", "Game->DoPulse");
    }
    CLOCK(" Top", " Idle");
}

bool CServer::IsFinished()
{
    if (m_pGame)
    {
        return m_pGame->IsFinished();
    }

    return false;
}

bool CServer::PendingWorkToDo()
{
    if (m_pGame && g_pNetServer)
    {
        if (g_pNetServer->GetPendingPacketCount() > 0)
        {
            return true;
        }
    }
    return false;
}

bool CServer::GetSleepIntervals(int& iSleepBusyMs, int& iSleepIdleMs, int& iLogicFpsLimit)
{
    if (m_pGame && g_pNetServer)
    {
        iSleepBusyMs = m_pGame->GetConfig()->GetPendingWorkToDoSleepTime();
        iSleepIdleMs = m_pGame->GetConfig()->GetNoWorkToDoSleepTime();
        iLogicFpsLimit = m_pGame->GetConfig()->GetServerLogicFpsLimit();
        return true;
    }
    return false;
}
