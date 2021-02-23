#ifndef SRT_GAME_SERVER_CONFIG_H
#define SRT_GAME_SERVER_CONFIG_H

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
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"

class Config {
private:
    // Private constructor per singleton pattern
    Config();

    static Config *inst_;   // The one, single instance

    // holds the contents of the config.yaml file
    YAML::Node yamlConfig;

public:
    // Config variables
    std::string brokerUri;
    long sleepCycle;
    std::string commandIn;
    std::string gameEventOut;
    float forceMultiplier;

    static void init(int &argc, char *argv[]);

    // Singleton
    static Config *Instance();
};

#endif //SRT_GAME_SERVER_CONFIG_H
