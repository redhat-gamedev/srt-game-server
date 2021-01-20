#include "ProtonConsumer.h"
#include <proton/connection.hpp>
#include <proton/connection_options.hpp>
#include <proton/container.hpp>
#include <proton/delivery.hpp>
#include <proton/link.hpp>
#include <proton/message.hpp>
#include <proton/message_id.hpp>
#include <proton/messaging_handler.hpp>
#include <proton/value.hpp>

#include <iostream>
#include <map>

#include "../Shared/fake_cpp11.hpp"

#include "../Logging/loguru.hpp"

// constructor
ProtonConsumer::ProtonConsumer(const std::string &s) :
  url(s) {
    LOG_F(INFO, "Constructor");
  };

// destructor
//ProtonConsumer::~ProtonConsumer() {}
//
void ProtonConsumer::on_container_start(proton::container &c) {
  LOG_F(INFO, "Container Start");
  proton::connection_options co;
  receiver = c.open_receiver(url, co);
}

void ProtonConsumer::on_message(proton::delivery &d, proton::message &msg) {
  LOG_F(2, "Message Received");
}
//
//void ProtonConsumer::on_container_stop(proton::container &c) {}