//
//  B2DWorld_BuildT.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-21.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_B2DWorld_BuildT_h
#define CMSTest_B2DWorld_BuildT_h

#include "B2DWorld.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
//#include "../../../ThirdParty/xdispatch/include/xdispatch/synchronized.h"


template <class T>
class B2DWorld::_BuildT
{
public:
    static void B2DBody(T* pT, void (T::*pOnB2DBodyCreated)(b2Body* pb2Body), const b2BodyDef& ab2BodyDef, const b2FixtureDef& ab2FixtureDef)
    {
        xdispatch::queue("simulation").sync([=]
        {
            // call the body factory.
            b2Body* pb2Body = B2DWorld::world->CreateBody(&ab2BodyDef);
            pb2Body->CreateFixture(&ab2FixtureDef);
            
            (pT->* pOnB2DBodyCreated)(pb2Body);
        });
    }
    
    static void B2DPod(T* pT, void (T::*pB2DReceivePod)(b2Body* pb2bPod))
    {
        b2BodyDef           bodyDef;
        b2PolygonShape      dynamicBox;
        b2CircleShape       aB2CircleShape;
        b2FixtureDef        fixtureDef;
        
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
            
        xdispatch::queue("simulation").sync([=]
        {
            // call the body factory.
            b2Body* pb2bPod = B2DWorld::world->CreateBody(&bodyDef);
            pb2bPod->CreateFixture(&fixtureDef);
            
            (pT->* pB2DReceivePod)(pb2bPod);
        });
    }
    
    static void B2DBullet(T* pT, void (T::*pOnB2DBulletCompleted)(b2Body* pb2bBullet), const b2Vec2& b2v2Position, b2Vec2& b2v2Direction)
    {
        b2BodyDef           bodyDef;
        b2CircleShape       aB2CircleShape;
        b2FixtureDef        fixtureDef;
    
        // Define the dynamic body. We set its position
        bodyDef.type = b2_dynamicBody;
        bodyDef.bullet = true;
        bodyDef.allowSleep = false;
        bodyDef.position.Set(b2v2Position.x, b2v2Position.y);
        
        // Set the size of our shape
        aB2CircleShape.m_radius = 0.25f;
        
        // Set the fixture and use the shape
        fixtureDef.density = 0.1f;
        fixtureDef.friction = 0.1f;
        fixtureDef.restitution = 0.1f;
        fixtureDef.filter.groupIndex = -2;
        fixtureDef.shape = &aB2CircleShape;

        b2Vec2 b2v2Force = b2v2Direction;
        b2v2Force.x *= 10.0f;
        b2v2Force.y *= 10.0f;

        xdispatch::queue("simulation").sync([=]
        {
            // call the body factory.
            b2Body* pb2bBullet = B2DWorld::world->CreateBody(&bodyDef);
            pb2bBullet->CreateFixture(&fixtureDef);
            pb2bBullet->ApplyForceToCenter(b2v2Force, false);

            (pT->* pOnB2DBulletCompleted)(pb2bBullet);
        });
    }
};
#endif
