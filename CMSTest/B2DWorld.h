//
//  B2DWorld.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DWorld__
#define __CMSTest__B2DWorld__

#include "box2d.pb.h"
#include "Input.h"
#include "../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "decaf/lang/Runnable.h"
#include "decaf/util/StlQueue.h"
//#include "../../Libraries/Phoenix/source/PublisherT.cpp"
#include "PublisherT.cpp"
#include <string>
#include <list>


// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
class B2DWorld :
    public decaf::lang::Runnable,
    public Input::ICallbacks
{
// Class
public:
    class ICallbacks
    {
    public:
        virtual void OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle) {};
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
        virtual void OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle);
        virtual void OnB2DWorldBodyUpdate(b2Body* pBody);
    };

public:
    static _Publisher               Publisher;
    
private:
    
// Instance
private:
    
protected:
    b2World*        world;
    b2Vec2*         gravity;
    b2BodyDef       groundBodyDef;
    b2Body*         groundBody;
    b2BodyDef       bodyDef;
    b2Body*         body;
    b2Vec2          position;
    float32         angle;
    
    b2PolygonShape  groundBox;
    b2PolygonShape  dynamicBox;
    b2FixtureDef    fixtureDef;
    
    float32         timeStep;// = 1.0f / 60.0f;
	int32           velocityIterations;
    int32           positionIterations;
    
    char            m_szBuf[0xff];
    
    decaf::util::StlQueue<b2Vec2>       m_b2v2MoveQueue;
    decaf::util::StlQueue<b2Vec2>       m_b2v2MoveSwapQueue;
    
public:
    // Constructor(s)
    B2DWorld();
    
    // Destructor
    ~B2DWorld();
    
    // Method(s)
    void CreateBodiesAndShapes();
    void Update(std::string& strText);
    void CreatePod();

    // decaf::lang::Runnable implementation
    void run();
    
    // Input::ICallbacks implementation
    virtual void OnDualStick(const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot);
};


#endif /* defined(__CMSTest__B2DWorld__) */