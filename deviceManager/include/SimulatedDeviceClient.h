#pragma once

#include "IDeviceClient.h"

#include <string>
#include <vector>

class SimulatedDeviceClient : public IDeviceClient {
    public:
        explicit SimulatedDeviceClient(std::string devicesFilePath); 

        std::vector<Device> listDevices() const override;

        std::optional<Device> getDeviceById(
            const std::string& id
        ) const override;
    
        private:
            std::string devicesFilePath_;
            std::optional<Device> parseDeviceLine(
                const std::string& line
            ) const ;
};
