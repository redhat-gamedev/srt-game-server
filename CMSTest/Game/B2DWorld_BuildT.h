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

    static void B2DBodyDestroy(T* pT, void (T::*pOnB2DBodyDestroyed)(), b2Body* pb2Body)
    {
        assert(pb2Body);
        
        xdispatch::queue("simulation").sync([=]
        {
            B2DWorld::world->DestroyBody(pb2Body);
            
            (pT->* pOnB2DBodyDestroyed)();
        });
    }    
};
#endif
