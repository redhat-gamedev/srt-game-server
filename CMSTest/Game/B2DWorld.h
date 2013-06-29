//
//  B2DWorld.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DWorld__
#define __CMSTest__B2DWorld__

#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/timer.h"
#include <string>
#include <list>

namespace xdispatch
{
    class queue;
}

class B2DWorld
{
    friend class AB2DEntity;
    
// Class
public:

    // See B2DWorld_BuildT.h
    template <class T>
    class _BuildT;
    
protected:

public:
    
// Instance
private:
    
protected:
    b2Vec2*         gravity;
        
    float32         timeStep;// = 1.0f / 60.0f;
	int32           velocityIterations;
    int32           positionIterations;
        
    xdispatch::queue*               m_pBox2DSerialDispatchQueue;
    
public:
    static b2World*        world;

    // Constructor(s)
    B2DWorld();
    
    // Destructor
    ~B2DWorld();
    
    // Method(s)
    void Step();
};

#endif /* defined(__CMSTest__B2DWorld__) */