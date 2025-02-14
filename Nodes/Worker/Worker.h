#ifndef Worker 
#define Worker
#include "../Node.h"
#include <iostream>
#include "protofiles/gRPC_Communication.grpc.pb.h"
#include "protofiles/gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include <fstream>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
class WorkerServer : public NodeServer{
private:
    NodeClient node_client;
    std::mutex isBusy_mtx,file_mtx;
    std::condition_variable isBusy_cv,file_cv;
    std::unique_lock<std::mutex> isBusy_lock,file_lock;
    void keepBusy();
    int32_t r_id,completed;
    std::vector<std::pair<std::string,std::string>>fileInfoBuffer;// filePath,ipPort
    std::vector<std::string> fileBuffer;
public:
    
    WorkerServer(std::string &folderPath,std::string &master_ipPort);
    ~WorkerServer() override;

    void reducer_func(std::string &path,std::map<std::string,int32_t> &mpp);
    grpc::Status sendSignal(::grpc::ClientContext* context, const ::isReceived* request, ::isReceived* response);// To Recieve Start Signal
    grpc::Status sendNodeInfo(::grpc::ClientContext* context, const ::NodeInfo* request, ::isReceived* response);// Method is not required by worker is left un-implemented
    grpc::Status sendFileInfo(::grpc::ClientContext* context, const ::FileInfo* request, ::isReceived* response);


};
void RunWorker();
#endif
