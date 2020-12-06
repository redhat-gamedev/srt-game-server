#ifndef __SRT__Command__
#define __SRT__Command__

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

namespace redhatgamedev
{
    namespace srt
    {
        class CommandBuffer;
    }
}
namespace cms
{
    class BytesMessage;
}


class ICommand
{
public:
    virtual void Execute() = 0;
};


class ACommand :
    public ICommand
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        const cms::BytesMessage*                        m_pBytesMessage;
        redhatgamedev::srt::CommandBuffer*                m_pCommandBuffer;
        
        // Constructor
        _Dependencies(redhatgamedev::srt::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage);
        
        // Destructor
        virtual ~_Dependencies();
    };
    
protected:
    const cms::BytesMessage*                        m_pBytesMessage;
    redhatgamedev::srt::CommandBuffer*                m_pCommandBuffer;
    
    // Constructor
    ACommand(_Dependencies& theDependencies);
    
    // Destructor
    virtual ~ACommand();
    
public:
    // Method(s)
    virtual void Execute() = 0;
};

#endif /* defined(__SRT__Command__) */
