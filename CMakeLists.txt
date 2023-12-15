cmake_minimum_required(VERSION 3.5)
project(OHLCService)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE -lprotobuf --std=c++20")
set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

include(FetchContent)

set(RDKAFKA_BUILD_EXAMPLES OFF ON CACHE INTERNAL "Turn off examples")
set(RDKAFKA_BUILD_TESTS OFF CACHE INTERNAL "Turn off tests")
FetchContent_Declare(
    librdkafka
    GIT_REPOSITORY https://github.com/confluentinc/librdkafka
    GIT_TAG        v2.3.0
)


FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)

set(CPPKAFKA_DISABLE_EXAMPLES ON CACHE INTERNAL "Turn off examples")
set(CPPKAFKA_DISABLE_TESTS ON CACHE INTERNAL "Turn off tests")

FetchContent_Declare(
    CppKafka
    GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
    GIT_TAG        v0.3.1
)

FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(librdkafka)
FetchContent_MakeAvailable(CppKafka)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(protobuf CONFIG REQUIRED)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/protobufs")

add_library(proto-objects OBJECT "${CMAKE_CURRENT_LIST_DIR}/protobufs/ohlc.proto")
target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf gRPC::grpc++)

target_include_directories(proto-objects PUBLIC ${PROTO_BINARY_DIR})#"$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET proto-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/protobufs"
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

protobuf_generate(
    TARGET proto-objects
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/protobufs"
    PROTOC_OUT_DIR "${CMAKE_CURRENT_LIST_DIR}")

file(GLOB OHLCService_SOURCES src/*.cpp)
file(GLOB Kafka_SOURCES src/kafka/*.cpp)
file(GLOB protobufs_SOURCES protofs/*.cc)

add_library(kafka ${Kafka_SOURCES})
target_include_directories(kafka PUBLIC include/kafka)
target_link_libraries(kafka PUBLIC  rdkafka cppkafka nlohmann_json::nlohmann_json)

add_library(libOHLCService ${OHLCService_SOURCES})
target_include_directories(libOHLCService PUBLIC include/ protobufs/ ${PROTO_HDRS})
target_link_libraries (libOHLCService PUBLIC proto-objects  rdkafka cppkafka nlohmann_json::nlohmann_json absl::base absl::strings ${Protobuf_LIBRARIES})

add_executable(OHLCService src/main.cpp)
target_include_directories(OHLCService PRIVATE include/)
target_link_libraries(OHLCService libOHLCService proto-objects ${Protobuf_LIBRARIES} rdkafka cppkafka nlohmann_json::nlohmann_json)

add_executable(OHLCProducer src/ohlc_producer.cpp)
target_include_directories(OHLCProducer PRIVATE include/)
target_link_libraries(OHLCProducer libOHLCService proto-objects ${Protobuf_LIBRARIES} rdkafka cppkafka kafka nlohmann_json::nlohmann_json)

add_executable(OHLCConsumer src/ohlc_consumer.cpp)
target_include_directories(OHLCConsumer PRIVATE include/)
target_link_libraries(OHLCConsumer libOHLCService proto-objects ${Protobuf_LIBRARIES} rdkafka cppkafka  kafka nlohmann_json::nlohmann_json) 
