#ifndef SRT_GAME_SERVER_CONFIGURATION_H
#define SRT_GAME_SERVER_CONFIGURATION_H

//   Copyright 2020 Roddie Kieley
//
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

#include <string>


class Configuration {
private:
    std::string         m_strBrokerURI;

protected:
    // Constructor(s)
    Configuration() {};

    // Destructor
    ~Configuration() {};

public:
    std::string&        BrokerURI = m_strBrokerURI;

    // Singleton(s)
    static Configuration& Instance()
    {
        static Configuration theConfiguration;
        return theConfiguration;
    }
};


#endif //SRT_GAME_SERVER_CONFIGURATION_H
