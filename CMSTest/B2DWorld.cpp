//
//  B2DWorld.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "B2DWorld.h"
#include "decaf/lang/Thread.h"

B2DWorld::_Publisher                 B2DWorld::Publisher;

// Constructor(s)
/*
 B2DWorld.h::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 B2DWorld.h::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void B2DWorld::_Publisher::OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle)
{
    ICallbacks* pObjToCallback = NULL;
    
    //m_listSubscribersSwap = m_listSubscribers;
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnB2DWorldUpdate(b2vNewPosition, fNewAngle);
    }
}

void B2DWorld::_Publisher::OnB2DWorldBodyUpdate(b2Body* pBody)
{
    ICallbacks* pObjToCallback = NULL;
    
    //m_listSubscribersSwap = m_listSubscribers;
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnB2DWorldBodyUpdate(pBody);
    }
}

// Constructor(s)
B2DWorld::B2DWorld()
{
    //gravity = new b2Vec2(0.0f, -9.81f);
    gravity = new b2Vec2(0.0f, 0.0f);
    world = new b2World(*gravity);
    
    // As per https://developer.valvesoftware.com/wiki/Source_Multiplayer_Networking
    // resulting in 15ms per timeStep or tick
	timeStep = 1.0f / 66.0f;
    
	velocityIterations = 6;
	positionIterations = 2;
    
    Input::Publisher.Attach(this);
}

// Destructor
B2DWorld::~B2DWorld()
{
    Input::Publisher.Detach(this);
    
    delete gravity;
    delete world;
}

// Method(s)
void B2DWorld::CreateBodiesAndShapes()
{
    // Define the ground body.
	groundBodyDef.position.Set(0.0f, -20.0f);
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
    groundBody = world->CreateBody(&groundBodyDef);
    
	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);
    
	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
    body = world->CreateBody(&bodyDef);
    
	// Define another box shape for our dynamic body.
	dynamicBox.SetAsBox(4.0f, 4.0f);
    
	// Define the dynamic body fixture.
	fixtureDef.shape = &dynamicBox;
    
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.3f;
	body->CreateFixture(&fixtureDef);
}

void B2DWorld::Update(std::string& strText)
{
    memset(m_szBuf, 0, sizeof(m_szBuf));
    //sprintf(m_szBuf, "%4.2f %4.2f %4.2f", position.x, position.y, angle);
    sprintf(m_szBuf, "%4.2f", position.y);
    //printf("%s\n", m_szBuf);
    strText = m_szBuf;
}

// decaf::lang::Runnable implementation
void B2DWorld::run()
{
    //static bool bOneTime = true;
    //static unsigned int ui = 0;
    //static b2Vec2 ab2Vec2Move;

    while (true)
    {
        //if (bOneTime)
        //{
            //bOneTime = false;
            //body->ApplyForceToCenter(b2Vec2(20.0f, 0.0f), true);
        //}
        
//        if (ui < 100)
//        {
//            body->ApplyForceToCenter(b2Vec2(20.0f, 0.0f), true);
//            ++ui;
//        }
        
        m_b2v2MoveQueue.lock();
        //m_b2v2MoveSwapQueue = m_b2v2MoveQueue;
        //m_b2v2MoveQueue.clear();
        //m_b2v2MoveQueue.unlock();
        while (!(m_b2v2MoveQueue.empty()))
        {
            b2Vec2 ab2Vec2Move = m_b2v2MoveQueue.pop();
            ab2Vec2Move.x *= 1000.0f;
            ab2Vec2Move.y *= 1000.0f;
            body->ApplyForceToCenter(ab2Vec2Move, true);
        }
        m_b2v2MoveQueue.unlock();
        
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world->Step(timeStep, velocityIterations, positionIterations);
        
        // Now print the position and angle of the body.
        //position = body->GetPosition();
        //angle = body->GetAngle();

        //Publisher.OnB2DWorldUpdate(position, angle);
        Publisher.OnB2DWorldBodyUpdate(body);
        
        decaf::lang::Thread::currentThread()->sleep(15);
    }
}

// Input::ICallbacks implementation
void B2DWorld::OnDualStick(const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot)
{
    b2Vec2 b2v2Move;
    b2Vec2 b2v2Shoot;
    
    b2v2Move.x = pbv2Move.x();
    b2v2Move.y = pbv2Move.y();
    b2v2Shoot.x = pbv2Shoot.x();
    b2v2Shoot.y = pbv2Shoot.y();

    m_b2v2MoveQueue.lock();
    m_b2v2MoveQueue.push(b2v2Move);
    m_b2v2MoveQueue.unlock();
    //body->ApplyForceToCenter(b2v2Move, true);
    //Publisher.OnB2DWorldBodyUpdate(body);
}

