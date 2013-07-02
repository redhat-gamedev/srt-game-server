//
//  BulletFactory.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-01.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

//#include "BulletFactory.h"
//#include "Bullet.h"
//#include "B2DBullet.h"


// Constructor(s)
//Bullet::_Factory::_Factory()
//{
//}

// Destructor(s)
//Bullet::_Factory::~_Factory()
//{
//}

//Bullet* BulletFactory::Create(const std::string& strParentUUID, const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity)
//{
//    B2DBullet::_B2DDefinition       aB2DBulletDefinition(b2v2GunPosition, b2v2GunVelocity);
//    B2DBullet* pB2DBullet = B2DBullet::Factory().Create(aB2DBulletDefinition);
//    Bullet* pBullet = new Bullet(strParentUUID, pB2DBullet);
//    pB2DBullet->SetParentEntity(pBullet);
//    CreatedEvent(this, pBullet);
//    
//    return pBullet;
//}
//
//void BulletFactory::Destroy(Bullet*& pBullet)
//{
//    assert(pBullet);
//    
//    B2DBullet* pB2DBullet = (B2DBullet*)pBullet->m_pB2DEntity;
//    B2DBullet::Factory().Destroy(pB2DBullet);
//    
//    DestroyedEvent(this, pBullet);
//    delete pBullet;
//    pBullet = NULL;
//}

