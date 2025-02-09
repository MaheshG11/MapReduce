cmake_minimum_required(VERSION 3.30.3)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)


add_executable(MAPPER mapper_.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Mapper/Mapper.cpp)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}:~/.local:~/.local/bin:~/grpc:${CMAKE_SOURCE_DIR}")
target_link_libraries(MAPPER gRPC_Communication_Lib gRPC::grpc++)
target_include_directories(MAPPER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Mapper ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../../protofiles )