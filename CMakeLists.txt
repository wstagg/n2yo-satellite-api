cmake_minimum_required(VERSION 3.20.0)

project(n2yoSatelliteApi)

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



add_library(n2yoSatelliteApi SHARED 
cpp/DataReceiver.cpp
cpp/Config.cpp
cpp/JsonParser.cpp
cpp/pythonInterface.cpp)

target_include_directories(n2yoSatelliteApi PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add this line:
set_target_properties(n2yoSatelliteApi PROPERTIES PREFIX "")

target_link_libraries(n2yoSatelliteApi
    CURL::libcurl
    Boost::python
    Python3::Python)

add_executable(tests
    tests/cpp/SatelliteTrackerTestsMain.cpp
    tests/cpp/DataReceiverUsingConfigFileTests.cpp
    tests/cpp/DataReceiverTests.cpp
    tests/cpp/ConfigTests.cpp
    cpp/DataReceiver.cpp
    cpp/Config.cpp
    cpp/JsonParser.cpp
    cpp/pythonInterface.cpp)

target_include_directories(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures)

target_link_libraries(tests
    CURL::libcurl
    Boost::python
    Python3::Python)

add_test(NAME SatelliteTrackerTests COMMAND tests)