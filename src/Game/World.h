#ifndef __SRT__World__
#define __SRT__World__

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

#include "B2DWorld.h"
#include "../Proto/box2d.pb.h"
#include <string>

class B2DWorld;


class World
{
private:
    class Simulation
    {
    private:
        World*      m_pWorld;
        
    public:
        // Constructor(s)
        Simulation(World* pWorld);
        
        // Destructor
        ~Simulation();
    
        // decaf::lang::Runnable implementation
        void run();
    };

protected:
//    World::Simulation*              m_pWorldSimulation;

    // Helper(s)
    void Setup();
    void Teardown();
    void b2Vec2ToPbVec2(b2Vec2* pb2Vec2);
    void b2WorldToPbWorld(b2World* pb2World, box2d::PbWorld*& pPbWorldDefault);
    
public:
    static B2DWorld*               m_pB2DWorld;
    
    // Constructor(s)
    World();
    
    // Destructor(s)
    ~World();

    void Simulate();
};


#endif /* defined(__SRT__World__) */
