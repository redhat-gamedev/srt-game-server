#ifndef __SRT__Server__
#define __SRT__Server__

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

#include "../Events/EventDispatcher.h"
#include "../Network/MessageDispatcher.h"
#include "../Network/MessageConsumer.h"
#include "../Commands/CommandConsumer.h"
#include "../Commands/CommandQueue.h"
#include "../Game/B2DWorld.h"
#include "../Proto/box2d.pb.h"
#include <string>
#include <thread>

class World;
class Pod;


class Server
{
// Class
private:
    bool                    m_bStop;
    bool                    m_bIsStopped;
    
protected:

public:
    
// Instance
private:
    
protected:
    World*                  m_pWorld;
    
    std::thread*            m_pMainThread;
    
    EventDispatcher&        m_theEventDispatcher;
    MessageDispatcher&      m_theMessageDispatcher;
    
    MessageConsumer&        m_theMessageConsumer;
    CommandConsumer&        m_theCommandConsumer;
    CommandQueue&           m_theCommandQueue;
    
    // Helper(s)
    void Setup();
    void Teardown();
    void run();

public:
    // Constructor(s)
    Server(EventDispatcher& theEventDispatcher,
           MessageDispatcher& theMessageDispatcher,
           MessageConsumer& theMessageConsumer,
           CommandConsumer& theCommandConsumer,
           CommandQueue& theCommandQueue);
    
    // Destructor(s)
    ~Server();
    
    // Method(s)
    void Stop();
    void Launch();

    // Accessor(s)
    bool& IsStopped = m_bIsStopped;
};

#endif /* defined(__SRT__Server__) */
