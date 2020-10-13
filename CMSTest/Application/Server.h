#ifndef __CMSTest__Server__
#define __CMSTest__Server__

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
#include "../Game/Input.h"
#include "../Proto/box2d.pb.h"
#include <decaf/lang/Runnable.h>
#include <string>

namespace decaf
{
    namespace lang
    {
        class Thread;
    }
    namespace util
    {
        class Timer;
    }
}
class Security;
class World;
class Pod;

using namespace decaf::lang;


class Server :
    public decaf::lang::Runnable
{
// Class
private:
    
protected:

public:
    
// Instance
private:
    
protected:
    //Input*                  m_pInput;
    World*                  m_pWorld;
    
    decaf::lang::Thread*    m_pMainThread;
    
    EventDispatcher&        m_theEventDispatcher;
    MessageDispatcher&      m_theMessageDispatcher;
    
    MessageConsumer&        m_theMessageConsumer;
    CommandConsumer&        m_theCommandConsumer;
    CommandQueue&           m_theCommandQueue;
    
    // Helper(s)
    void Setup();
    void Teardown();
    
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
    // decaf::lang::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Server__) */
