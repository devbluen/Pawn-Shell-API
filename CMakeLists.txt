cmake_minimum_required(VERSION 3.19)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
# Version comes from -DSHELLAPI_VERSION=x.y.z (CI) or, locally, from the latest git tag.
if(NOT SHELLAPI_VERSION)
    execute_process(
        COMMAND git describe --tags --abbrev=0 --match "*[0-9]*.[0-9]*.[0-9]*"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE _git_tag OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" SHELLAPI_VERSION "${_git_tag}")
    if(NOT SHELLAPI_VERSION)
        set(SHELLAPI_VERSION 0.0.0)
    endif()
endif()
if(NOT SHELLAPI_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+$")
    message(FATAL_ERROR "SHELLAPI_VERSION must be MAJOR.MINOR.PATCH, got '${SHELLAPI_VERSION}'")
endif()
set(SHELLAPI_VERSION "${SHELLAPI_VERSION}" CACHE STRING "Plugin version (MAJOR.MINOR.PATCH)" FORCE)

project(ShellAPI VERSION ${SHELLAPI_VERSION} LANGUAGES CXX)
message(STATUS "ShellAPI version: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(AddSAMPPlugin)

add_subdirectory(lib/omp-sdk)

add_samp_plugin(ShellAPI
    src/main.cpp
    src/packages/natives/natives.cpp
    src/packages/logs/logs.cpp
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

target_compile_definitions(ShellAPI PRIVATE
    SHELLAPI_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    SHELLAPI_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    SHELLAPI_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)
