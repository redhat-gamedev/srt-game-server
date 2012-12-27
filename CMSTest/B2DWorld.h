//
//  B2DWorld.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DWorld__
#define __CMSTest__B2DWorld__

#include "../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "decaf/lang/Runnable.h"
#include "decaf/util/StlQueue.h"
//#include "../../Libraries/Phoenix/source/PublisherT.cpp"
#include "PublisherT.cpp"
#include <string>
#include <list>

class Player;


// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
class B2DWorld :
    public decaf::lang::Runnable
{
// Class
public:
    class ICallbacks
    {
    public:
        //virtual void OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle) {};
        virtual void OnB2DWorldUpdate(b2World* pWorld) {};
        virtual void OnB2DWorldBodyUpdate(b2Body* pBody) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        //virtual void OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle);
        virtual void OnB2DWorldUpdate(b2World* pWorld);
        virtual void OnB2DWorldBodyUpdate(b2Body* pBody);
    };

public:
    static _Publisher               Publisher;
    
private:
    
// Instance
private:
    
protected:
    //b2World*        world;
    b2Vec2*         gravity;
        
    float32         timeStep;// = 1.0f / 60.0f;
	int32           velocityIterations;
    int32           positionIterations;
    
    char            m_szBuf[0xff];
    
    std::list<Player*>              m_listPlayers;
    std::list<Player*>              m_listPlayersSwap;
    
public:
    b2World*        world;
    
    // Constructor(s)
    B2DWorld();
    
    // Destructor
    ~B2DWorld();
    
    // Method(s)
    void AddPlayer(const std::string& strUUID);

    // decaf::lang::Runnable implementation
    void run();
};


#endif /* defined(__CMSTest__B2DWorld__) */