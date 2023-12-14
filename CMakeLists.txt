cmake_minimum_required(VERSION 3.5)
project(OHLCService)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE -lprotobuf --std=c++20")
set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})
 
# set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--copy-dt-needed-entries")
# set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--copy-dt-needed-entries")
# set(CMAKE_STATIC_LINKER_FLAGS "-Wl,--copy-dt-needed-entries")

include(FetchContent)

set(PROTO_SRCS protobufs)
set(PROTO_HDRS protobufs)

find_package(absl REQUIRED)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protobufs/ohlc.proto)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS EXPORT_MACRO DLL_EXPORT protobufs/ohlc.proto)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS PROTO_DESCS protobufs/ohlc.proto)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)

FetchContent_MakeAvailable(json)

file(GLOB OHLCService_SOURCES src/*.cpp)
file(GLOB protobufs_SOURCES protofs/*.cc)

add_library(libOHLCService ${OHLCService_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(libOHLCService PUBLIC include/ protobufs/ ${PROTO_HDRS})
target_link_libraries (libOHLCService PUBLIC nlohmann_json::nlohmann_json absl::base absl::strings ${Protobuf_LIBRARIES})

# add_library(protobufs ${protobufs_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
# target_include_directories(protobufs PUBLIC protobufs/ )
# target_link_libraries(protobufs PUBLIC ${Protobuf_LIBRARIES} nlohmann_json::nlohmann_json)

add_executable(OHLCService src/main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(OHLCService PRIVATE include/)
target_link_libraries(OHLCService libOHLCService absl::base absl::strings ${Protobuf_LIBRARIES} nlohmann_json::nlohmann_json) 
 