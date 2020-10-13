#ifndef __CMSTest__SecurityCommand__
#define __CMSTest__SecurityCommand__

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
#include "Poco/BasicEvent.h"
#include <string>

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


class SecurityCommand :
    public ACommand
{
public:
    class _SecurityDependencies :
        public _Dependencies
    {
    private:
    protected:
    public:
        // Constructor
        _SecurityDependencies(usx::geofactions::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage);
        
        // Destructor
        ~_SecurityDependencies();
    };
    
private:
protected:
public:
    // Constructor
    SecurityCommand(_SecurityDependencies& theDependencies);
    
    // Destructor
    virtual ~SecurityCommand();
    
    // Method(s)
    virtual void Execute() = 0;
};

#endif /* defined(__CMSTest__SecurityCommand__) */
