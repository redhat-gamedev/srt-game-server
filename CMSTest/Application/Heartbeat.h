#ifndef __CMSTest__Heartbeat__
#define __CMSTest__Heartbeat__

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

#include <Poco/BasicEvent.h>
#include <decaf/util/TimerTask.h>
#include <list>


class Heartbeat :
    public decaf::util::TimerTask
{
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<const int&>     BeatEvent;
    };
    
public:
    static _EventPublisher              EventPublisher;

    // Constructor(s)
    Heartbeat();
    
    // Destructor(s)
    ~Heartbeat();
    
    // Event Firing Method(s)
    void FireBeatEvent(const int& iBeat);
    
    // decaf::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Heartbeat__) */
