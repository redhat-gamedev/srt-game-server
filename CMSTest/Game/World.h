//
//  World.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__World__
#define __CMSTest__World__

#include "B2DWorld.h"
#include "../Application/Security.h"
#include "../Proto/box2d.pb.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/timer.h"
#include <decaf/lang/Runnable.h>
#include <decaf/util/StlQueue.h>
#include <string>

namespace decaf
{
    namespace lang
    {
        class Thread;
    }
    namespace util
    {
        class Timer;
    }
}
class SimpleProducer;
class B2DWorld;
class Player;
class Messenger;


class World :
    public Security::ICallbacks
{
private:
    class Simulation :
        public decaf::lang::Runnable
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
    xdispatch::queue*               m_pSimulationSerialDispatchQueue;
    xdispatch::timer*               m_pSimulationDispatchTimer;

    World::Simulation*              m_pWorldSimulation;
    decaf::lang::Thread*            m_pWorldSimulationThread;

    std::list<Player*>              m_listPlayers;
    std::list<Player*>              m_listPlayersSwap;
    
    std::string                     m_strPBBuffer;
    
    Messenger*                      m_pMessenger;
    
    // Helper(s)
    void Setup();
    void Teardown();
    void b2Vec2ToPbVec2(b2Vec2* pb2Vec2);
    void b2WorldToPbWorld(b2World* pb2World, ::box2d::PbWorld*& pPbWorldDefault);
    
public:
    static B2DWorld*               m_pB2DWorld;
    
    // Constructor(s)
    World();
//    World(Messenger* pMessenger);
    
    // Destructor(s)
    ~World();

    // Method(s)
    void AddPlayer(const std::string& strUUID);
    void RemovePlayer(const std::string& strUUID);
    
    // decaf::lang::Runnable implementation
    void Simulate();
    
    // Security::ICallbacks implementation
    void OnSecurityRequestJoin(std::string& strUUID);
    void OnSecurityRequestLeave(std::string& strUUID);
};

#endif /* defined(__CMSTest__World__) */
