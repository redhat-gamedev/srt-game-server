//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "Timer.h"
#include <assert.h>
//#include "mmgr/mmgr.h"


namespace Rock2D
{
    // Bring the statics into this space
    long				Timer::s_liCountsPerSecond;
    long				Timer::s_liThisCounts;
    long				Timer::s_liLastCounts;
    float				Timer::s_fTargetFPS = 60.0f;
    float				Timer::s_fActualFPS = 0.0f;
    float				Timer::s_fSpeedFactor = 0.0f;
    bool				Timer::s_bPaused = false;	// Start UnPaused...
    DWORD				Timer::s_dwThisTime = 0;
    DWORD				Timer::s_dwLastTime = 0;
    Timer*				Timer::s_pTimer = NULL;

    std::list<Timer*>				Timer::s_listTimers;
    std::list<Timer*>				Timer::s_listTimersSwap;
    std::list<Timer*>				Timer::s_listTimersToRemove;
    //std::list<Timer*>				Timer::s_listTimersPaused;
    std::list<Timer*>::iterator		Timer::s_iterTimer;

    Timer::ICallbacks*							Timer::s_pObjToNotify = NULL;
    std::list<Timer::ICallbacks*>				Timer::s_listElementsToUpdate;
    std::list<Timer::ICallbacks*>				Timer::s_listElementsToUpdateSwap;
    std::list<Timer::ICallbacks*>				Timer::s_listRemoveNotifications;
    std::list<Timer::ICallbacks*>::iterator		Timer::s_iterUpdateElement;

    // Flags for behaviour of this timer
    const BYTE	Timer::STARTEXPIRED		= (1 << 0);
    const BYTE	Timer::AUTOREMOVE		= (1 << 1);
    const BYTE	Timer::AUTORESTART		= (1 << 2);
    const BYTE	Timer::STARTINACTIVE	= (1 << 3);


    // Constructor(s)
    Timer::Timer(const DWORD& dwDuration,
                 const BYTE& byteFlags,
                 const DWORD& dwStartTime)
    {
        assert(0 != dwDuration);

        Configure(dwDuration, byteFlags, dwStartTime);

        // Attach this to the master list of timers
        if (!(byteFlags & STARTINACTIVE))
        {
            s_listTimers.push_front(this);
        }
        
        m_pObjToNotify = NULL;
    }

    Timer::Timer(ICallbacks* pObjToNotify,
                 const DWORD& dwDuration,
                 const BYTE& byteFlags,
                 const DWORD& dwStartTime)
    {
        //assert(0 != dwDuration);
        assert(pObjToNotify);

        Configure(dwDuration, byteFlags, dwStartTime);

        // Attach this to the master list of timers
        if (!(byteFlags & STARTINACTIVE))
        {
            s_listTimers.push_front(this);
        }

        m_pObjToNotify = pObjToNotify;	
    }

    // Destructor(s)
    Timer::~Timer()
    {
    //RNK 050709 (?)
    //	assert(SCHEDULED != m_eStatus);
        
        // No doubt...
        m_eStatus = NUMSTATUSTYPES;
        m_dwTimeLeft = 0;
        m_dwStartTime = 0;
        m_dwEndTime = 0;

        // Remove this from the master list of timers to be updated
        s_listTimers.remove(this);
        s_listTimersSwap.remove(this);
    //	s_listTimersPaused.remove(this);
        s_listTimersToRemove.remove(this);
        
        m_pObjToNotify = NULL;
    }

    // Retrieves the frequency of the high performance counter
    // if one is available
    void Timer::Initialize()
    {	
        //TODO
        s_liCountsPerSecond = 0;
        // Ensure we have a count frequency
        //if (QueryPerformanceFrequency(&s_liCountsPerSecond)) {
        Timer::QueryPerformanceCounter(&s_liThisCounts);
        s_liLastCounts = s_liThisCounts;
        //}
        
        Update();
    }

    // Helper(s)
    void Timer::Configure(const DWORD& dwDuration, const BYTE& byteFlags, const DWORD& dwStartTime)
    {
        // When does this timer start?
        m_dwStartTime = timeGetTime() + dwStartTime;
        
        // Set the length this will last
        m_dwDuration = dwDuration;
        m_dwTimeLeft = m_dwDuration;
        
        // When does this end?
        m_dwEndTime = m_dwStartTime + m_dwDuration;
        
        // Set the flags for this instance
        m_byteFlags = byteFlags;
        
        // Set the current status
        if ((m_byteFlags & STARTEXPIRED) || (0 == m_dwDuration))
        {
            m_eStatus = EXPIRED;
        }
        else
        {
            m_eStatus = COUNTING;
        }
        
        if (m_dwStartTime > 0)
        {
            m_eStatus = SCHEDULED;
        }
    }

    void Timer::UpdateChildInstances()
    {
        if (s_listTimers.empty())
        {
            return;
        }
        
        s_listTimersSwap = s_listTimers;
        while(!s_listTimersSwap.empty())
        {
            s_pTimer = s_listTimersSwap.front();
            s_listTimersSwap.pop_front();
            
            assert(s_pTimer);
            
            // Update this timer instance
            s_pTimer->UpdateInstance();
            /*
            // Check this timer's state and take action
            // if required
            switch(s_pTimer->Status())
            {
                case SCHEDULED:
                    break;
                case COUNTING:
                    break;
                case PAUSED:
                    //			s_listTimersPaused.push_front(s_pTimer);
                    //			s_listTimers.remove(s_pTimer);
                    break;
                case EXPIRED:
                    // See if we need to remove this timer
                    if (s_pTimer->Is(AUTOREMOVE))
                    {
                        s_listTimersToRemove.push_front(s_pTimer);
                    }
                    // See if we need to restart this timer
                    if (s_pTimer->Is(AUTORESTART))
                    {
                        s_pTimer->Restart();
                    }
                    break;
                default:
                    assert(false);
                    break;
            }
            */
        }
    }

    void Timer::UpdateData()
    {
        // Record what the last time was
        s_dwLastTime = s_dwThisTime;
        
        // Record what the last counts was
        s_liLastCounts = s_liThisCounts;
        
        // Update this time
        s_dwThisTime = Timer::timeGetTime();
        if (0 == s_dwLastTime)
        {
            s_dwLastTime = s_dwThisTime-10;
        }
        
        // Update this counts
        Timer::QueryPerformanceCounter(&s_liThisCounts);
        
        // Calculate this frames speed factor
        //TODO
        //s_fSpeedFactor = static_cast<float>(s_liThisCounts.QuadPart - s_liLastCounts.QuadPart)/(static_cast<float>(s_liCountsPerSecond.QuadPart)/s_fTargetFPS);
        s_fSpeedFactor = static_cast<float>(s_liThisCounts - s_liLastCounts)/(static_cast<float>(s_liCountsPerSecond)/s_fTargetFPS);
        s_fActualFPS = s_fTargetFPS/s_fSpeedFactor;
    }

    // Operation(s)
    // Allows the client to pause this timer
    void Timer::Pause()
    {
        //if (COUNTING == m_eStatus)
        if (EXPIRED != m_eStatus)
        {
            if ((NULL != m_pObjToNotify) && (PAUSED != m_eStatus))
            {
                m_pObjToNotify->OnPause();
            }		
            
            m_eStatus = PAUSED;
        }
    }

    // Allows the client to unpause and resume this timer
    void Timer::UnPause()
    {
        if (PAUSED == m_eStatus)
        {
            m_eStatus = COUNTING;
            m_dwStartTime = s_dwThisTime;
            m_dwEndTime = s_dwThisTime + m_dwTimeLeft;

            if (NULL != m_pObjToNotify)
            {
                m_pObjToNotify->OnUnPause();
            }		
        }
    }

    // Allows the client to reset this timer
    // to it's starting values.
    void Timer::Restart(const DWORD& dwRestartTime)
    {
        assert(SCHEDULED != m_eStatus);
        
        // Reset the start time
        m_dwStartTime = dwRestartTime;

        // Reset the end time to now + duration
        //m_dwEndTime = m_dwStartTime + m_dwDuration;
        m_dwEndTime = Timer::timeGetTime() + m_dwDuration;
        m_dwTimeLeft = m_dwDuration;

        // Reset the status
        if (EXPIRED == m_eStatus)
        {
            m_eStatus = COUNTING;
        }
    }

    // Allows the client to reset this timer
    // to new values.
    void Timer::Reset(	const DWORD& dwDuration,
                        const BYTE&	byteFlags,
                        const DWORD& dwStartTime)
    {
        Configure(dwDuration, byteFlags, dwStartTime);
        
        if (byteFlags & STARTINACTIVE)
        {
            //s_listTimersToRemove.push_front(this);
            s_listTimers.remove(this);
        }
        
        //s_listTimers.remove(this);
    }

    void Timer::Activate()
    {
        assert(m_byteFlags & STARTINACTIVE);
        
        s_listTimers.push_front(this);	
    }

    void Timer::Deactivate()
    {
        assert(m_byteFlags & STARTINACTIVE);
        
        s_listTimers.remove(this);
        
    //	if (PAUSED == m_eStatus)
    //	{
    //		s_listTimersPaused.remove(this);
    //	}
    }

    // Master update which when called will update all timers
    // that have been created.
    void Timer::Update()
    {
        UpdateData();

        // If we're not paused update the times and the timers
        if (!s_bPaused)
        {
            if (!s_listTimers.empty())
            {
                UpdateChildInstances();
            }

            // Update those elements that need to be notified
            s_listElementsToUpdateSwap.clear();
            s_listElementsToUpdateSwap = s_listElementsToUpdate;
            while (!s_listElementsToUpdateSwap.empty())
            {
    #ifdef DEBUG
    //			printf("Update_: [%0x][%d][%d]\n", s_listElementsToUpdateSwap.front(), s_listElementsToUpdate.size(), s_listElementsToUpdateSwap.size());
    #endif		
                s_pObjToNotify = s_listElementsToUpdateSwap.front();
                s_listElementsToUpdateSwap.pop_front();
                assert(s_pObjToNotify);
                s_pObjToNotify->OnFrame();
            }

            // If we have any timers to remove, do so
            while(s_listTimersToRemove.size() > 0)
            {
                s_pTimer = *s_listTimersToRemove.begin();
                s_listTimersToRemove.pop_front();
                s_listTimers.remove(s_pTimer);
                //s_listTimersPaused.remove(s_pTimer);
                
                delete s_pTimer;
                s_pTimer = NULL;
            }
        }
        /*
        else
        {
            // We're paused so let the timers update their end times
            // Update all the child instances
            s_iterTimer = s_listTimers.begin();
            for(; s_iterTimer != s_listTimers.end(); s_iterTimer++)
            {
                // Only dereference once
                s_pTimer = (*s_iterTimer);

                // Update this timer instance
                s_pTimer->UpdateInstance();
            }
        }
        */
    }

    // Allows the client to remove a timer from the list when
    // finished with it if AUTOREMOVE is not set on construction
    void Timer::Remove(Timer* pTimer)
    {

        assert(pTimer);

        s_listTimers.remove(pTimer);
        s_listTimersSwap.remove(pTimer);
    //	s_listTimersPaused.remove(pTimer);
        s_listTimersToRemove.remove(pTimer);

        delete pTimer;
        pTimer = NULL;
    }

    // Allows the client to remove all timers from the list when
    // finished with them.
    void Timer::RemoveAll()
    {
        while(!s_listTimers.empty())
        {
            s_pTimer = s_listTimers.front();
            s_listTimers.pop_front();
            delete s_pTimer;
            s_pTimer = NULL;
        }
        s_listTimersSwap.clear();
    }

    // Allows the client to pause all timers that are currently
    // active in the system at once.
    void Timer::PauseAll()
    {
    #ifdef DEBUG 
        printf("Timer::PauseAll().\n");
    #endif
        
        if (s_bPaused)
        {
    #ifdef DEBUG 
            printf("Already paused... bailing.\n");
    #endif
            return;
        }

        // Tell all the timers to pause
        s_iterTimer = s_listTimers.begin();
        for(; s_iterTimer != s_listTimers.end(); s_iterTimer++)
        {
            (*s_iterTimer)->Pause();
        }

        // Changes how Update behaves
        s_bPaused = true;
    }

    // Allows the client to UnPause all the timers that are
    // currently active in the system at once.
    void Timer::UnPauseAll()
    {
    #ifdef DEBUG 
        printf("Timer::UnPauseAll().\n");
    #endif
        
        // Ensure we were paused
        if (s_bPaused)
        {
            // Update the last time to be this time so we don't get
            // a big jump in time
            //s_dwLastTime = s_dwThisTime;
            UpdateData();

            // Unpause all the timers
            s_iterTimer = s_listTimers.begin();
            for(; s_iterTimer != s_listTimers.end(); s_iterTimer++)
            {
                (*s_iterTimer)->UnPause();
            }

            // UnPause...
            s_bPaused = false;
        }
    }

    // Allows the master Update function
    // to update each of the timer instances
    void Timer::UpdateInstance()
    {
        if ((s_bPaused) || (PAUSED == m_eStatus))
        {
            // Push ahead our times
            //m_dwStartTime += s_dwThisTime - s_dwLastTime;
            //m_dwEndTime += s_dwThisTime - s_dwLastTime;
            return;
        }
        
        switch(m_eStatus)
        {
            case SCHEDULED:
                if (s_dwThisTime >= m_dwStartTime)
                {
                    m_eStatus = COUNTING;
                }
                break;
            case COUNTING:
                // See if this is past it's end time
                if (s_dwThisTime >= m_dwEndTime)
                {
                    m_eStatus = EXPIRED;
                    m_dwTimeLeft = 0;
                }
                else
                {
                    m_dwTimeLeft = m_dwEndTime - s_dwThisTime;
                }
                
                if (NULL != m_pObjToNotify)
                {
                    m_pObjToNotify->OnFrame();
                    m_pObjToNotify->OnFrame(TimeT());
                }
                break;
    //		case PAUSED:
    //			// Push ahead our times
    //			m_dwStartTime += s_dwThisTime - s_dwLastTime;
    //			m_dwEndTime += s_dwThisTime - s_dwLastTime;
    //			break;
            case EXPIRED:
                // See if we need to remove this timer
                if (Is(AUTOREMOVE))
                {
                    s_listTimersToRemove.push_front(this);
                }
                // See if we need to restart this timer
                if (Is(AUTORESTART))
                {
                    Restart();
                }
                break;
                
                break;
            default:
                assert(false);
                break;
        }
    }

    // Allows clients to register for system notifications such as OnFrame...
    void Timer::RegisterForUpdate(ICallbacks* pObjToNotify)
    {
        assert(pObjToNotify);
        
        do
        {
            if ((s_listElementsToUpdate.empty()) || 
                (0 == pObjToNotify->Priority()))
            {
                s_listElementsToUpdate.push_back(pObjToNotify);
                break;
            }
            
            // 1 being the highest, 255 the lowest priority...
            if (s_listElementsToUpdate.front()->Priority() > pObjToNotify->Priority())
            {
                s_listElementsToUpdate.push_front(pObjToNotify);
                break;
            }

            // See if it should go last
            if (s_listElementsToUpdate.back()->Priority() < pObjToNotify->Priority())
            {
                s_listElementsToUpdate.push_back(pObjToNotify);
                break;
            }
            
            // Somewhere in between
            s_listElementsToUpdate.push_front(pObjToNotify);
            s_listElementsToUpdate.sort(ICallbacks::Compare);	
        }
        while (false); // do once
        
    #ifdef DEBUG
    //	printf("Added__: [%0x][%d]\n", pObjToNotify, s_listElementsToUpdate.size());
    #endif
    }

    // Allows clients to deregister for system notifications such as OnFrame...
    void Timer::UnRegisterForUpdate(ICallbacks* pObjToNotify)
    {
        assert(pObjToNotify);
        assert(!s_listElementsToUpdate.empty());

    //	s_listRemoveNotifications.push_front(pObjToNotify);

        s_listElementsToUpdateSwap.remove(pObjToNotify);
        s_listElementsToUpdate.remove(pObjToNotify);
        
    #ifdef DEBUG
    //	printf("Removed: [%0x][%d][%d]\n", pObjToNotify, s_listElementsToUpdate.size(), s_listElementsToUpdateSwap.size());
    #endif	
    }

    // Allows clients to see if they previously registered for updates
    bool Timer::Registered(ICallbacks* pObjToNotify)
    {
        assert(pObjToNotify);
        
        std::list<ICallbacks*>	listRegisteredObjects = s_listElementsToUpdate;
        
        while(!listRegisteredObjects.empty())
        {
            if (listRegisteredObjects.front() == pObjToNotify)
            {
                listRegisteredObjects.clear();
                return true;
            }
            listRegisteredObjects.pop_front();
        }
        return false;
    }


    // Used each frame to unregister any objects that have requested removal
    void Timer::UnRegisterObjects()
    {
        if (s_listRemoveNotifications.size() > 0)
        {
            s_iterUpdateElement = s_listRemoveNotifications.begin();
            for(;s_iterUpdateElement != s_listRemoveNotifications.end(); s_iterUpdateElement++)
            {
    #ifdef DEBUG
    //			printf("Removing: %0x", *s_iterUpdateElement);
    #endif
                s_listElementsToUpdate.remove(*s_iterUpdateElement);
            }

            // Clear the list
            s_listRemoveNotifications.clear();
        }
    }

    DWORD Timer::timeGetTime()
    {
        struct timeval theCurrentTime = {0,0};
        gettimeofday(&theCurrentTime, NULL);
        
        // On return convert micro seconds to milli seconds as originally
        // returned by timeGetTime;
        //return ((theCurrentTime.tv_sec * 1000000) + (theCurrentTime.tv_usec))/1000;
        return ((theCurrentTime.tv_usec / 1000) + (theCurrentTime.tv_sec * 1000));
    }

    void Timer::QueryPerformanceCounter(long* pliThisCounts)
    {
        assert(pliThisCounts);
        
        struct timeval theCurrentTime = {0,0};
        
        gettimeofday(&theCurrentTime, NULL);
        //s_liThisCounts = theCurrentTime.tv_usec;	
        *pliThisCounts = theCurrentTime.tv_usec;
    }

    bool Timer::ICallbacks::Compare(ICallbacks* pObjToNotify1, ICallbacks* pObjToNotify2)
    {
        assert(pObjToNotify1);
        assert(pObjToNotify1);
        
        if (pObjToNotify1->m_ucPriority < pObjToNotify2->m_ucPriority)
        {
            return true;
        }
        return false;
    }

    float Timer::TimeT()
    {
        if (s_dwThisTime >= m_dwEndTime)
        {
            return 0.0f;
        }
        //return static_cast<float>(m_dwEndTime - s_dwThisTime)/static_cast<float>(m_dwDuration);
        return static_cast<float>(m_dwTimeLeft)/static_cast<float>(m_dwDuration);
    }
}
