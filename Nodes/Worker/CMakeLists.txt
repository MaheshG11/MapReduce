cmake_minimum_required(VERSION 3.30.3)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(MAPPER  mapper_.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../Node.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Mapper/Mapper.cpp )
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}:~/.local:~/.local/bin:~/grpc:${CMAKE_SOURCE_DIR}")
target_link_libraries(MAPPER ${CMAKE_CURRENT_SOURCE_DIR}/../../out/build/protofiles/libgRPC_Communication_Lib.a gRPC::grpc++)
target_include_directories(MAPPER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Mapper ${CMAKE_CURRENT_SOURCE_DIR}/../../ ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../../protofiles )
# include_directories(/project)