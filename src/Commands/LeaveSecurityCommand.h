#ifndef __SRT__LeaveSecurityCommand__
#define __SRT__LeaveSecurityCommand__

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

#include "SecurityCommand.h"
#include <string>


class LeaveSecurityCommand :
    public SecurityCommand
{
private:
protected:
public:
    // Event(s)
    Poco::BasicEvent<const std::string&>      ExecutedEvent;
    
    // Constructor
    LeaveSecurityCommand(_SecurityDependencies& theDependencies);
    
    // Destructor
    ~LeaveSecurityCommand();
    
    // Method(s)
    virtual void Execute();
};


#endif /* defined(__SRT__LeaveSecurityCommand__) */
