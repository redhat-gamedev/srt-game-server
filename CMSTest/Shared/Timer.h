// Basic timer class which will allow us to
// more easily do time based updates and
// actions.
// Author: Roddie Kieley
// Date: August 4th, 2003


#pragma once

#include "Types.h"
#include <sys/time.h>
#include <list>

namespace Rock2D
{
    class Timer
    {
    public:
        // Interface for class which when implemented
        // will allow the implementing class to be updated
        // each frame and be notified if the application
        // pauses and unpauses. ie. global time changes.
        class ICallbacks
        {
            friend class	Timer;
        private:
            static bool			Compare(ICallbacks* pObjToNotify1, ICallbacks* pObjToNotify2);
        protected:
            // Priority goes from 1 being the highest to 255 being the lowest and
            // represents the order that the objects should be updated in.
            // 0 indicates no priority and it doesn't matter when it's updated
            // which is the default
            unsigned char	m_ucPriority;
            
            const unsigned char	Priority() { return m_ucPriority; };
        public:
            ICallbacks(unsigned char ucPriority = 0) : m_ucPriority(ucPriority) {};
            virtual ~ICallbacks() {};
            virtual void OnFrame() {};
            virtual void OnFrame(float fT) {};
            virtual void OnPause() {};
            virtual void OnUnPause() {};
        };
        
    public:
        // Data types
        // Current state of the timer
        enum EStatus	{ SCHEDULED, PAUSED, COUNTING, EXPIRED, NUMSTATUSTYPES };

        // Flags for behaviour of this timer
        static const BYTE	STARTEXPIRED;// = (1 << 0);
        static const BYTE	AUTOREMOVE;// = (1 << 1);		// Possibly not so useful
        static const BYTE	AUTORESTART;// = (1 << 2);
        static const BYTE	STARTINACTIVE;

        // Static Data
        // Current time value for all timers
        static DWORD						s_dwThisTime;

        // Last time value for all timers
        static DWORD						s_dwLastTime;

        // For global pausing so that ThisTime doesn't get updated
        static bool							s_bPaused;

        // Master list of timers that have been created
        static std::list<Timer*>			s_listTimers;
        static std::list<Timer*>			s_listTimersSwap;
    //	static std::list<Timer*>			s_listTimersPaused;

        // Master iterator helper
        static std::list<Timer*>::iterator	s_iterTimer;

        // Master helper pointer for the current iterator
        static Timer*						s_pTimer;

        // Master list of timers to be remove this time around
        static std::list<Timer*>			s_listTimersToRemove;

        // High Performance counter data
        // The resolution of the high-performance counter
        static long							s_liCountsPerSecond;

        // Number of counts this time around
        static long							s_liThisCounts;

        // Number of counts last time around
        static long							s_liLastCounts;

        // The target FPS which everything will be adjusted to
        static float						s_fTargetFPS;

        // Actual current FPS
        static float						s_fActualFPS;

        // Calculated speedfactor to adjust rates by to achieve
        // the target fps
        static float						s_fSpeedFactor;

        // List of object's that need OnFrame updates
        static ICallbacks*							s_pObjToNotify;
        static std::list<ICallbacks*>				s_listElementsToUpdate;
        static std::list<ICallbacks*>				s_listElementsToUpdateSwap;
        
        // Iterator to help traverse the update list
        static std::list<ICallbacks*>::iterator		s_iterUpdateElement;

        // List of notification to objects to be removed. Used when clients call
        // to be UnRegistered for notifications so that iterators don't get
        // invalidated if the object requests removal when being notified.
        static std::list<ICallbacks*>				s_listRemoveNotifications;

        // Class Functions
        // Retrieves the frequency of the high performance counter
        // if one is available
        static void		Initialize();

        // List of all timers that have been created
        // Static functions
        // Master update which when called will update all timers
        // that have been created.
        static void		Update();

        // Allows the client to remove a timer from the list when
        // finished with it if AUTOREMOVE is not set on construction
        static void		Remove(Timer* pTimer);

        // Allows the client to remove all timers from the list when
        // finished with them.
        static void		RemoveAll(); // RemoveAll side comment
        // RemoveAll after comment

        // Allows the client to pause all timers that are currently
        // active in the system at once.
        static void		PauseAll();

        // Allows the client to UnPause all the timers that are
        // currently active in the system at once.
        static void		UnPauseAll();

        // Get this time
        static const DWORD	ThisTime() { return s_dwThisTime; };

        // Get last time
        static const DWORD	LastTime() { return s_dwLastTime; };

        // Get time change
        static const DWORD	TimeChange() { return (s_dwThisTime - s_dwLastTime); };

        // High-Performance counter functionality
        // Get the # of counts per second
        static const long	CountsPerSecond() { return s_liCountsPerSecond; };

        // Get the # of counts this time around
        static const long	ThisCounts() { return s_liThisCounts; };

        // Get the # of counts last time around
        static const long	LastCounts() { return s_liLastCounts; };

        // Get the counts change between frames
        //TODO
        //static const LONGLONG	CountsChange() { return s_liThisCounts.QuadPart - s_liLastCounts.QuadPart); };
        static const LONGLONG	CountsChange() { return (s_liThisCounts - s_liLastCounts); };

        // Get the current set target FPS
        static const float TargetFPS() { return s_fTargetFPS; };

        // Set the target FPS
        static const void SetTargetFPS(const float fTargetFPS) { s_fTargetFPS = fTargetFPS; };
        
        // Get the actual FPS
        static const float ActualFPS() { return s_fActualFPS; };

        // Get the current speed factor, ie. what you need to multiply
        // you're value by to have it equal to the target fps rate
        static const float SpeedFactor() { return s_fSpeedFactor; };

        // Allow the client to query the number of active timers
        static const DWORD	NumberOfTimers() { return s_listTimers.size(); };
        
        // Allows clients to register for system notifications such as OnFrame...
        static void			RegisterForUpdate(ICallbacks* pObjToNotify);

        // Allows clients to deregister for system notifications such as OnFrame...
        static void			UnRegisterForUpdate(ICallbacks* pObjToNotify);
        
        // Allows clients to see if they previously registered for updates
        static bool			Registered(ICallbacks* pObjToNotify);

        // Used each frame to unregister any objects that have requested removal
        static void			UnRegisterObjects();

        static void			QueryPerformanceCounter(long* pliThisCounts);
        
        static	void		UpdateData();

        static	void		UpdateChildInstances();

    private:

    protected:
        // Keep track of the current state of this timer
        EStatus		m_eStatus;

        // Time state information for this instance
        DWORD		m_dwStartTime;
        DWORD		m_dwDuration;
        DWORD		m_dwEndTime;
        
        // For Pausing and UnPausing...
        DWORD		m_dwTimeLeft; 

        // Flags for this instance
        BYTE		m_byteFlags;
        
        // Single object that this instance can be instructed to notify
        // each time it's updated. Will only be updated when COUNTING.
        ICallbacks*	m_pObjToNotify;

        // Allows the master Update function
        // to update each of the timer instances
        void		UpdateInstance();

        // Allows the master Update function
        // to query this instance flags
        int			Is(const BYTE& byteFlag) { return (m_byteFlags & byteFlag); }

        // Helper(s)
        void		Configure(const DWORD& dwDuration, const BYTE& byteFlags, const DWORD& dwStartTime);
        
    public:

        static DWORD		timeGetTime();

        // Constructor(s)
        //TODO
        Timer(	const DWORD& dwDuration,
                const BYTE&	byteFlags = 0,
                const DWORD& dwStartTime = 0); // where 0 is now

        Timer(	ICallbacks* pObjToNotify,
                const DWORD& dwDuration,
                const BYTE&	byteFlags = 0,
                const DWORD& dwStartTime = 0); // where 0 is now

        // Destructor(s)
        virtual ~Timer();

        // Operation(s)
        // Allows the client to pause this timer
        void	Pause();// { if (COUNTING == m_eStatus) m_eStatus = PAUSED; };

        // Allows the client to unpause and resume this timer
        void	UnPause();// { if (PAUSED == m_eStatus) m_eStatus = COUNTING; };

        // Allows the client to reset this timer
        // to it's starting values. By default
        // restarts now, although can be scheduled
        // to restart at a given time
        //void	Restart(const DWORD& dwRestartTime = Timer::ThisTime());
        void	Restart(const DWORD& dwRestartTime = timeGetTime());

        // Allows the client to reset this timer
        // to new values.
        void	Reset(	const DWORD& dwDuration,
                        const BYTE&	byteFlags = 0,
                        //const DWORD& dwStartTime = Timer::ThisTime());
                        //const DWORD& dwStartTime = timeGetTime());
                        const DWORD& dwStartTime = 0); // where 0 is now

        // Must be used with STARTINACTIVE
        void	Activate();
        void	Deactivate();
        
        // Allows the client to query for the status of this timer
        EStatus	Status() { return m_eStatus; };

        // Allows the client to query the timer to see how much
        // time is left for this specific instance
        //DWORD	TimeLeft() { if (EXPIRED != m_eStatus) return (m_dwEndTime - s_dwThisTime); else return 0; };
        DWORD	TimeLeft() { return m_dwTimeLeft; };

        // Allows clients to query this timer for the t value
        // in the range 0 to 1 which represents the time gone
        // in the timer.
        float	TimeT();// { return static_cast<float>(m_dwEndTime - s_dwThisTime)/static_cast<float>(m_dwDuration); };
    };
}
