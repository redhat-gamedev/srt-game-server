#ifndef __SRT__B2DPod__
#define __SRT__B2DPod__

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
#include <Box2D/Box2D.h>
#include <queue>
#include <mutex>

class AEntity;


class B2DPod :
    public AB2DEntity
{
public:
    class _Dependencies :
        public AB2DEntity::_AB2DDefinition
    {
    protected:
        const b2Vec2&           m_b2v2Position;
        b2CircleShape           m_b2CircleShape;
        
    public:
        // Constructor
        _Dependencies(const b2Vec2& b2v2Position);
        
        // Destructor()
        ~_Dependencies() {};
    };
    
protected:
    std::queue<b2Vec2>       m_b2v2MoveQueue;
    std::mutex               m_b2v2MoveQueueMutex;
    
public:
    // Constructor(s)
    B2DPod(_Dependencies& theDependencies);
    
    // Destructor(s)
    ~B2DPod();
    
    // Method(s)
    void Move(float fX, float fY);
    void Update();
};


#endif /* defined(__SRT__B2DPod__) */
