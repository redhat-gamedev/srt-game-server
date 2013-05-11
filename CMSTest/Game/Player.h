//
//  Player.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Player__
#define __CMSTest__Player__

#include "Input.h"
#include "AEntity.h"
#include "../Shared/PublisherT.cpp"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <decaf/util/StlQueue.h>
#include <string>

struct b2BodyDef;
struct b2FixtureDef;
//class B2DWorld;
class b2Body;
class b2PolygonShape;
namespace Rock2D
{
    class Timer;
}


class Player :
    public AEntity,
    public Input::ICallbacks
{
public:
    class ICallbacks
    {
    public:
        virtual void OnPlayerCreated(const std::string& strUUID) {};
        virtual void OnPlayerDestroyed(const std::string& strUUID) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnPlayerCreated(const std::string& strUUID);
        virtual void OnPlayerDestroyed(const std::string& strUUID);
    };
private:
    static uint32_t         s_ui32Count;
    
protected:
    b2Body*         m_pb2bPod;

    Rock2D::Timer*          m_pBulletTimer;
    
    decaf::util::StlQueue<b2Vec2>       m_b2v2MoveQueue;
    decaf::util::StlQueue<b2Vec2>       m_b2v2MoveSwapQueue;

    decaf::util::StlQueue<b2Vec2>       m_b2v2ShootQueue;
    decaf::util::StlQueue<b2Vec2>       m_b2v2ShootSwapQueue;

    // Helper(s)
    void CreatePod();

public:
    static _Publisher               Publisher;
    
    // Constructor(s)
    Player(const std::string& strUUID);
    
    // Destructor(s)
    ~Player();
    
    // Method(s)
    void Update();
//    bool ThisUUIDIsAMatch(const std::string& strUUID);
    
    // Callback(s)
    void ReceivePod(b2Body* pb2bPod);
    
    // Input::ICallbacks implementation
    virtual void OnDualStick(const std::string& strUUID, const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot);
};


#endif /* defined(__CMSTest__Player__) */
