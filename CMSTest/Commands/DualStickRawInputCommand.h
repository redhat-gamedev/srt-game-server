//
//  DualStickRawInputCommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__DualStickRawInputCommand__
#define __CMSTest__DualStickRawInputCommand__

#include "RawInputCommand.h"
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <Box2D/Box2D.h>
#include <Poco/BasicEvent.h>
#include <string>


class DualStickRawInputCommand :
    public RawInputCommand
{
private:
protected:
public:
    b2Vec2          m_b2v2Move;
    b2Vec2          m_b2v2Shoot;
    
    // Event(s)
    Poco::BasicEvent<const std::string&>      ExecutedEvent;
    //Poco::BasicEvent<const std::string&, b2Vec2& b2v2Move, b2Vec2& b2v2Shoot>      ExecutedEvent;
    
    // Constructor
    DualStickRawInputCommand(_RawInputDependencies& theDependencies);
    
    // Destructor
    ~DualStickRawInputCommand();
    
    // Method(s)
    virtual void Execute();
};


#endif /* defined(__CMSTest__DualStickRawInputCommand__) */
