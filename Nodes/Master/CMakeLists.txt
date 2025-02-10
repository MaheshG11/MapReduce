# target_include_directories(protoCommunicationLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )# CMAKE_CURRENT_BINARY_DIR refers to where build is taking place
add_library(Master STATIC masterNode.cpp)
target_link_libraries(Master gRPC_Communication_Lib gRPC::grpc++)
target_include_directories(Master PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/protofiles ${PROJECT_SOURCE_DIR}/Nodes ${PROJECT_SOURCE_DIR}/Nodes/Master)