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
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

class Configuration {
private:
    static Configuration *m_pConInstance;  // The instance

    // Config variables default values
    std::string m_strBrokerUri     = "tcp://127.0.0.1:5672";
    long        m_lSleepCycle      = 50;
    std::string m_strCommandIn     = "COMMAND.IN";
    std::string m_strGameEventOut  = "GAME.EVENT.OUT";
    float       m_fForceMultiplier = 5000.0;

protected:
    // Constructor
    Configuration() = default;

    // Destructor
    ~Configuration() = default;

public:
    // Config variables references to protected members for convenience
    std::string &BrokerUri       = m_strBrokerUri;
    long        &SleepCycle      = m_lSleepCycle;
    std::string &CommandIn       = m_strCommandIn;
    std::string &GameEventOut    = m_strGameEventOut;
    float       &ForceMultiplier = m_fForceMultiplier;

    void Init(int &argc, char *argv[]);

    // Singleton
    static Configuration &Instance();
};

#endif //SRT_GAME_SERVER_CONFIGURATION_H
