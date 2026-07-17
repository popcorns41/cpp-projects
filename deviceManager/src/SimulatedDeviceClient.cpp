#include "SimulatedDeviceClient.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

SimulatedDeviceClient::SimulatedDeviceClient(std::string devicesFilePath)
    : devicesFilePath_(std::move(devicesFilePath)) {}

std::vector<Device> SimulatedDeviceClient::listDevices() const {
    std::ifstream file(devicesFilePath_);

    if (!file.is_open()){
        throw std::runtime_error(
            "Failed to open devices file: " + devicesFilePath_
        );
    }

    std::vector<Device> devices;
    std::string line;

    while (std::getline(file, line)) {
        std::optional<Device> device = parseDeviceLine(line);

        if (device.has_value()) {
            devices.push_back(device.value());
        }
    }

    return devices;
}

bool SimulatedDeviceClient::rebootDevice(const std::string& id) {
    return getDeviceById(id).has_value();
}

std::optional<Device> SimulatedDeviceClient::getDeviceById(
    const std::string& id
) const {
    std::vector<Device> devices = listDevices();

    for (const Device& device : devices) {
        if (device.id == id) {
            return device;
        }
    }

    return std::nullopt;
}

std::optional<Device> SimulatedDeviceClient::parseDeviceLine(
    const std::string& line
) const {
    std::istringstream stream(line);

    std::string id;
    std::string name;
    std::string statusText;
    std::string firmwareVersion;

    if (!(stream >> id >> name >> statusText >> firmwareVersion)) {
        return std::nullopt;
    }

    DeviceStatus status = statusFromString(statusText);

    if (status == DeviceStatus::Unknown) {
        return std::nullopt;
    }

    return Device{
        id,
        name,
        status,
        firmwareVersion
    };
}