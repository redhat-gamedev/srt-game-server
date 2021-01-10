#ifndef __SRT__Bullet__
#define __SRT__Bullet__

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

#include "AEntity.h"
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <Box2D/Box2D.h>
#include <Poco/BasicEvent.h>
#include <string>

namespace Rock2D
{
    class Timer;
}
class AB2DEntity;


class Bullet :
    public AEntity
{
    friend class Pod;
    friend class BulletFactory;

private:
    static uint32_t         s_ui32Count;
    
protected:
    bool                    m_bAlive;
    Rock2D::Timer*          m_pLifeTimer;
    
public:
    // Event(s)
    static Poco::BasicEvent<Bullet*&>    UpdatedEvent;
    
    // Constructor(s)
    Bullet(_Dependencies& theDependencies);
    
    // Destructor(s)
    ~Bullet();
    
    // Method(s)
    const bool Alive() { return m_bAlive; }
    void Fire(b2Vec2& b2v2FiringDirection);

    // Override(s)
    void Update();
};

#endif /* defined(__SRT__Bullet__) */
