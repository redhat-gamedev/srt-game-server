//
//  Security.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Security.h"
//#include "../Game/AEntity.h"
#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "../Proto/Command.pb.h"
#include "../Proto/SecurityCommand.pb.h"
#include "../Game/Player.h"
#include "../Game/PodFactory.h"
#include "../Shared/SimpleAsyncConsumer.h"
#include "../Shared/SimpleAsyncProducer.h"
#include "Poco/Delegate.h"
#include <cms/CMSException.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/Destination.h>
#include <cms/TemporaryQueue.h>
#include <decaf/util/UUID.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>

Security::_EventPublisher           Security::EventPublisher;

using namespace cms;
using namespace command;


// Constructor(s)
Security::Security() :
    m_pSimpleAsyncConsumer(NULL),
    m_pSimpleAsyncProducer(NULL)
{
//    bool            useTopics = false;
//    bool            clientAck = false;
    std::string     strSecurityInURI = "AAS.IN";
    std::string     strSecurityOutURI = "AAS.OUT";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";
    PodFactory&  aPodFactory = PodFactory::Instance();
    
    std::cout << "Security::Security()..." << std::endl;
    
    m_pSimpleAsyncConsumer = new SimpleAsyncConsumer(strBrokerURI, strSecurityInURI, false, true);
    m_pSimpleAsyncConsumer->runConsumer();
    m_pSimpleAsyncConsumer->SetMessageListener(this);
    
    m_pSimpleAsyncProducer = new SimpleProducer(strBrokerURI, strSecurityOutURI, true, true);
    
//    Player::EventPublisher.CreatedEvent += Poco::Delegate<Security, const AEntity::EType&>(this, &Security::OnPlayerCreated);
//    Player::EventPublisher.DestroyedEvent += Poco::Delegate<Security, const AEntity::EType&>(this, &Security::OnPlayerDestroyed);
    
    aPodFactory.CreatedEvent += Poco::Delegate<Security, Player*&>(this, &Security::HandlePodCreatedEvent);
    aPodFactory.DestroyedEvent += Poco::Delegate<Security, Player*&>(this, &Security::HandlePodDestroyedEvent);
}

// Destructor
Security::~Security()
{
    PodFactory&  aPodFactory = PodFactory::Instance();
    
//    Player::EventPublisher.DestroyedEvent -= Poco::Delegate<Security, const AEntity::EType&>(this, &Security::OnPlayerDestroyed);
//    Player::EventPublisher.CreatedEvent -= Poco::Delegate<Security, const AEntity::EType&>(this, &Security::OnPlayerCreated);
    
    aPodFactory.DestroyedEvent -= Poco::Delegate<Security, Player*&>(this, &Security::HandlePodDestroyedEvent);
    aPodFactory.CreatedEvent -= Poco::Delegate<Security, Player*&>(this, &Security::HandlePodCreatedEvent);

    m_pSimpleAsyncProducer->close();
    delete m_pSimpleAsyncProducer;
    m_pSimpleAsyncProducer = NULL;
    
    m_pSimpleAsyncConsumer->close();
    delete m_pSimpleAsyncConsumer;
    m_pSimpleAsyncConsumer = NULL;
}

// Event Firing Method(s)
void Security::FireRequestJoinEvent(const std::string& strUUID)
{
    EventPublisher.RequestJoinEvent(this, strUUID);
}

void Security::FireRequestLeaveEvent(const std::string& strUUID)
{
    EventPublisher.RequestLeaveEvent(this, strUUID);
}

void Security::FireHasJoinedEvent(const std::string& strUUID)
{
    EventPublisher.HasJoinedEvent(this, strUUID);
}

void Security::FireHasLeftEvent(const std::string& strUUID)
{
    EventPublisher.HasLeftEvent(this, strUUID);
}

// MessageListener implementation
void Security::onMessage(const Message* pMessage)
{
    assert(pMessage);
    
    static int              count = 0;
//    bool                    clientAck = false;
    Command                 aCommand;
    std::string             strUUID = "";
    std::string             strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    
    try
    {
        count++;
        const BytesMessage* pBytesMessage = dynamic_cast<const BytesMessage*>(pMessage);
        assert(pBytesMessage);

        unsigned char* pucBodyBytes = pBytesMessage->getBodyBytes();
        int iBodyBytes = pBytesMessage->getBodyLength();
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        //if(clientAck)
        //{
        //    pMessage->acknowledge();
        //}
        
        aCommand.ParseFromArray(pucBodyBytes, iBodyBytes);

        assert(Command_CommandType_SECURITY == aCommand.type());
        const SecurityCommand& aSecurityCommand = aCommand.securitycommand();
        if (SecurityCommand_SecurityCommandType_JOIN == aSecurityCommand.type())
        {
            // Join stuff
            // don't forget to ->clone() the reply to destination if lifetime is impt
            const cms::Destination* pDestination = pBytesMessage->getCMSReplyTo();
            assert(pDestination);
            decaf::util::UUID aNewUUID = decaf::util::UUID::randomUUID();
            strUUID = aNewUUID.toString();
            // TODO: Make not super inefficient
            SimpleProducer* pSimpleAsyncProducer = new SimpleProducer(strBrokerURI, pDestination, false, true);
            pSimpleAsyncProducer->Send(strUUID);
            delete pSimpleAsyncProducer;
            
            FireRequestJoinEvent(strUUID);
        }

        if (SecurityCommand_SecurityCommandType_LEAVE == aSecurityCommand.type())
        {
            assert(aSecurityCommand.has_uuid());
            strUUID = aSecurityCommand.uuid();
            
            FireRequestLeaveEvent(strUUID);
        }
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}

// Player Event response
//void Security::OnPlayerCreated(const void* pSender, const AEntity::EType& anEntityType)
void Security::HandlePodCreatedEvent(const void* pSender, Player*& pPlayer)
{
//    assert(strUUID.length() > 0);
    
    std::string strPBBuffer = "";
    
    const AEntity* pEntity = static_cast<const AEntity*>(pPlayer);
    
    Command* pCommand = new Command();
    SecurityCommand* pSecurityCommand = pCommand->mutable_securitycommand();
    assert(NULL != pSecurityCommand);
    
    pCommand->set_type(Command_CommandType_SECURITY);
    //pSecurityCommand->set_uuid(strUUID);
    pSecurityCommand->set_uuid(pEntity->UUID);
    pSecurityCommand->set_type(SecurityCommand_SecurityCommandType_JOIN);
    
    pCommand->SerializeToString(&strPBBuffer);
    const char* pucText = strPBBuffer.c_str();
    unsigned long ulLength = strPBBuffer.length();
    m_pSimpleAsyncProducer->Send((const unsigned char*)pucText, (int)ulLength);
    
    FireHasJoinedEvent(pEntity->UUID);
}

//void Security::OnPlayerDestroyed(const void* pSender, const AEntity::EType& anEntityType)
void Security::HandlePodDestroyedEvent(const void* pSender, Player*& pPlayer)
{
//    assert(strUUID.length() > 0);
    
    std::string strPBBuffer = "";
    
    const AEntity* pEntity = static_cast<const AEntity*>(pPlayer);
    
    Command* pCommand = new Command();
    SecurityCommand* pSecurityCommand = pCommand->mutable_securitycommand();
    assert(NULL != pSecurityCommand);
    
    pCommand->set_type(Command_CommandType_SECURITY);
    //pSecurityCommand->set_uuid(strUUID);
    pSecurityCommand->set_uuid(pEntity->UUID);
    pSecurityCommand->set_type(SecurityCommand_SecurityCommandType_LEAVE);
    
    pCommand->SerializeToString(&strPBBuffer);
    const char* pucText = strPBBuffer.c_str();
    unsigned long ulLength = strPBBuffer.length();
    m_pSimpleAsyncProducer->Send((const unsigned char*)pucText, (int)ulLength);
    
    FireHasLeftEvent(pEntity->UUID);
}

// cms::AsyncCallback implementation
void Security::onSuccess()
{
    //delete m_pSimpleAsyncProducer;
    //m_pSimpleAsyncProducer = NULL;
}

void Security::onException(const cms::CMSException& aCMSException)
{
    //delete m_pSimpleAsyncProducer;
    //m_pSimpleAsyncProducer = NULL;
}