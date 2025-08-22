cmake_minimum_required(VERSION 3.20.0)

project(satelliteTracker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/)

add_executable(satelliteTracker 
src/main.cpp
src/DataReceiver.cpp
src/Config.cpp)

target_link_libraries(satelliteTracker
    CURL::libcurl)

# Copy configuration file and directories
add_custom_command(
        TARGET satelliteTracker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/config.txt
                ${CMAKE_CURRENT_BINARY_DIR}/config.txt)

