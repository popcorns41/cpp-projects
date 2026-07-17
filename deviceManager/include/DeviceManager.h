#pragma once

#include "Device.h"
#include "IDeviceClient.h"
#include "OperationResult.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

class DeviceManager{
    public:
        explicit DeviceManager(std::unique_ptr<IDeviceClient> deviceClient);

        std::vector<Device> listDevices() const;

        std::optional<Device> getDeviceStatus(
            const std::string& deviceId
        ) const;
        
        OperationResult rebootDevice(const std::string& deviceId);

        OperationResult deployBuild(
            const std::string& deviceId,
            const std::string& buildPath
        );

        OperationResult setStatus(
            const std::string& deviceId,
            const std::string& statusText
        );

    private:
        std::unique_ptr<IDeviceClient> deviceClient_;
};