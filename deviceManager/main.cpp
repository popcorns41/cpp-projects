#include "SimulatedDeviceClient.h"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  device_manager list\n";
    std::cout << "  device_manager status <device_id>\n";
}

void printDevice(const Device& device) {
    std::cout 
        << device.id << " "
        << device.name << " "
        << statusToString(device.status) << " "
        << device.firmwareVersion << "\n";
}

int main (int argc, char* argv[]) {

    try {
        std::unique_ptr<IDeviceClient> deviceClient =
            std::make_unique<SimulatedDeviceClient>("../data/devices.txt");
        
        if (argc < 2) {
            printUsage();
            return 1;
        }

        std::string command = argv[1];

        if (command == "list") {
            std::vector<Device> devices = deviceClient->listDevices();

            for (const Device& device : devices) {
                printDevice(device);
            }

            return 0;
        }

        if (command == "status") {
            if (argc != 3) {
                std::cerr << "Error: status requires a device ID.\n";
                printUsage();
                return 1;
            }

            std::string deviceId = argv[2];

            std::optional<Device> device = 
                deviceClient -> getDeviceById(deviceId);
            
            if (!device.has_value()) {
                std::cerr << "Error: device not found : " << deviceId << "\n";
                return 1;
            }

            std::cout << "Device: " << device->id << "\n";
            std::cout << "Name: " << device->name << "\n";
            std::cout << "Status: " << statusToString(device->status) << "\n";
            std::cout << "Firmware: " << device->firmwareVersion << "\n";

            return 0;
        }
        

        std::cerr << "Error: unknown command: " << command << "\n";
        printUsage();
        return 1;
        
    }catch (const std::exception& e){
        std::cerr << "Application error: " << e.what() << "\n";
        return 1;
    }
}