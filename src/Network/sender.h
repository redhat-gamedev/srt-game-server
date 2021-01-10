#ifndef SRT_GAME_SERVER_SENDER_H
#define SRT_GAME_SERVER_SENDER_H

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


// A thread-safe sending connection that blocks sending threads when there
// is no AMQP credit to send messages.
class sender : private proton::messaging_handler {
    // Only used in proton handler thread
    proton::sender sender_;

    // Shared by proton and user threads, protected by lock_
    std::mutex lock_;
    proton::work_queue *work_queue_;
    std::condition_variable sender_ready_;
    int queued_;                       // Queued messages waiting to be sent
    int credit_;                       // AMQP credit - number of messages we can send

public:
    sender(proton::container& cont, const std::string& url, const std::string& address)
            : work_queue_(0), queued_(0), credit_(0)
    {
        cont.open_sender(url+"/"+address, proton::connection_options().handler(*this));
    }

    // Thread safe
    void send(const proton::message& m) {
        {
            std::unique_lock<std::mutex> l(lock_);
            // Don't queue up more messages than we have credit for
            while (!work_queue_ || queued_ >= credit_) sender_ready_.wait(l);
            ++queued_;
        }
        work_queue_->add([=]() { this->do_send(m); }); // work_queue_ is thread safe
    }

    // Thread safe
    void close() {
        work_queue()->add([=]() { sender_.connection().close(); });
    }

private:

    proton::work_queue* work_queue() {
        // Wait till work_queue_ and sender_ are initialized.
        std::unique_lock<std::mutex> l(lock_);
        while (!work_queue_) sender_ready_.wait(l);
        return work_queue_;
    }

    // == messaging_handler overrides, only called in proton handler thread

    void on_sender_open(proton::sender& s) override {
        // Make sure sender_ and work_queue_ are set atomically
        std::lock_guard<std::mutex> l(lock_);
        sender_ = s;
        work_queue_ = &s.work_queue();
    }

    void on_sendable(proton::sender& s) override {
        std::lock_guard<std::mutex> l(lock_);
        credit_ = s.credit();
        sender_ready_.notify_all(); // Notify senders we have credit
    }

    // work_queue work items is are automatically dequeued and called by proton
    // This function is called because it was queued by send()
    void do_send(const proton::message& m) {
        sender_.send(m);
        std::lock_guard<std::mutex> l(lock_);
        --queued_;                    // work item was consumed from the work_queue
        credit_ = sender_.credit();   // update credit
        sender_ready_.notify_all();       // Notify senders we have space on queue
    }

    void on_error(const proton::error_condition& e) override {
        std::mutex out_lock;
        #define OUT(x) do { std::lock_guard<std::mutex> l(out_lock); x; } while (false)

        OUT(std::cerr << "unexpected error: " << e << std::endl);
        exit(1);
    }
};


#endif //SRT_GAME_SERVER_SENDER_H
