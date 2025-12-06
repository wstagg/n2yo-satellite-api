cmake_minimum_required(VERSION 3.20.0)

project(OrbitFetcher)

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

add_library(OrbitFetcher SHARED
${SOURCES})

target_include_directories(OrbitFetcher PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(OrbitFetcher PROPERTIES PREFIX "")

set (LIBS CURL::libcurl)

if (BUILD_PY_BINDINGS)
list(APPEND LIBS
        Boost::python
        Python3::Python)
endif ()

target_link_libraries(OrbitFetcher
    ${LIBS})

add_executable(OrbitFetcherTests
        tests/cpp/OrbitFetcherTestsMain.cpp
        tests/cpp/DataReceiverUsingConfigFileTests.cpp
        tests/cpp/DataReceiverTests.cpp
        tests/cpp/ConfigTests.cpp
        cpp/DataReceiver.cpp
        cpp/Config.cpp
        cpp/JsonParser.cpp)

target_include_directories(OrbitFetcherTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures)

target_link_libraries(OrbitFetcherTests
    CURL::libcurl)

add_test(NAME OrbitFetcherTests COMMAND OrbitFetcherTests)