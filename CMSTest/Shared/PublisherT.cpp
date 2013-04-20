/*
 *  Publisher.cpp
 *  Phoenix
 *
 *  Created by Roddie Kieley on 10-01-22.
 *  Copyright 2010 Binary Dawn Interactive Inc.. All rights reserved.
 *
 */

#pragma once

#include "PublisherT.h"
#include <algorithm>
#include <assert.h>


// Constructor(s)
template <class T>
PublisherT<T*>::PublisherT()
{
}

// Destructor
template <class T>
PublisherT<T*>::~PublisherT()
{
}

// Helper(s)
template <class T>
void PublisherT<T*>::Clone(std::list<T*>& listToCloneInto)
{
    mutex.lock();
    listToCloneInto = m_listSubscribers;
    mutex.unlock();
}

// Method(s)
template <class T>
void PublisherT<T*>::Attach(T* pSubscriber, bool bBeforeExisting)
{
	assert(pSubscriber);
	assert(find(m_listSubscribers.begin(), m_listSubscribers.end(), pSubscriber) == m_listSubscribers.end());
	
	if (bBeforeExisting)
	{
        mutex.lock();
		m_listSubscribers.push_front(pSubscriber);
        mutex.unlock();
	}
	else
	{
        mutex.lock();
		m_listSubscribers.push_back(pSubscriber);
        mutex.unlock();
	}
}

template <class T>
void PublisherT<T*>::Detach(T* pSubscriber)
{
	assert(pSubscriber);
	
    mutex.lock();
	m_listSubscribers.remove(pSubscriber);
    mutex.unlock();
}

template <class T>
bool PublisherT<T*>::IsAttached(T* pSubscriber)
{
	return (find(m_listSubscribers.begin(), m_listSubscribers.end(), pSubscriber) != m_listSubscribers.end());
}
