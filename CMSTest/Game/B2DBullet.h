//
//  B2DBullet.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DBullet__
#define __CMSTest__B2DBullet__

#include "AB2DEntity.h"
#include "Poco/BasicEvent.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"

class AEntity;


class B2DBullet :
    public AB2DEntity
{
public:
    class _Dependencies :
        public AB2DEntity::_AB2DDefinition
    {
    protected:
        const b2Vec2&           m_b2v2GunPosition;
        const b2Vec2&           m_b2v2GunVelocity;
        b2CircleShape           m_b2CircleShape;
        
    public:
        // Constructor
        _Dependencies(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity);
        
        // Destructor()
        ~_Dependencies() {};
    };
    
private:
    
protected:
    
public:
    class _B2DDefinition :
        public AB2DEntity::_AB2DDefinition
    {
        friend class B2DBullet;
        
    protected:
        b2CircleShape       m_ab2CircleShape;
        
    public:
        // Constructor(s)
        _B2DDefinition();
        _B2DDefinition(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, void* pUserData = NULL);
    };
    
protected:    
    class _Factory :
        public AB2DEntity::_Factory
    {
        friend class B2DBullet;
        
    protected:
        // Constructor(s)
        _Factory() {};
        
        // Destructor(s)
        ~_Factory() {};
        
    public:
        virtual B2DBullet* Create(const _B2DDefinition& aB2DDefinition);
        virtual void Destroy(B2DBullet* pB2DBullet);
        
        Poco::BasicEvent<B2DBullet*&>    CreatedEvent;
        Poco::BasicEvent<B2DBullet*&>    DestroyedEvent;
    };

    b2Vec2              m_b2v2InitialPosition;
    b2Vec2              m_b2v2InitialVelocity;

    // Helper(s)

    // Constructor(s)
    B2DBullet(b2Body* pb2Body);
//    B2DBullet(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, b2Vec2& b2v2FiringDirection, AEntity* pBullet);
    
public:
    // Constructor(s)
    B2DBullet(_Dependencies& theDependencies);

    // Destructor(s)
    ~B2DBullet();

    // Singleton
    static _Factory& Factory()
    {
        static _Factory aFactory;
        return aFactory;
    }
    
    // Method(s)
    void Fire(b2Vec2& b2v2FiringDirection);

    // Callback(s)
};


#endif /* defined(__CMSTest__B2DBullet__) */
