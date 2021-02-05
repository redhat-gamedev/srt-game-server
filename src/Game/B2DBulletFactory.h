#ifndef SRT_B2DBulletFactory_h
#define SRT_B2DBulletFactory_h

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

#include "B2DBullet.h"
#include "B2DWorld.h"
#include "../Shared/FactoryT.h"


class B2DBulletFactory :
    public FactoryT<B2DBullet, B2DBullet::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    B2DBulletFactory() {};
    
    // Destructor(s)
    ~B2DBulletFactory() {};
    
public:
    // Singleton
    static B2DBulletFactory& Instance()
    {
        static B2DBulletFactory  aB2DBulletFactory;
        return aB2DBulletFactory;
    }
};


#endif
