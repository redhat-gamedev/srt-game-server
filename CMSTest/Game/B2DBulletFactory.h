//
//  B2DBulletFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-01.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_B2DBulletFactory_h
#define CMSTest_B2DBulletFactory_h

#include "B2DBullet.h"
#include "B2DWorld.h"
#include "../Shared/FactoryT.h"


class B2DBulletFactory :
    public FactoryT<B2DBullet, B2DBullet::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    B2DBulletFactory() {};
    
    // Destructor(s)
    ~B2DBulletFactory() {};
    
public:
    // Singleton
    static B2DBulletFactory& Instance()//unsigned int uiCapacity)
    {
        static B2DBulletFactory  aB2DBulletFactory;
        return aB2DBulletFactory;
    }
};



#endif
