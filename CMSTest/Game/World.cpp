//
//  World.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "World.h"
#include "B2DWorld.h"
#include "Player.h"
#include "UserData.h"
#include "../Shared/SimpleAsyncProducer.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Common/b2Settings.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <cms/CMSException.h>
#include <decaf/lang/Thread.h>

B2DWorld*               World::m_pB2DWorld = NULL;

using namespace decaf::lang;
using namespace decaf::util::concurrent;
using namespace box2d;
using namespace cms;


// Helper(s)
void World::Setup()
{
    std::string     strWorldSimulationURI = "WORLD.SIMULATION";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    
    m_pB2DWorld = new B2DWorld();
    m_pSimulationProducer = new SimpleProducer(strBrokerURI, strWorldSimulationURI, true);

    m_pSimulationSerialDispatchQueue = new xdispatch::queue("simulation");
//    m_pSimulationDispatchTimer = new xdispatch::timer(15 * NSEC_PER_MSEC, *m_pSimulationSerialDispatchQueue);
    
    m_pProducerSerialDispatchQueue = new xdispatch::queue("producer");
    
    //B2DWorld::Publisher.Attach(this);
    Security::Publisher.Attach(this);
}

void World::Teardown()
{
    Security::Publisher.Detach(this);
    //B2DWorld::Publisher.Detach(this);

    delete m_pWorldProducerThread;
    m_pWorldProducerThread = NULL;
    
    delete m_pWorldProducer;
    m_pWorldProducer = NULL;
    
    delete m_pWorldSimulationThread;
    m_pWorldSimulationThread = NULL;
    
    delete m_pWorldSimulation;
    m_pWorldSimulation = NULL;
    
    delete m_pProducerDispatchTimer;
    m_pProducerDispatchTimer = NULL;
    
    delete m_pSimulationDispatchTimer;
    m_pSimulationDispatchTimer = NULL;
    
    delete m_pSimulationSerialDispatchQueue;
    m_pSimulationSerialDispatchQueue = NULL;
    
    m_pSimulationProducer->close();
    delete m_pSimulationProducer;
    m_pSimulationProducer = NULL;
 
    //delete m_pWorldThread;
    //m_pWorldThread = NULL;
    
    delete m_pB2DWorld;
    m_pB2DWorld = NULL;
}

// Constructor(s)
World::World() :
    m_pSimulationProducer(NULL),
    //m_pWorldThread(NULL),
    m_pSimulationSerialDispatchQueue(NULL),
    m_pSimulationDispatchTimer(NULL),
    m_pProducerSerialDispatchQueue(NULL),
    m_pProducerDispatchTimer(NULL),
    m_pWorldSimulation(NULL),
    m_pWorldSimulationThread(NULL),
    m_pWorldProducer(NULL),
    m_pWorldProducerThread(NULL)
{
    Setup();
}

// Destructor(s)
World::~World()
{
    Teardown();
}

void World::b2Vec2ToPbVec2(b2Vec2* pb2Vec2)
{
    assert(NULL != pb2Vec2);
}

void World::b2WorldToPbWorld(b2World* pb2World, PbWorld*& pPbWorldDefault)
{
    assert(NULL != pb2World);
    assert(NULL != pPbWorldDefault);
    
    b2Fixture*  pFixtureList = NULL;
    PbBody*     pPbBody = NULL;
    PbFixture*  pPbFixture = NULL;
    PbVec2*     ppbv2Gravity = new PbVec2();
    PbVec2*     ppbv2Position = new PbVec2();
    PbVec2*     pPbVec2LinearVelocity = NULL;
    PbVec2*     pPbVec2Force = NULL;
    const       b2Vec2 b2v2Gravity = pb2World->GetGravity();
    UserData*   pUserData = NULL;
    
    ppbv2Gravity->set_x(b2v2Gravity.x);
    ppbv2Gravity->set_y(b2v2Gravity.y);
    pPbWorldDefault->set_allocated_gravity(ppbv2Gravity);
    
    int iPreCount = 0;
    int iPostCount = 0;
    b2Body* pBodyList = pb2World->GetBodyList();
    for (b2Body* pBody = pBodyList; pBody; pBody = pBody->GetNext())
    {
        iPreCount = pPbWorldDefault->bodies_size();
        pPbBody = pPbWorldDefault->add_bodies();
        assert(NULL != pPbBody);
        iPostCount = pPbWorldDefault->bodies_size();
        assert(iPostCount > iPreCount);
        
        pPbBody->set_active(pBody->IsActive());
        pPbBody->set_bullet(pBody->IsBullet());
        pPbBody->set_type(DYNAMIC);
        ppbv2Position = new PbVec2();
        ppbv2Position->set_x(pBody->GetPosition().x);
        ppbv2Position->set_y(pBody->GetPosition().y);
        pPbBody->set_angle(pBody->GetAngle());
        pPbBody->set_allocated_position(ppbv2Position);
        
        pPbVec2LinearVelocity = new PbVec2();
        pPbVec2LinearVelocity->set_x(pBody->GetLinearVelocity().x);
        pPbVec2LinearVelocity->set_y(pBody->GetLinearVelocity().y);
        pPbBody->set_allocated_linear_velocity(pPbVec2LinearVelocity);
        
        pPbVec2Force = new PbVec2();
        pPbVec2Force->set_x(0.0f);
        pPbVec2Force->set_y(0.0f);
        pPbBody->set_allocated_force(pPbVec2Force);
        
        pUserData = static_cast<UserData*>(pBody->GetUserData());
        assert(NULL != pUserData);
        pPbBody->set_uuid(pUserData->m_strUUID);
        pPbBody->set_tag(pUserData->m_ui64Tag);
        
        pFixtureList = pBody->GetFixtureList();
        for (b2Fixture* pFixture = pFixtureList; pFixture; pFixture = pFixture->GetNext())
        {
            iPreCount = pPbBody->fixtures_size();
            pPbFixture = pPbBody->add_fixtures();
            assert(NULL != pPbFixture);
            iPostCount = pPbBody->fixtures_size();
            assert(iPostCount > iPreCount);
            
            pPbFixture->set_density(pFixture->GetDensity());
            pPbFixture->set_friction(pFixture->GetFriction());
        }
    }
}

// Method(s)
void World::AddPlayer(const std::string& strUUID)
{
    assert(strUUID.length() > 0);
    
    xdispatch::global_queue().sync([=]
    {
       Player* pPlayer = new Player(strUUID);
       m_listPlayers.push_front(pPlayer);
    });
}

void World::RemovePlayer(const std::string& strUUID)
{
    assert(strUUID.length() > 0);
    
    xdispatch::global_queue().sync([=]
    {
       std::list<Player*>::iterator    iterPlayerList;
       Player* pPlayer = NULL;
       
       iterPlayerList = m_listPlayers.begin();
       for (;iterPlayerList != m_listPlayers.end(); iterPlayerList++)
       {
           pPlayer = *iterPlayerList;
           if (pPlayer->ThisUUIDIsAMatch(strUUID))
           {
               m_listPlayers.erase(iterPlayerList);
               delete pPlayer;
               break;
           }
       }
    });
}

//void World::SendUpdate(PbWorld* pPbWorldDefault)
//{
//    assert(pPbWorldDefault);
//    
//    static std::string strPBBuffer = "";
//    
//    try
//    {
//        strPBBuffer.clear();
//        pPbWorldDefault->SerializeToString(&strPBBuffer);
//        const char* pucText = strPBBuffer.c_str();
//        unsigned long ulLength = strPBBuffer.length();
//        m_pSimulationProducer->Send((const unsigned char*)pucText, (int)ulLength);
//    }
//    catch ( CMSException& e )
//    {
//        e.printStackTrace();
//        //        if (NULL != pPbWorldDefault)
//        //        {
//        //            pPbWorldDefault->clear_bodies();
//        //            pPbWorldDefault->clear_joints();
//        //            delete pPbWorldDefault;
//        //            pPbWorldDefault = NULL;
//        //        }
//    }
//    
//    //    if (NULL != pPbWorldDefault)
//    //    {
//    //        pPbWorldDefault->clear_bodies();
//    //        pPbWorldDefault->clear_joints();
//    //        delete pPbWorldDefault;
//    //        pPbWorldDefault = NULL;
//    //    }
//}

void World::SendUpdate(std::string* pstrWorldUpdate)
{
    assert(pstrWorldUpdate);
    
    try
    {
        const char* pucText = pstrWorldUpdate->c_str();
        unsigned long ulLength = pstrWorldUpdate->length();
        m_pSimulationProducer->Send((const unsigned char*)pucText, (int)ulLength);
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

// Security::ICallbacks implementation
void World::OnSecurityRequestJoin(std::string& strUUID)
{
    std::string     strWorldSimulationName = "WorldSimulationThread";
    std::string     strWorldProducerName = "WorldProducerThread";
    
    AddPlayer(strUUID);
    
    if (NULL == m_pSimulationDispatchTimer)
    {
        std::cout << "Starting the world simulation" << std::endl;
        m_pWorldSimulation = new World::Simulation(this);
        m_pWorldSimulationThread = new decaf::lang::Thread(m_pWorldSimulation, strWorldSimulationName);
        m_pWorldSimulationThread->start();
        
        std::cout << "Starting the world producer" << std::endl;
        m_pWorldProducer = new World::Producer(this);
        m_pWorldProducerThread = new decaf::lang::Thread(m_pWorldProducer, strWorldProducerName);
        m_pWorldProducerThread->start();
        
        std::cout << "Starting the producer dispatch timer" << std::endl;
        m_pProducerDispatchTimer = new xdispatch::timer(5 * NSEC_PER_MSEC, *m_pProducerSerialDispatchQueue);
        m_pProducerDispatchTimer->start();
        
        std::cout << "Starting the simulation dispatch timer" << std::endl;
        m_pSimulationDispatchTimer = new xdispatch::timer(15 * NSEC_PER_MSEC, *m_pSimulationSerialDispatchQueue);
        m_pSimulationDispatchTimer->start();
    }
}

void World::OnSecurityRequestLeave(std::string& strUUID)
{
    assert(m_pB2DWorld);
    
    RemovePlayer(strUUID);
}

// decaf::lang::Runnable implementation
void World::Simulate()
{
    Player*     pPlayer = NULL;
    float32 timeStep = 1.0f / 66.0f;
    
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
    
    while (true)
    {
        xdispatch::global_queue().sync([=]
        {
           m_listPlayersSwap = m_listPlayers;
        });
        
        while (!(m_listPlayersSwap.empty()))
        {
            pPlayer = m_listPlayersSwap.front();
            m_listPlayersSwap.pop_front();
            assert(pPlayer);
            pPlayer->Update();
        }
        
        m_pSimulationSerialDispatchQueue->sync([=]
        {
            B2DWorld::world->Step(timeStep, velocityIterations, positionIterations);
            PbWorld* pPbWorldDefault = new PbWorld(); // TODO: remove memory thrash
            b2WorldToPbWorld(B2DWorld::world, pPbWorldDefault);
            std::string* pstrPBBuffer = new std::string();
            pPbWorldDefault->SerializeToString(pstrPBBuffer);
            pPbWorldDefault->Clear();
            m_aSimulationUpdateQueue.lock();
            //m_aSimulationUpdateQueue.push(pPbWorldDefault);
            m_aSimulationUpdateQueue.push(pstrPBBuffer);
            m_aSimulationUpdateQueue.unlock();
        });
        decaf::lang::Thread::currentThread()->sleep(15);
    }
}

void World::SendUpdates()
{
    //PbWorld*    pPbWorldDefault = NULL;
    //std::string*    pstrWorldUpdateToSend = NULL;
    
    while (true)
    {
        m_pProducerSerialDispatchQueue->sync([=]
        {
            m_aSimulationUpdateQueue.lock();
            //PbWorld*  pPbWorldDefault = m_aSimulationUpdateQueue.pop();
            std::string* pstrWorldUpdateToSend = m_aSimulationUpdateQueue.pop();
            m_aSimulationUpdateQueue.unlock();
            if (pstrWorldUpdateToSend)
            {
                SendUpdate(pstrWorldUpdateToSend);
                delete pstrWorldUpdateToSend; // TODO: remove memory thrash
                pstrWorldUpdateToSend = NULL;
            }
        });
        decaf::lang::Thread::currentThread()->sleep(5);
    }
}

// Constructor(s)
World::Simulation::Simulation(World* pWorld) :
    m_pWorld(pWorld)
{
    assert(m_pWorld);
}

// Destructor
World::Simulation::~Simulation()
{
    assert(m_pWorld);
}

// decaf::lang::Runnable implementation
void World::Simulation::run()
{
    assert(m_pWorld);
    
    m_pWorld->Simulate();
}

// Constructor(s)
World::Producer::Producer(World* pWorld) :
    m_pWorld(pWorld)
{
    assert(m_pWorld);
}

// Destructor
World::Producer::~Producer()
{
    assert(m_pWorld);
}

// decaf::lang::Runnable implementation
void World::Producer::run()
{
    assert(m_pWorld);
    
    m_pWorld->SendUpdates();
}
