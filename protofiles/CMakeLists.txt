add_library(gRPC_Communication_Lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/gRPC_Communication.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gRPC_Communication.grpc.pb.cc
)
target_link_libraries(gRPC_Communication_Lib PUBLIC protobuf::libprotobuf gRPC::grpc++)
target_include_directories(gRPC_Communication_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
