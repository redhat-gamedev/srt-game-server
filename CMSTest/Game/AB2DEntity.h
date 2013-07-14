//
//  AB2DEntity.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__AB2DEntity__
#define __CMSTest__AB2DEntity__

#include "Poco/BasicEvent.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"

namespace GameEventBuffers
{
    class EntityGameEventBuffer;
}
class AEntity;


class AB2DEntity
{
    friend class AEntity;
    
protected:
    class _AB2DDefinition
    {
    protected:
        b2BodyDef       m_ab2BodyDef;
        b2FixtureDef    m_ab2FixtureDef;
        void*           m_pUserData;
        b2Body*         m_pb2Body;
        
        // Constructor(s)
        _AB2DDefinition();
        
    public:
        // Properties
        b2BodyDef&          BodyDef         = m_ab2BodyDef;
        b2FixtureDef&       FixtureDef      = m_ab2FixtureDef;
        void*&              UserData        = m_pUserData;
        b2Body*&            pBody           = m_pb2Body;
    };
    
    class _Serializer
    {
    public:
        void Serialize(const AB2DEntity* anEntity, GameEventBuffers::EntityGameEventBuffer* pEntityGameEvent);
        void Deserialisze(const GameEventBuffers::EntityGameEventBuffer* pEntityGameEvent, AB2DEntity*& anEntity);
    };
    
    b2Body*         m_pb2Body;
    AEntity*        m_pParentEntity;
    
    // Constructor(s)
    AB2DEntity();
    AB2DEntity(b2Body* pb2Body);
    AB2DEntity(const _AB2DDefinition& aAB2DDefinition, AEntity* pEntity);
    
    // Destructor
    virtual ~AB2DEntity();
    
public:
    static _Serializer          Serializer;
    
    // Accessor(s)
    const b2Vec2& GetPosition() { return m_pb2Body->GetPosition(); }
    const b2Vec2& GetLinearVelocity() { return m_pb2Body->GetLinearVelocity(); }
    AEntity* GetParentEntity() { return m_pParentEntity; }
    void SetParentEntity(AEntity* pParentEntity);
    
    // Method(s)
    virtual void Move(float fX, float fY) {}
    virtual void Update() {}
};



#endif /* defined(__CMSTest__AB2DEntity__) */
