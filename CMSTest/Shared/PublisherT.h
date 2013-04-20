/*
 *  Publisher.h
 *  Phoenix
 *
 *  Created by Roddie Kieley on 10-01-22.
 *  Copyright 2010 Binary Dawn Interactive Inc.. All rights reserved.
 *
 */

#pragma once

#include <list>
#include "decaf/util/concurrent/Mutex.h"


template <class T>
class PublisherT;

template <class T>
class PublisherT<T*>
{
private:
	
protected:
	// Constructor(s)
	PublisherT();

	std::list<T*>		m_listSubscribers;

    // Object used for sync
    mutable decaf::util::concurrent::Mutex     mutex;
    
    // Helper(s)
    void Clone(std::list<T*>& listToCloneInto);
    
public:
	
	// Destructor
	virtual ~PublisherT();
	
	// Method(s)
	virtual void Attach(T* pSubscriber, bool bBeforeExisting = true);
	virtual void Detach(T* pSubscriber);
	virtual bool IsAttached(T* pSubscriber);
};

