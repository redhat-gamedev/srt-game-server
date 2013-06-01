//
//  Messenger_Consumer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger_Consumer.h"
#include "../Shared/SimpleAsyncConsumer.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include "EntityData.h"
#include <cms/CMSException.h>
#include <cms/BytesMessage.h>
#include <assert.h>

Messenger::_Consumer::_EventPublisher           Messenger::_Consumer::EventPublisher;

using namespace cms;
using namespace gameevent;


// Constructor(s)
Messenger::_Consumer::_Consumer():
    m_pSimpleAsyncConsumer(NULL)
{

}

// Destructor(s)
Messenger::_Consumer::~_Consumer()
{

}

// Helper(s)
void Messenger::_Consumer::Setup(std::string& strBrokerURI, std::string& strDestinationURI)
{
    bool            useTopics = false;
    bool            clientAck = false;
    
    std::cout << "Messenger::_Consumer::Setup()..." << std::endl;
    
    m_pSimpleAsyncConsumer = new SimpleAsyncConsumer(strBrokerURI, strDestinationURI, useTopics, clientAck);
    m_pSimpleAsyncConsumer->runConsumer();
    m_pSimpleAsyncConsumer->SetMessageListener(this);
}

void Messenger::_Consumer::Teardown()
{
    m_pSimpleAsyncConsumer->close();
    delete m_pSimpleAsyncConsumer;
    m_pSimpleAsyncConsumer = NULL;    
}

// MessageListener implementation
void Messenger::_Consumer::onMessage(const cms::Message* pMessage)
{
    assert(pMessage);
    
    static int count = 0;

    //bool            clientAck = false;
    std::string     strNMSXGroupIDPropertyName = "NMSXGroupID";
    std::string     strNMSXGroupID = "";
    //std::string     strUUID = "";
    //uint64_t        ui64Tag = 0;
    GameEvent       aGameEvent;
    //EntityData      anEntityData;
    
    
    try
    {
        count++;
        const BytesMessage* pBytesMessage = dynamic_cast<const BytesMessage*>(pMessage);
        assert(pBytesMessage);
        
        unsigned char* pucBodyBytes = pBytesMessage->getBodyBytes();
        int iBodyBytes = pBytesMessage->getBodyLength();
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        if (aGameEvent.ParseFromArray(pucBodyBytes, iBodyBytes))
        {
            switch (aGameEvent.type())
            {
                case GameEvent_GameEventType_ENTITY:
                    const EntityGameEvent& anEntityGameEvent = aGameEvent.entitygameevent();
                    switch (anEntityGameEvent.type())
                    {
                        case EntityGameEvent_EntityGameEventType_CREATE:
                            EventPublisher.ReceivedCreateEntityRequest(                                                                       this,
                                EntityData(anEntityGameEvent.entitytag(), anEntityGameEvent.uuid()));
                            break;
                        case EntityGameEvent_EntityGameEventType_DESTROY:
                            EventPublisher.ReceivedDestroyEntityRequest(
                                this,
                                EntityData(anEntityGameEvent.entitytag(), anEntityGameEvent.uuid()));
                            break;
                        default:
                            assert(false);
                            break;
                    }
                    break;
//                default:
//                    assert(false);
//                    break;
            }
        }
        
        
        
        //aDualStick.ParseFromArray(pucBodyBytes, iBodyBytes);
        
        if (pBytesMessage->propertyExists(strNMSXGroupIDPropertyName))
        {
            strNMSXGroupID = pBytesMessage->getStringProperty(strNMSXGroupIDPropertyName);
        }
        
        //if(clientAck)
        //{
        //    pMessage->acknowledge();
        //}
        
        //FireDualStickEvent(aDualStick);
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
    
}