//
//  BulletFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-01.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Bullet_Factory__
#define __CMSTest__Bullet_Factory__

#include "Bullet.h"
#include "../Shared/FactoryT.h"


class BulletFactory :
    public FactoryT<Bullet, Bullet::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    BulletFactory() {};
    
    // Destructor(s)
    ~BulletFactory() {};
    
public:
    // Singleton
    static BulletFactory& Instance()//unsigned int uiCapacity)
    {
        static BulletFactory  aBulletFactory;
        return aBulletFactory;
    }
};

#endif /* defined(__CMSTest__Bullet_Factory__) */