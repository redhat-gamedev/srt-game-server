//
//  Addressbook.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Addressbook.h"
#include "addressbook.pb.h"
#include <stdio.h>
#include <assert.h>

Addressbook::_Publisher                 Addressbook::Publisher;
tutorial::Person* person = NULL;
tutorial::Person::PhoneNumber* phone_number = NULL;
tutorial::AddressBook address_book;

// Constructor(s)
/*
 B2DWorld.h::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 B2DWorld.h::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void Addressbook::_Publisher::OnPerson(tutorial::Person* person)
{
    assert(person);
    
    ICallbacks* pObjToCallback = NULL;
    
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        //pObjToCallback->OnAddress(iBeat);
        pObjToCallback->OnPerson(person);
    }
}

// Constructor(s)
Addressbook::Addressbook()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
}

// Destructor(s)
Addressbook::~Addressbook()
{
    int i = 0;
    ++i;
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
}

// Method(s)
void Addressbook::run()
{
    static int iBeat = 0;

    char szName[0xff] = {0};
    char szEmail[0xff] = {0};
    char szPhone[0xff] = {0};
    
    sprintf(szName, "%iID PersonName", iBeat);
    sprintf(szEmail, "someone%i@binarydawn.com", iBeat);
    sprintf(szPhone, "%09i", iBeat);
    
    person = address_book.add_person();
    person->set_id(iBeat);
    person->set_name(szName);
    person->set_email(szEmail);
    phone_number = person->add_phone();
    phone_number->set_number(szPhone);
    phone_number->set_type(tutorial::Person::MOBILE);
    
    //Publisher.OnAddress(iBeat);
    Publisher.OnPerson(person);
    ++iBeat;
}
