cmake_minimum_required(VERSION 3.5)
project(OHLCService)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE -lprotobuf --std=c++20")
set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

include(FetchContent)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(protobuf CONFIG REQUIRED)

add_library(proto-objects OBJECT "${CMAKE_CURRENT_LIST_DIR}/protobufs/ohlc.proto")
target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/protobufs")

target_include_directories(proto-objects PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET proto-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/protobufs"
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")


FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)


FetchContent_MakeAvailable(json)

file(GLOB OHLCService_SOURCES src/*.cpp)
file(GLOB protobufs_SOURCES protofs/*.cc)

add_library(libOHLCService ${OHLCService_SOURCES})
target_include_directories(libOHLCService PUBLIC include/ protobufs/ ${PROTO_HDRS})
target_link_libraries (libOHLCService PUBLIC proto-objects nlohmann_json::nlohmann_json absl::base absl::strings ${Protobuf_LIBRARIES})

add_executable(OHLCService src/main.cpp)
target_include_directories(OHLCService PRIVATE include/)
target_link_libraries(OHLCService libOHLCService proto-objects ${Protobuf_LIBRARIES} nlohmann_json::nlohmann_json) 