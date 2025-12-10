cmake_minimum_required(VERSION 3.20.0)
project(OrbitFetcher)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(BUILD_PY_BINDINGS "Build Python bindings" OFF)
enable_testing()

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

if(WIN32)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
    set(TEST_BOOST_LIBS Boost::unit_test_framework)
endif()

find_package(CURL REQUIRED)

set(SOURCES
    cpp/DataReceiver.cpp
    cpp/Config.cpp
    cpp/JsonParser.cpp
)

# Main C++ library - STATIC
add_library(OrbitFetcher STATIC ${SOURCES})
target_include_directories(OrbitFetcher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(OrbitFetcher PUBLIC CURL::libcurl)

# Optional Python bindings - SHARED library
if(BUILD_PY_BINDINGS)
    find_package(Boost REQUIRED COMPONENTS python)
    find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
    
    add_library(OrbitFetcher_py SHARED
        ${SOURCES}
        cpp/pythonInterface.cpp
    )
    
    target_include_directories(OrbitFetcher_py PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    set_target_properties(OrbitFetcher_py PROPERTIES
        PREFIX ""
        OUTPUT_NAME "OrbitFetcher"
    )
    
    target_link_libraries(OrbitFetcher_py
        PRIVATE
        CURL::libcurl
        Boost::python
        Python3::Python
    )
endif()

# Tests
add_executable(OrbitFetcherTests
    tests/cpp/OrbitFetcherTestsMain.cpp
    tests/cpp/DataReceiverUsingConfigFileTests.cpp
    tests/cpp/DataReceiverTests.cpp
    tests/cpp/ConfigTests.cpp
    cpp/DataReceiver.cpp
    cpp/Config.cpp
    cpp/JsonParser.cpp
)

target_include_directories(OrbitFetcherTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures
)

target_link_libraries(OrbitFetcherTests
    PRIVATE
    CURL::libcurl
    ${TEST_BOOST_LIBS}
)

add_test(NAME OrbitFetcherTests COMMAND OrbitFetcherTests)