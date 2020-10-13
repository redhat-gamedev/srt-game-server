#ifndef CMSTest_FactoryT_h
#define CMSTest_FactoryT_h

//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

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
