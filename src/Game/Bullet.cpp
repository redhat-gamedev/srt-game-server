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

#include "Bullet.h"

#include "B2DWorld.h"
#include "AB2DEntity.h"
#include "B2DBullet.h"
#include "../Shared/Timer.h"
#include <box2d/box2d.h>
#include "../Shared/MakeT.h"
#include <Poco/Delegate.h>
#include <string>
#include <assert.h>

Poco::BasicEvent<Bullet*&>  Bullet::UpdatedEvent;
uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::Bullet(_Dependencies& theDependencies) :
    m_bAlive(true),
    m_pLifeTimer(new Rock2D::Timer(3000)),
    AEntity(theDependencies.UUID,
            (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count), theDependencies.pB2DEntity)
{
    assert(m_pB2DEntity);

    ++s_ui32Count;
    
    m_pB2DEntity->SetParentEntity(this);
}

// Destructor(s)
Bullet::~Bullet()
{
    delete m_pLifeTimer;
    m_pLifeTimer = NULL;
}

// Method(s)
void Bullet::Fire(b2Vec2& b2v2FiringDirection)
{
    assert(m_pB2DEntity);
    
    ((B2DBullet*)m_pB2DEntity)->Fire(b2v2FiringDirection);
}

// Override(s)
void Bullet::Update()
{
    assert(m_pLifeTimer);

    if (m_pLifeTimer->Status() == Rock2D::Timer::EXPIRED)
    {
        m_bAlive = false;
        return;
    }
    
    Bullet* pBullet = this;
    UpdatedEvent(this, pBullet);
}
