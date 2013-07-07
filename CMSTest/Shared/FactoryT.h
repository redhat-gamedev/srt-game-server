//
//  FactoryT.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-01.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_FactoryT_h
#define CMSTest_FactoryT_h

#include "Poco/BasicEvent.h"
#include <limits>

template <class T, class D>
class FactoryT
{
private:
    
protected:
    // Constructor(s)
    FactoryT<T, D>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<T, D>() {};
    
public:
    // Event(s)
    Poco::BasicEvent<T*&>    CreatedEvent;
    Poco::BasicEvent<T*&>    DestroyedEvent;
    
    // Singleton
    static FactoryT<T, D>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<T, D>  aTFactory;
        return aTFactory;
    }
    
    // Method(s)
    virtual T* Create(D& aD)
    {
        T* pT = NULL;
        pT = new T(aD);
        
        CreatedEvent(this, pT);
        return pT;
    }
    
    virtual void Destroy(T*& pT)
    {
        DestroyedEvent(this, pT);
        delete pT;
        pT = NULL;
    }
};

#endif
