#ifndef __ProtonConsumer__
#define __ProtonConsumer__

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

class ProtonConsumer : public proton::messaging_handler {
  private:
    std::string url;
    proton::receiver receiver;

  public:
    // constructor
    ProtonConsumer(const std::string &s);

    // destructor
    //virtual ~ProtonConsumer() {};

    void on_container_start(proton::container &c) OVERRIDE;
    void on_message(proton::delivery &d, proton::message &msg) OVERRIDE;
};

#endif

