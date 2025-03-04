// Copyright 2020 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <string>

namespace NetSettings {

struct Values {
    // WebService
    bool enable_telemetry;
    std::string web_api_url;
    std::string cytrus_username;
    std::string cytrus_token;
} extern values;

} // namespace NetSettings
