//
//  Player.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Player.h"
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

// Constructor(s)
Player::Player(std::string& strUUID, B2DWorld* pB2DWorld) :
    m_strUUID(strUUID)
{
    assert(pB2DWorld);
    
    pB2DWorld->CreatePod();
    
    Publisher.OnPlayerCreated(m_strUUID);
}

// Destructor(s)
Player::~Player()
{
    
}

