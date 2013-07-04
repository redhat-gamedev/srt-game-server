//
//  BulletFactory.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-01.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "BulletFactory.h"
#include "Bullet.h"
#include "B2DBullet.h"
#include "B2DBulletFactory.h"
#include <assert.h>


// Method(s)
void BulletFactory::Destroy(Bullet*& pBullet)
{
    assert(pBullet);
    
    B2DBullet* pB2DBullet = (B2DBullet*)pBullet->m_pB2DEntity;
    FactoryT<Bullet, Bullet::_Dependencies>::Destroy(pBullet);    
    B2DBulletFactory::Instance().Destroy(pB2DBullet);
}
