#include <vector>
#include <string>
#include <Device.h>
#include <optional>


class IDeviceClient {
    public:
        virtual ~IDeviceClient() = default;

        virtual std::vector<Device> listDevices() const = 0;
        virtual std::optional<Device> getDeviceById(const std::string& id) const = 0;
        virtual bool rebootDevice(const std::string& id) = 0;
        virtual bool deployBuild(const std::string& id, const std::string& buildPath) = 0;
        virtual std::vector<std::string> fetchLogs(const std::string& id) const = 0;
};