cmake_minimum_required(VERSION 3.0)
project(OHLCService)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE --std=c++20")

file(GLOB OHLCService_SOURCES src/*.cpp)

add_library(libOHLCService ${OHLCService_SOURCES})
target_include_directories(libOHLCService PUBLIC include/)

add_executable(OHLCService src/main.cpp)
target_include_directories(OHLCService PRIVATE include/)
target_link_libraries(OHLCService libOHLCService) 
 
