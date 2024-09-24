// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <chrono>
#include <string>
#include <discord_rpc.h>
#include "common/common_types.h"
#include "core/core.h"
#include "core/loader/loader.h"
#include "cytrus_qt/discord_impl.h"
#include "cytrus_qt/uisettings.h"

namespace DiscordRPC {

DiscordImpl::DiscordImpl(const Core::System& system_) : system{system_} {
    DiscordEventHandlers handlers{};

    // The number is the client ID for Cytrus, it's used for images and the
    // application name
    Discord_Initialize("1288168516196892702", &handlers, 1, nullptr);
}

DiscordImpl::~DiscordImpl() {
    Discord_ClearPresence();
    Discord_Shutdown();
}

void DiscordImpl::Pause() {
    Discord_ClearPresence();
}

void DiscordImpl::Update() {
    s64 start_time = std::chrono::duration_cast<std::chrono::seconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count();
    std::string title;
    const bool is_powered_on = system.IsPoweredOn();
    if (is_powered_on) {
        system.GetAppLoader().ReadTitle(title);
    }

    DiscordRichPresence presence{};
    presence.largeImageKey = "cytrus";
    presence.largeImageText = "Cytrus is an emulator for the Nintendo 3DS";
    if (is_powered_on) {
        presence.state = title.c_str();
        presence.details = "Currently in game";
    } else {
        presence.details = "Not in game";
    }
    presence.startTimestamp = start_time;
    Discord_UpdatePresence(&presence);
}
} // namespace DiscordRPC
