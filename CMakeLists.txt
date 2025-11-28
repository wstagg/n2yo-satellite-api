cmake_minimum_required(VERSION 3.20.0)

project(n2yoSatelliteApi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(BUILD_PY_BINDINGS "Build Python bindings" OFF)

enable_testing()

# Set CMP0167 to OLD to use the legacy FindBoost module
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

find_package(CURL REQUIRED)

set(SOURCES
    cpp/DataReceiver.cpp
    cpp/Config.cpp
    cpp/JsonParser.cpp)

if (BUILD_PY_BINDINGS)
    find_package(Boost REQUIRED COMPONENTS python)
    find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
    list(APPEND SOURCES cpp/pythonInterface.cpp)
endif ()

add_library(n2yoSatelliteApi SHARED
${SOURCES})

target_include_directories(n2yoSatelliteApi PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(n2yoSatelliteApi PROPERTIES PREFIX "")

set (LIBS CURL::libcurl)

if (BUILD_PY_BINDINGS)
list(APPEND LIBS
        Boost::python
        Python3::Python)
endif ()

target_link_libraries(n2yoSatelliteApi
    ${LIBS})

add_executable(n2yoSatelliteApiTests
    tests/cpp/SatelliteTrackerTestsMain.cpp
    tests/cpp/DataReceiverUsingConfigFileTests.cpp
    tests/cpp/DataReceiverTests.cpp
    tests/cpp/ConfigTests.cpp
    cpp/DataReceiver.cpp
    cpp/Config.cpp
    cpp/JsonParser.cpp)

target_include_directories(n2yoSatelliteApiTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures)

target_link_libraries(n2yoSatelliteApiTests
    CURL::libcurl)

add_test(NAME SatelliteTrackerTests COMMAND n2yoSatelliteApiTests)