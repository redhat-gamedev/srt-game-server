#ifndef __SRT__Input__
#define __SRT__Input__

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

#if 0
#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include <Poco/BasicEvent.h>
#include <cms/MessageListener.h>
#include <string>
#include <list>

namespace cms
{
    class Message;
}
class SimpleAsyncConsumer;


class Input :
    public cms::MessageListener
{
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<DualStick::PbDualStick>     DualStickEvent;
    };

    SimpleAsyncConsumer*        m_pSimpleAsyncConsumer;

public:
    static _EventPublisher          EventPublisher;

    // Constructor(s)
    Input();
    
    // Destructor
    ~Input();
    
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
    
    // Event Firing Method(s)
    void FireDualStickEvent(DualStick::PbDualStick aPbDualStick);
};
#endif
#endif /* defined(__SRT__Input__) */
