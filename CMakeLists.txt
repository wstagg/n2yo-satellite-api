cmake_minimum_required(VERSION 3.20.0)

project(satelliteTracker)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Set CMP0167 to OLD to use the legacy FindBoost module
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

find_package(CURL REQUIRED)
find_package(Boost REQUIRED COMPONENTS python)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

include_directories(${CMAKE_SOURCE_DIR}/include/)

add_library(satelliteTracker SHARED 
src/cpp/DataReceiver.cpp
src/cpp/Config.cpp
src/cpp/JsonParser.cpp
src/cpp/pythonInterface.cpp)

target_link_libraries(satelliteTracker
    CURL::libcurl
    Boost::python
    Python3::Python)

# Copy configuration file and directories
add_custom_command(
    TARGET satelliteTracker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/config.txt
            ${CMAKE_CURRENT_BINARY_DIR}/config.txt)

# Copy configuration file and directories
add_custom_command(
    TARGET satelliteTracker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/config_tests.txt
            ${CMAKE_CURRENT_BINARY_DIR}/config_tests.txt)

# Copy the .so to the Python source directory
add_custom_command(
    TARGET satelliteTracker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:satelliteTracker>
            ${CMAKE_SOURCE_DIR}/src/python/satelliteTracker.so
)

# Also copy config file to Python directory if needed
add_custom_command(
    TARGET satelliteTracker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/config.txt
            ${CMAKE_SOURCE_DIR}/src/python/config.txt
)

include_directories(${CMAKE_SOURCE_DIR}/tests/fixtures)

add_executable(tests
    tests/cpp/SatelliteTrackerTestsMain.cpp
    tests/cpp/DataReceiverTests.cpp
    tests/cpp/ConfigTests.cpp
    src/cpp/DataReceiver.cpp
    src/cpp/Config.cpp
    src/cpp/JsonParser.cpp
    src/cpp/pythonInterface.cpp)

target_link_libraries(tests
    CURL::libcurl
    Boost::python
    Python3::Python)

add_test(NAME SatelliteTrackerTests COMMAND tests)