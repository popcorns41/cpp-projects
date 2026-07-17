cmake_minimum_required(VERSION 3.20)

project(DeviceManager)

add_executable(device_manager
    main.cpp
    src/DeviceStatus.cpp
    src/SimulatedDeviceClient.cpp
    src/DeviceManager.cpp
    include/OperationResult.h
)

target_include_directories(device_manager PRIVATE include)

target_compile_features(device_manager PRIVATE cxx_std_17)

if (MSVC)
    target_compile_options(device_manager PRIVATE /W4)
else()
    target_compile_options(device_manager PRIVATE -Wall -Wextra -Wpedantic)
endif()