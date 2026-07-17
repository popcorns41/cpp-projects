#include <string>
#include <DeviceStatus.h>

struct Device {
    std::string id;
    std::string name;
    DeviceStatus status;
    std::string firmwareVersion;
};