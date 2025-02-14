add_library(Master STATIC Master/masterNode.cpp 
Node.cpp
)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
target_link_libraries(Master gRPC_Communication_Lib gRPC::grpc++)
target_include_directories(Master PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/protofiles ${PROJECT_SOURCE_DIR}/Nodes ${PROJECT_SOURCE_DIR}/Nodes/Master)


# Worker

# target_include_directories(protoCommunicationLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )# CMAKE_CURRENT_BINARY_DIR refers to where build is taking place
add_library(Worker STATIC
Worker/Worker.cpp Node.cpp # Worker/Mapper/mapper.cpp  # Worker/Reducer/reducer.cpp
)
target_link_libraries(Worker gRPC_Communication_Lib gRPC::grpc++)

target_include_directories(Worker PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/protofiles ${PROJECT_SOURCE_DIR}/Nodes ${PROJECT_SOURCE_DIR}/Nodes/Worker ${PROJECT_SOURCE_DIR}/Nodes/Worker/Reducer ${PROJECT_SOURCE_DIR}/Nodes/Worker/Mapper)

