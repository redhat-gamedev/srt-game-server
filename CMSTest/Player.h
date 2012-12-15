//
//  Player.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Player__
#define __CMSTest__Player__

#include "PublisherT.cpp"
#include <string>

class B2DWorld;


class Player
{
public:
    class ICallbacks
    {
    public:
        virtual void OnPlayerCreated(std::string& strUUID) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnPlayerCreated(std::string& strUUID);
    };
private:
    
protected:
    std::string     m_strUUID;
    
public:
    static _Publisher               Publisher;
    
    // Constructor(s)
    Player(std::string& strUUID, B2DWorld* pB2DWorld);
    
    // Destructor(s)
    ~Player();
};


#endif /* defined(__CMSTest__Player__) */
