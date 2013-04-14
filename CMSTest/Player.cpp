//
//  Player.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Player.h"
//#include "../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "B2DWorld.h"
#include <assert.h>

Player::_Publisher                 Player::Publisher;

// Constructor(s)
/*
 Player::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 Player::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void Player::_Publisher::OnPlayerCreated(std::string& strUUID)
{
    ICallbacks* pObjToCallback = NULL;
    
    //m_listSubscribersSwap = m_listSubscribers;
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnPlayerCreated(strUUID);
    }
}

void Player::_Publisher::OnPlayerDestroyed(std::string& strUUID)
{
    ICallbacks* pObjToCallback = NULL;
    
    //m_listSubscribersSwap = m_listSubscribers;
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnPlayerDestroyed(strUUID);
    }
}


// Constructor(s)
Player::Player(const std::string& strUUID, B2DWorld* pB2DWorld) :
    m_strUUID(strUUID),
    m_pB2DWorld(pB2DWorld)
{
    assert(m_pB2DWorld);
    
    CreatePod();
    
    Publisher.OnPlayerCreated(m_strUUID);
    
    Input::Publisher.Attach(this);
}

// Destructor(s)
Player::~Player()
{
    Input::Publisher.Detach(this);

    Publisher.OnPlayerDestroyed(m_strUUID);
    
    m_pB2DWorld->world->DestroyBody(m_pb2bPod);
    m_pb2bPod = NULL;
}

void Player::CreatePod()
{
    b2BodyDef       bodyDef;
    b2PolygonShape  dynamicBox;
    b2CircleShape   aB2CircleShape;
    b2FixtureDef    fixtureDef;
    
	// Define the dynamic body. We set its position
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.3f;
    
//    // Define another box shape for our dynamic body.
//	dynamicBox.SetAsBox(4.0f, 4.0f);
//	// Define the dynamic body fixture.
//	fixtureDef.shape = &dynamicBox;

    aB2CircleShape.m_radius = 1.0f;
    fixtureDef.shape = &aB2CircleShape;

    // call the body factory.
    m_pb2bPod = m_pB2DWorld->world->CreateBody(&bodyDef);
	m_pb2bPod->CreateFixture(&fixtureDef);
    
    m_pb2bPod->SetUserData(&m_strUUID);
}

// Method(s)
void Player::Update()
{
    m_b2v2MoveQueue.lock();
    while (!(m_b2v2MoveQueue.empty()))
    {
        b2Vec2 ab2Vec2Move = m_b2v2MoveQueue.pop();
        ab2Vec2Move.x *= 50.0f;
        ab2Vec2Move.y *= 50.0f;
        m_pb2bPod->ApplyForceToCenter(ab2Vec2Move, true);
    }
    m_b2v2MoveQueue.unlock();
}

bool Player::ThisUUIDIsAMatch(const std::string& strUUID)
{
    if (strUUID == m_strUUID)
    {
        return true;
    }
    return false;
}

// Input::ICallbacks implementation
void Player::OnDualStick(const std::string& strUUID, const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot)
{
    if (strUUID != m_strUUID)
    {
        return;
    }
    b2Vec2 b2v2Move;
    b2Vec2 b2v2Shoot;
    
    b2v2Move.x = pbv2Move.x();
    b2v2Move.y = pbv2Move.y();
    b2v2Shoot.x = pbv2Shoot.x();
    b2v2Shoot.y = pbv2Shoot.y();
    
    m_b2v2MoveQueue.lock();
    m_b2v2MoveQueue.push(b2v2Move);
    m_b2v2MoveQueue.unlock();
}
