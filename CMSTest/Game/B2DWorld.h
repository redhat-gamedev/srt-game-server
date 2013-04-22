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

    template <class T>
    class _BuildT;
//    {
//    public:
//        static void B2DPod(T* pT, void (T::*pB2DPodCreated)(b2Body* pb2bPod), UserData* pUserData = NULL)
//        {
//            b2BodyDef       bodyDef;
//            b2PolygonShape  dynamicBox;
//            b2CircleShape   aB2CircleShape;
//            b2FixtureDef    fixtureDef;
//            b2Body*         pb2bPod = NULL;
//            
//            // Define the dynamic body. We set its position
//            bodyDef.type = b2_dynamicBody;
//            bodyDef.position.Set(0.0f, 0.0f);
//            
//            // Set the size of our shape
//            aB2CircleShape.m_radius = 1.0f;
//            
//            // Set the fixture and use the shape
//            fixtureDef.density = 1.0f;
//            fixtureDef.friction = 0.3f;
//            fixtureDef.restitution = 0.3f;
//            fixtureDef.filter.groupIndex = -2;
//            fixtureDef.shape = &aB2CircleShape;
//            
//            //UserData* pUserData = new UserData(m_ui64Tag, m_strUUID);
//            
//            // call the body factory.
//            //    m_pb2bPod = World::m_pB2DWorld->world->CreateBody(&bodyDef);
//            //	m_pb2bPod->CreateFixture(&fixtureDef);
//            //    m_pb2bPod->SetUserData(pUserData);
//            
//            pb2bPod = world->CreateBody(&bodyDef);
//            pb2bPod->CreateFixture(&fixtureDef);
//            pb2bPod->SetUserData(pUserData);
//            
//            (pT->* pB2DPodCreated)(pb2bPod);
//        }
//    };
    
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

//template <class T>
//class B2DWorld::_BuildT
//{
//public:
//    static void B2DPod(T* pT, void (T::*pB2DPodCreated)(b2Body* pb2bPod), UserData* pUserData = NULL)
//    {
//        b2BodyDef       bodyDef;
//        b2PolygonShape  dynamicBox;
//        b2CircleShape   aB2CircleShape;
//        b2FixtureDef    fixtureDef;
//        b2Body*         pb2bPod = NULL;
//        
//        // Define the dynamic body. We set its position
//        bodyDef.type = b2_dynamicBody;
//        bodyDef.position.Set(0.0f, 0.0f);
//        
//        // Set the size of our shape
//        aB2CircleShape.m_radius = 1.0f;
//        
//        // Set the fixture and use the shape
//        fixtureDef.density = 1.0f;
//        fixtureDef.friction = 0.3f;
//        fixtureDef.restitution = 0.3f;
//        fixtureDef.filter.groupIndex = -2;
//        fixtureDef.shape = &aB2CircleShape;
//        
//        //UserData* pUserData = new UserData(m_ui64Tag, m_strUUID);
//        
//        // call the body factory.
//        //    m_pb2bPod = World::m_pB2DWorld->world->CreateBody(&bodyDef);
//        //	m_pb2bPod->CreateFixture(&fixtureDef);
//        //    m_pb2bPod->SetUserData(pUserData);
//        
//        pb2bPod = B2DWorld::world->CreateBody(&bodyDef);
//        pb2bPod->CreateFixture(&fixtureDef);
//        pb2bPod->SetUserData(pUserData);
//        
//        (pT->* pB2DPodCreated)(pb2bPod);
//    }
//};



#endif /* defined(__CMSTest__B2DWorld__) */