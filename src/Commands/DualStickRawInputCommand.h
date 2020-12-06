#ifndef __SRT__DualStickRawInputCommand__
#define __SRT__DualStickRawInputCommand__

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

#include "RawInputCommand.h"
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <Box2D/Box2D.h>
#include <Poco/BasicEvent.h>
#include <string>


class DualStickRawInputCommand :
    public RawInputCommand
{
private:
protected:
public:
    b2Vec2          m_b2v2Move;
    b2Vec2          m_b2v2Shoot;
    
    // Event(s)
    Poco::BasicEvent<const std::string&>      ExecutedEvent;
    //Poco::BasicEvent<const std::string&, b2Vec2& b2v2Move, b2Vec2& b2v2Shoot>      ExecutedEvent;
    
    // Constructor
    DualStickRawInputCommand(_RawInputDependencies& theDependencies);
    
    // Destructor
    ~DualStickRawInputCommand();
    
    // Method(s)
    virtual void Execute();
};


#endif /* defined(__SRT__DualStickRawInputCommand__) */
