protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=$HOME/.local/bin/grpc_cpp_plugin gRPC_Communication.proto
protoc -I . --cpp_out=. gRPC_Communication.proto