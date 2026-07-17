#include "DeviceManager.h"

#include <stdexcept>
#include <utility>

DeviceManager::DeviceManager(std::unique_ptr<IDeviceClient> deviceClient)
    : deviceClient_(std::move(deviceClient)) {

    if(!deviceClient_) {
        throw std::invalid_argument("DeviceManager requires a valid device client.");
    }
}

std::vector<Device> DeviceManager::listDevices() const {
    return deviceClient_->listDevices();
}

std::optional<Device> DeviceManager::getDeviceStatus(
    const std::string& deviceId
) const {
    return deviceClient_->getDeviceById(deviceId);
}

OperationResult DeviceManager::rebootDevice(const std::string& deviceId) {
    std::optional<Device> device = deviceClient_->getDeviceById(deviceId);

    if (!device.has_value()) {
        return OperationResult{
            false,
            "Device not found: " + deviceId
        };
    }

    if (device->status == DeviceStatus::Busy) {
        return OperationResult{
            false,
            "Cannot reboot busy device: " + deviceId
        };
    }

    bool rebootSent = deviceClient_->rebootDevice(deviceId);

    if (!rebootSent) {
        return OperationResult{
            false,
            "Failed to send roobt command to device: " + deviceId
        };
    }

    return OperationResult{
        true,
        "Reboot command sent successfully to device: " + deviceId
    };
}