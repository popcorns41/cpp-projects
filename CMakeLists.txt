cmake_minimum_required(VERSION 3.20)

project(DevToolLogInspector)

add_executable(log_inspector main.cpp)

target_compile_features(log_inspector PRIVATE cxx_std_17)

if (MSVC)
    target_compile_options(log_inspector PRIVATE /W4)
else()
    target_compile_options(log_inspector PRIVATE -Wall -Wextra -Wpedantic)
endif()