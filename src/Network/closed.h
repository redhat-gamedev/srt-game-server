#ifndef SRT_GAME_SERVER_CLOSED_H
#define SRT_GAME_SERVER_CLOSED_H

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


// Exception raised if a sender or receiver is closed when trying to send/receive
class closed : public std::runtime_error {
public:
    closed(const std::string& msg) : std::runtime_error(msg) {}
};


#endif //SRT_GAME_SERVER_CLOSED_H
