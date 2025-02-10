#ifndef Worker 
#define Worker
#include "../Node.h"
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <vector>

class WorkerServer : public NodeServer{
private:
    NodeClient node_client;
public:
    WorkerServer(std::string &folderPath,std::string &master_ipPort);
    ~WorkerServer() override;


    grpc::Status sendSignal(::grpc::ClientContext* context, const ::isReceived* request, ::isReceived* response);// To Recieve Start Signal
    grpc::Status sendNodeInfo(::grpc::ClientContext* context, const ::NodeInfo* request, ::isReceived* response);// Method is not required by worker is left un-implemented
    grpc::Status sendFileInfo(::grpc::ClientContext* context, const ::FileInfo* request, ::isReceived* response);


};
void RunWorker();
#endif
