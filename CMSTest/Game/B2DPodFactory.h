//
//  B2DPodFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-03.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_B2DPodFactory_h
#define CMSTest_B2DPodFactory_h

#include "B2DPod.h"
#include "B2DWorld.h"
#include "../Shared/FactoryT.h"


class B2DPodFactory :
    public FactoryT<B2DPod, B2DPod::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    B2DPodFactory() {};
    
    // Destructor(s)
    ~B2DPodFactory() {};
    
public:
    // Singleton
    static B2DPodFactory& Instance()//unsigned int uiCapacity)
    {
        static B2DPodFactory  aB2DPodFactory;
        return aB2DPodFactory;
    }
};


#endif
