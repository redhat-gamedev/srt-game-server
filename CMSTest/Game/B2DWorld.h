//
//  B2DWorld.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DWorld__
#define __CMSTest__B2DWorld__

#include "../Shared/PublisherT.cpp"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <string>
#include <list>

//class Player;
class UserData;


class B2DWorld
{
// Class
public:
    class ICallbacks
    {
    public:
        virtual void OnB2DWorldUpdate(b2World* pWorld) {};
        virtual void OnB2DWorldBodyUpdate(b2Body* pBody) {};
    };

    // See B2DWorld_BuildT.h
    template <class T>
    class _BuildT;
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnB2DWorldUpdate(b2World* pWorld);
        virtual void OnB2DWorldBodyUpdate(b2Body* pBody);
    };

public:
    static _Publisher               Publisher;
    //static xdispatch::synclock      aSyncLock;
    //static xdispatch::synclock*     s_pSyncLock;
    

private:
    
// Instance
private:
    
protected:
    //b2World*        world;
    b2Vec2*         gravity;
        
    float32         timeStep;// = 1.0f / 60.0f;
	int32           velocityIterations;
    int32           positionIterations;
    
public:
    static b2World*        world;
    
    // Constructor(s)
    B2DWorld();
    
    // Destructor
    ~B2DWorld();
    
    // Method(s)

    // decaf::lang::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__B2DWorld__) */