//
//  B2DWorld.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DWorld__
#define __CMSTest__B2DWorld__

//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <Box2D/Box2D.h>
//#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
//#include "../../../ThirdParty/xdispatch/include/xdispatch/timer.h"
#include <Poco/Mutex.h>
#include <string>
#include <list>

namespace xdispatch
{
    class queue;
}

class B2DWorld
{
    friend class AB2DEntity;
    
// Class
protected:
    static Poco::Mutex      s_aMutex;

public:
    static b2World*        s_pb2World;
    
    
// Instance
private:
    
protected:
    class _Factory
    {
        friend class B2DWorld;
        
    protected:
        // Constructor(s)
        _Factory() {};
        
        // Destructor(s)
        ~_Factory() {};

    public:
        b2Body* CreateBody(const b2BodyDef* pb2BodyDef);
        void DestroyBody(b2Body* pb2Body);
        
        b2Joint* CreateJoint(const b2JointDef* pb2JointDef);
        void DestroyJoint(b2Joint* pb2Joint);
    };
    
    b2Vec2*         gravity;
        
    float32         timeStep;// = 1.0f / 60.0f;
	int32           velocityIterations;
    int32           positionIterations;
    
    //xdispatch::queue*               m_pBox2DSerialDispatchQueue;

    // Constructor(s)
    B2DWorld();
    
    // Destructor
    ~B2DWorld();

public:
    // Singleton(s)
    static _Factory& Factory()
    {
        static _Factory aFactory;
        return aFactory;
    }
    
    static B2DWorld& Instance()
    {
        static B2DWorld aB2DWorld;
        return aB2DWorld;
    }

    // Method(s)
    void Step();
};

#endif /* defined(__CMSTest__B2DWorld__) */
