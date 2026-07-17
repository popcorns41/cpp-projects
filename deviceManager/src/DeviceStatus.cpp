#include "DeviceStatus.h"

std::string statusToString(DeviceStatus status) {
    switch (status) {
        case DeviceStatus::Online:
            return "Online";
        case DeviceStatus::Offline:
            return "Offlien";
        case DeviceStatus::Busy:
            return "Busy";
        case DeviceStatus::Error:
            return "Error";
        case DeviceStatus::Unknown:
            return "Unknown";
    };

    return "Unknown";
}


DeviceStatus statusFromString(const std::string& text) {
    if (text == "Online") {
        return DeviceStatus::Online;
    }

    if (text == "Offline") {
        return DeviceStatus::Offline;
    }

    if (text == "Busy") {
        return DeviceStatus::Busy;
    }

    if (text == "Error") {
        return DeviceStatus::Error;
    }

    return DeviceStatus::Unknown;
}