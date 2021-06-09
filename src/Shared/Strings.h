#pragma once

//   Provides useful String functions.
//
//   Copyright 2021 Derek Reese
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

#include <algorithm>
#include <cctype>
#include <cstring>
// @TODO: Convert this to string_view for CPP17.
#include <string>

static inline void ltrim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char chr) {
        return !std::isspace(chr) || reinterpret_cast<const char*>(chr) == "\"";
    }));
}

static inline void rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char chr) {
        return !std::isspace(chr) || reinterpret_cast<const char*>(chr) == "\"";
    }).base(), str.end());
}

static inline void trim(std::string &str) {
    ltrim(str);
    rtrim(str);
}
