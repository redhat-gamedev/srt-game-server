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

#include "Config.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "../Logging/loguru.hpp"
#include <cstring>

// Define the static Singleton pointer
Config* Config::inst_ = nullptr;

Config::Config() {
    // Default values
    brokerUri = "tcp://127.0.0.1:5672";
    sleepCycle = 50;
    commandIn = "COMMAND.IN";
    gameEventOut = "GAME.EVENT.OUT";
    forceMultiplier = 5000.0;
}

void Config::init(int &argc, char *argv[]) {
    LOG_F(INFO, "Initializing configuration ...");

    if (inst_ == nullptr) {
        LOG_F(MAX, "Constructing a fresh Config instance");
        inst_ = new Config();
    }

    // Load the config.yaml file
    YAML::Node yamlConfig = inst_->yamlConfig = YAML::LoadFile("config.yaml");
    if (yamlConfig["broker-uri"]) {
        inst_->brokerUri = yamlConfig["broker-uri"].as<std::string>();
    }
    if (yamlConfig["sleep-cycle"]) {
        inst_->sleepCycle = yamlConfig["sleep-cycle"].as<long>();
    }
    if (yamlConfig["command-in"]) {
        inst_->commandIn = yamlConfig["command-in"].as<std::string>();
    }
    if (yamlConfig["game-event-out"]) {
        inst_->gameEventOut = yamlConfig["game-event-out"].as<std::string>();
    }
    if (yamlConfig["force-multiplier"]) {
        inst_->forceMultiplier = yamlConfig["force-multiplier"].as<float>();
    }

    // TODO: Process -> Usage Error checking on arg
    // Override yamlConfig.yaml and default values with any matching command line args
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp(argv[i], "--broker-uri")) {
            inst_->brokerUri = argv[++i];
        } else if (0 == strcmp(argv[i], "--sleep-cycle")) {
            inst_->sleepCycle = strtol(argv[++i], nullptr, 0);
        } else if (0 == strcmp(argv[i], "--command-in")) {
            inst_->commandIn = argv[++i];
        } else if (0 == strcmp(argv[i], "--game-event-out")) {
            inst_->gameEventOut = argv[++i];
        }else if (0 == strcmp(argv[i], "--force-multiplier")) {
            inst_->forceMultiplier = strtof(argv[++i], nullptr);
        }
    }
}

Config *Config::Instance() {
    if (inst_ == nullptr) {
        LOG_F(WARNING, "Config::Instance() called without calling Config::init() first. Using default values.");
        LOG_F(MAX, "Constructing a fresh yamlConfig instance");
        inst_ = new Config();
    }

    return inst_;
}
