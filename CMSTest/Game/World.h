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
#include <decaf/lang/Runnable.h>
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


class World :
    public decaf::lang::Runnable,
    public B2DWorld::ICallbacks,
    public Security::ICallbacks
{
private:
    
protected:
    SimpleProducer*                 m_pSimulationProducer;
    decaf::lang::Thread*            m_pWorldThread;
    
    std::list<Player*>              m_listPlayers;
    std::list<Player*>              m_listPlayersSwap;
    
    // Helper(s)
    void Setup();
    void Teardown();
    void b2Vec2ToPbVec2(b2Vec2* pb2Vec2);
    void b2WorldToPbWorld(b2World* pb2World, ::box2d::PbWorld*& pPbWorldDefault, std::string& strPBBuffer);
    
public:
    static B2DWorld*               m_pB2DWorld;
    
    // Constructor(s)
    World();
    
    // Destructor(s)
    ~World();

    // Method(s)
    void AddPlayer(const std::string& strUUID);
    void RemovePlayer(const std::string& strUUID);
    
    // B2DWorld::ICallbacks implementation
    void OnB2DWorldUpdate(b2World* pWorld);
    void OnB2DWorldBodyUpdate(b2Body* pBody);
    
    // Security::ICallbacks implementation
    void OnSecurityRequestJoin(std::string& strUUID);
    void OnSecurityRequestLeave(std::string& strUUID);
    
    // decaf::lang::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__World__) */
