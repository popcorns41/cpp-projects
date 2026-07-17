#pragma once

#include <string>

enum class DeviceStatus {
    Online,
    Offline,
    Busy,
    Error,
    Unknown
};

std::string statusToString(DeviceStatus status);
DeviceStatus statusFromString(const std::string& text);