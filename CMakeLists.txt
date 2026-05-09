cmake_minimum_required(VERSION 3.19)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(ShellAPI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(AddSAMPPlugin)

add_subdirectory(lib/omp-sdk)

add_samp_plugin(ShellAPI
    src/main.cpp
    src/packages/logs/logs.cpp
    src/packages/natives/natives.cpp
)

target_include_directories(ShellAPI PRIVATE
    lib
    src
    lib/samp-ptl
    lib/omp-sdk/include
    lib/omp-sdk/lib/glm
    lib/omp-sdk/lib/robin-hood-hashing/src/include
    lib/omp-sdk/lib/span-lite/include
    lib/omp-sdk/lib/string-view-lite/include
)

target_link_libraries(ShellAPI PRIVATE OMP-SDK)
