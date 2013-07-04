//
//  PodFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-03.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_PodFactory_h
#define CMSTest_PodFactory_h

#include "Player.h"
#include "../Shared/FactoryT.h"


class PodFactory :
    public FactoryT<Player, Player::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    PodFactory() {};
    
    // Destructor(s)
    ~PodFactory() {};
    
public:
    // Singleton
    static PodFactory& Instance()//unsigned int uiCapacity)
    {
        static PodFactory  aPodFactory;
        return aPodFactory;
    }
    
    // Method(s)
    void Destroy(Player*& pPod);
};

#endif
