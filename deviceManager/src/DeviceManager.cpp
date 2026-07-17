#include "DeviceManager.h"
#include <filesystem>
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

OperationResult DeviceManager::deployBuild(
    const std::string& deviceId,
    const std::string& buildPath
) {
    std::optional<Device> device = deviceClient_->getDeviceById(deviceId);

    if (!device.has_value()) {
        return OperationResult{
            false,
            "Device not found: " + deviceId
        };
    }

    if (device->status == DeviceStatus::Offline) { 
        return OperationResult{
            false,
            "Cannot deploy to offline device: " + deviceId
        };
    }

     if (device->status == DeviceStatus::Busy) {
        return OperationResult{
            false,
            "Cannot deploy to busy device: " + deviceId
        };
    }

    if (device->status == DeviceStatus::Error) {
        return OperationResult{
            false,
            "Cannot deploy to device in error state: " + deviceId
        };
    }

    if (!std::filesystem::exists(buildPath)) {
        return OperationResult{
            false,
            "Build file not found: " + buildPath
        };
    }

    bool deploySent = deviceClient_->deployBuild(deviceId, buildPath);

    if (!deploySent) {
        return OperationResult{
            false,
            "Failed to deploy build to device: " + deviceId
        };
    }

    return OperationResult{
        true,
        "Build deployed successfully to device: " + deviceId
    };
}

OperationResult DeviceManager::setStatus(
    const std::string& deviceId,
    const std::string& statusText
) {

    DeviceStatus newStatus = statusFromString(statusText);

    if (newStatus == DeviceStatus::Unknown) {
        return OperationResult{
            false,
            "Invalid device status: " + statusText
        };
    }

    std::optional<Device> device = deviceClient_->getDeviceById(deviceId);

    if (!device.has_value()) {
        return OperationResult{
            false,
            "Device not found: " + deviceId
        };
    }

    bool updated = deviceClient_->setStatus(deviceId, newStatus);

    if (!updated) {
        return OperationResult{
            false,
            "Failed to update device status: " + deviceId
        };
    }


    return OperationResult{
        true,
        "Device " + deviceId + " status updated to " + statusToString(newStatus)
    };
}
