//
//  AB2DEntity.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__AB2DEntity__
#define __CMSTest__AB2DEntity__

#include <Poco/BasicEvent.h>
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <Box2D/Box2D.h>

namespace usx
{
    namespace geofactions
    {
        class EntityGameEventBuffer;
    }
}
class AEntity;


class AB2DEntity
{
    friend class AEntity;
    
protected:
    enum _AB2DCollisionFilterBits
    {
        BOUNDARY =          0x0001,
        POD =               0x0002,
        BULLET =            0x0004,
        FRIENDLY_SHIP =     0x0008,
        ENEMY_SHIP =        0x0010,
        FRIENDLY_AIRCRAFT = 0x0020,
        ENEMY_AIRCRAFT =    0x0040
    };
    
    class _AB2DDefinition
    {
    protected:
        b2BodyDef       m_ab2BodyDef;
        b2FixtureDef    m_ab2FixtureDef;
        void*           m_pUserData;
        b2Body*         m_pb2Body;
        _AB2DCollisionFilterBits   m_eCategoryBits;
        _AB2DCollisionFilterBits   m_eMaskBits;
        
        // Constructor(s)
        _AB2DDefinition();
        
    public:
        // Properties
        b2BodyDef&          BodyDef         = m_ab2BodyDef;
        b2FixtureDef&       FixtureDef      = m_ab2FixtureDef;
        void*&              UserData        = m_pUserData;
        b2Body*&            pBody           = m_pb2Body;
        _AB2DCollisionFilterBits&   eCategoryBits       = m_eCategoryBits;
        _AB2DCollisionFilterBits&   eMaskBits           = m_eMaskBits;
    };
    
    class _Serializer
    {
    public:
        void Serialize(const AB2DEntity* anEntity, usx::geofactions::EntityGameEventBuffer* pEntityGameEvent);
        void Deserialisze(const usx::geofactions::EntityGameEventBuffer* pEntityGameEvent, AB2DEntity*& anEntity);
    };
    
    b2Body*         m_pb2Body;
    b2Fixture*      m_pb2Fixture;
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
    void SetGroupIndex(int16_t i16GroupIndex);
    
    // Method(s)
    virtual void Move(float fX, float fY) {}
    virtual void Update() {}
};



#endif /* defined(__CMSTest__AB2DEntity__) */
