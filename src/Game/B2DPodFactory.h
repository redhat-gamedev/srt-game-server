#ifndef SRT_B2DPodFactory_h
#define SRT_B2DPodFactory_h

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

#include "B2DPod.h"
#include "B2DWorld.h"
#include "../Shared/FactoryT.h"


class B2DPodFactory :
    public FactoryT<B2DPod, B2DPod::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    B2DPodFactory() {};
    
    // Destructor(s)
    ~B2DPodFactory() {};
    
public:
    // Singleton
    static B2DPodFactory& Instance()//unsigned int uiCapacity)
    {
        static B2DPodFactory  aB2DPodFactory;
        return aB2DPodFactory;
    }
};


#endif
