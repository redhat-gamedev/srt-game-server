//
//  Bullet.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Bullet__
#define __CMSTest__Bullet__

#include "AEntity.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <decaf/util/StlQueue.h>
#include <string>

namespace Rock2D
{
    class Timer;
}
class B2DBullet;


class Bullet :
    public AEntity
{
    friend class Player;
//    friend class B2DBullet;
    
private:
    static uint32_t         s_ui32Count;
    
protected:
    bool                    m_bAlive;
    Rock2D::Timer*          m_pLifeTimer;
    
    class _Factory :
        public AEntity::_Factory
    {
        friend class Bullet;
        
    protected:
        // Constructor(s)
        _Factory();
        
        // Destructor(s)
        ~_Factory();

    public:
        Poco::BasicEvent<Bullet*&>    CreatedEvent;
        Poco::BasicEvent<Bullet*&>    DestroyedEvent;
    
        virtual Bullet* Create(const std::string& strParentUUID, const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity);
        virtual void Destroy(Bullet*& pBullet);
        
        // Event response
//        void HandleB2DBulletCreatedEvent(const void* pSender, B2DBullet*& pB2DBullet);
//        void HandleB2DBulletDestroyedEvent(const void* pSender, B2DBullet*& pB2DBullet);
    };
    
public:
    static _EventPublisher          EventPublisher;

    // Singleton
    static _Factory& Factory()
    {
        static _Factory aFactory;
        return aFactory;
    }
    
    // Constructor(s)
    Bullet(const std::string& strParentUUID, B2DBullet* pB2DBullet);
    
    // Destructor(s)
    ~Bullet();
    
    // Method(s)
    const bool Alive() { return m_bAlive; }
    void Fire(b2Vec2& b2v2FiringDirection);

    // Override(s)
    void Update();
};

#endif /* defined(__CMSTest__Bullet__) */
