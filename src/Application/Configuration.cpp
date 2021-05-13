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

#include <cstring>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

#include "Configuration.h"
#include "../Logging/loguru.hpp"
#include "../Shared/Strings.h"

// Define the static Singleton pointer
Configuration *Configuration::m_pConInstance = nullptr;

void Configuration::Init(int &argc, char *argv[]) {
    LOG_F(INFO, "Initializing configuration ...");

    // Load the config.yaml file
    try {
        YAML::Node config = YAML::LoadFile("config.yaml");
        if (config["broker-uri"]) {
            m_pConInstance->BrokerUri = config["broker-uri"].as<std::string>();
        }
        if (config["sleep-cycle"]) {
            m_pConInstance->SleepCycle = config["sleep-cycle"].as<long>();
        }
        if (config["command-in"]) {
            m_pConInstance->CommandIn = config["command-in"].as<std::string>();
        }
        if (config["game-event-out"]) {
            m_pConInstance->GameEventOut = config["game-event-out"].as<std::string>();
        }
        if (config["force-multiplier"]) {
            m_pConInstance->ForceMultiplier = config["force-multiplier"].as<float>();
        }
        if (config["ship-width"]) {
            m_pConInstance->ShipWidth = config["ship-width"].as<float>();
        }
        if (config["ship-length"]) {
            m_pConInstance->ShipLength = config["ship-length"].as<float>();
        }
        if (config["fixture-density"]) {
            m_pConInstance->FixtureDensity = config["fixture-density"].as<float>();
        }
    }
    catch (YAML::BadFile &e) {
        LOG_F(INFO, "No config.yaml found..skipping");
    }

    // TODO: Process -> Usage Error checking on arg
    // Override yaml config and default values with any matching command line args
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp(argv[i], "--broker-uri")) {
            std::string m_strBrokerUri(argv[++i]);
            trim(m_strBrokerUri);
            m_pConInstance->BrokerUri = m_strBrokerUri;
        } else if (0 == strcmp(argv[i], "--sleep-cycle")) {
            m_pConInstance->SleepCycle = strtol(argv[++i], nullptr, 0);
        } else if (0 == strcmp(argv[i], "--command-in")) {
            m_pConInstance->CommandIn = argv[++i];
        } else if (0 == strcmp(argv[i], "--game-event-out")) {
            m_pConInstance->GameEventOut = argv[++i];
        } else if (0 == strcmp(argv[i], "--force-multiplier")) {
            m_pConInstance->ForceMultiplier = strtof(argv[++i], nullptr);
        } else if (0 == strcmp(argv[i], "--ship-width")) {
            m_pConInstance->ShipWidth = strtof(argv[++i], nullptr);
        } else if (0 == strcmp(argv[i], "--ship-length")) {
            m_pConInstance->ShipLength = strtof(argv[++i], nullptr);
        } else if (0 == strcmp(argv[i], "--fixture-density")) {
            m_pConInstance->FixtureDensity = strtof(argv[++i], nullptr);
        }
    }

    // Output the final configuration
    LOG_F(INFO, "Broker URI         : %s", m_pConInstance->BrokerUri.c_str());
    LOG_F(INFO, "Sleep Cycle        : %d", m_pConInstance->SleepCycle);
    LOG_F(INFO, "Command IN         : %s", m_pConInstance->CommandIn.c_str());
    LOG_F(INFO, "Game Event OUT     : %s", m_pConInstance->GameEventOut.c_str());
    LOG_F(INFO, "Force Multiplier   : %f", m_pConInstance->ForceMultiplier);
    LOG_F(INFO, "Ship Width         : %f", m_pConInstance->ShipWidth);
    LOG_F(INFO, "Ship Length        : %f", m_pConInstance->ShipLength);
    LOG_F(INFO, "Fixture Density    : %f", m_pConInstance->FixtureDensity);
}

Configuration &Configuration::Instance() {
    static Configuration theConfiguration;

    if (m_pConInstance == nullptr) {
        // Keep a pointer to the instance so it can be initialized later with argv
        m_pConInstance = &theConfiguration;
    }

    return theConfiguration;
}
