#ifndef __CMSTest__B2DBullet__
#define __CMSTest__B2DBullet__

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

#include "AB2DEntity.h"
#include <Poco/BasicEvent.h>
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <Box2D/Box2D.h>

class AEntity;


class B2DBullet :
    public AB2DEntity
{
public:
    class _Dependencies :
        public AB2DEntity::_AB2DDefinition
    {
    protected:
        const b2Vec2&           m_b2v2GunPosition;
        const b2Vec2&           m_b2v2GunVelocity;
        b2CircleShape           m_b2CircleShape;
        
    public:
        // Constructor
        _Dependencies(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity);
        
        // Destructor()
        ~_Dependencies() {};
    };
    
private:
    
protected:    

public:
    // Constructor(s)
    B2DBullet(_Dependencies& theDependencies);

    // Destructor(s)
    ~B2DBullet();

    // Method(s)
    void Fire(b2Vec2& b2v2FiringDirection);
};


#endif /* defined(__CMSTest__B2DBullet__) */
