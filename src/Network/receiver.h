#ifndef SRT_GAME_SERVER_RECEIVER_H
#define SRT_GAME_SERVER_RECEIVER_H

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

// Attribution:
// https://github.com/apache/qpid-proton/blob/0.33.0/cpp/examples/multithreaded_client_flow_control.cpp
// https://qpid.apache.org/releases/qpid-proton-0.33.0/proton/cpp/api/multithreaded_client_flow_control_8cpp-example.html

#include "closed.h"
#include <proton/connection.hpp>
#include <proton/connection_options.hpp>
#include <proton/container.hpp>
#include <proton/message.hpp>
#include <proton/messaging_handler.hpp>
#include <proton/receiver.hpp>
#include <proton/receiver_options.hpp>
#include <proton/sender.hpp>
#include <proton/work_queue.hpp>

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>


// A thread safe receiving connection that blocks receiving threads when there
// are no messages available, and maintains a bounded buffer of incoming
// messages by issuing AMQP credit only when there is space in the buffer.
class receiver : private proton::messaging_handler {
    static const size_t MAX_BUFFER = 100; // Max number of buffered messages

    // Used in proton threads only
    proton::receiver receiver_;

    // Used in proton and user threads, protected by lock_
    std::mutex lock_;
    proton::work_queue* work_queue_;
    std::queue<proton::message> buffer_; // Messages not yet returned by receive()
    std::condition_variable can_receive_; // Notify receivers of messages
    bool closed_;

public:

    // Connect to url
    receiver(proton::container& cont, const std::string& url, const std::string& address)
            : work_queue_(0), closed_(false)
    {
        // NOTE:credit_window(0) disables automatic flow control.
        // We will use flow control to match AMQP credit to buffer capacity.
        cont.open_receiver(url+"/"+address, proton::receiver_options().credit_window(0),
                           proton::connection_options().handler(*this));
    }

    // Thread safe receive
    proton::message receive() {
        std::unique_lock<std::mutex> l(lock_);
        // Wait for buffered messages
        while (!closed_ && (!work_queue_ || buffer_.empty())) {
            can_receive_.wait(l);
        }
        if (closed_) throw closed("receiver closed");
        proton::message m = std::move(buffer_.front());
        buffer_.pop();
        // Add a lambda to the work queue to call receive_done().
        // This will tell the handler to add more credit.
        work_queue_->add([=]() { this->receive_done(); });
        return m;
    }

    // Thread safe
    void close() {
        std::lock_guard<std::mutex> l(lock_);
        if (!closed_) {
            closed_ = true;
            can_receive_.notify_all();
            if (work_queue_) {
                work_queue_->add([this]() { this->receiver_.connection().close(); });
            }
        }
    }

private:
    // ==== The following are called by proton threads only.

    void on_receiver_open(proton::receiver& r) override {
        receiver_ = r;
        std::lock_guard<std::mutex> l(lock_);
        work_queue_ = &receiver_.work_queue();
        receiver_.add_credit(MAX_BUFFER); // Buffer is empty, initial credit is the limit
    }

    void on_message(proton::delivery &d, proton::message &m) override {
        // Proton automatically reduces credit by 1 before calling on_message
        std::lock_guard<std::mutex> l(lock_);
        buffer_.push(m);
        can_receive_.notify_all();
    }

    // called via work_queue
    void receive_done() {
        // Add 1 credit, a receiver has taken a message out of the buffer.
        receiver_.add_credit(1);
    }

    void on_error(const proton::error_condition& e) override {
        std::mutex out_lock;
        #define OUT(x) do { std::lock_guard<std::mutex> l(out_lock); x; } while (false)

        OUT(std::cerr << "unexpected error: " << e << std::endl);
        exit(1);
    }
};


#endif //SRT_GAME_SERVER_RECEIVER_H
