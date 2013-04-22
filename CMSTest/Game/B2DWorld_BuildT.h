//
//  B2DWorld_BuildT.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-21.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_B2DWorld_BuildT_h
#define CMSTest_B2DWorld_BuildT_h

//#include "UserData.h"
#include "B2DWorld.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"


class UserData;


template <class T>
class B2DWorld::_BuildT
{
public:
    static void B2DPod(T* pT, void (T::*pB2DPodCreated)(b2Body* pb2bPod), UserData* pUserData = NULL)
    {
        b2BodyDef       bodyDef;
        b2PolygonShape  dynamicBox;
        b2CircleShape   aB2CircleShape;
        b2FixtureDef    fixtureDef;
        b2Body*         pb2bPod = NULL;
        
        // Define the dynamic body. We set its position
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 0.0f);
        
        // Set the size of our shape
        aB2CircleShape.m_radius = 1.0f;
        
        // Set the fixture and use the shape
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.3f;
        fixtureDef.filter.groupIndex = -2;
        fixtureDef.shape = &aB2CircleShape;
        
        //UserData* pUserData = new UserData(m_ui64Tag, m_strUUID);
        
        // call the body factory.
        //    m_pb2bPod = World::m_pB2DWorld->world->CreateBody(&bodyDef);
        //	m_pb2bPod->CreateFixture(&fixtureDef);
        //    m_pb2bPod->SetUserData(pUserData);
        
        pb2bPod = B2DWorld::world->CreateBody(&bodyDef);
        pb2bPod->CreateFixture(&fixtureDef);
        pb2bPod->SetUserData(pUserData);
        
        (pT->* pB2DPodCreated)(pb2bPod);
    }
};


#endif
