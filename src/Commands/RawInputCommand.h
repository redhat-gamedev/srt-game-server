#ifndef __SRT__RawInputCommand__
#define __SRT__RawInputCommand__

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

#include "ACommand.h"

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
namespace cms
{
    class BytesMessage;
}
//struct b2Vec2;


class RawInputCommand :
    public ACommand
{
public:
    class _RawInputDependencies :
        public _Dependencies
    {
    private:
    protected:
    public:
        // Constructor
        _RawInputDependencies(redhatgamedev::srt::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage);
        
        // Destructor
        ~_RawInputDependencies();
    };
    
private:
protected:
public:
    // Constructor
    RawInputCommand(_RawInputDependencies& theDependencies);
    
    // Destructor
    virtual ~RawInputCommand();
    
    // Method(s)
    virtual void Execute() = 0;
};

#endif /* defined(__SRT__RawInputCommand__) */
