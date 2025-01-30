
#ifndef Master
#define Master
#include <iostream>
#include "../../protofiles/gRPC_Communication.grpc.pb.h"
#include "../../protofiles/gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include "../Node.h"
#include <memory>
#include <fstream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>

// const std::string folderPath;
//Server
class MasterServer : public NodeServer{
 private:
  // static const int data_transfer_rate=16;// In kilobytes
  std::string ipPort;
  std::map<std::string,std::unique_ptr<CommunicationService::Stub>> stubs;
  std::vector<std::string> NodeInfoBuffer;
  int workers,mappers,reducers,completed,working;
  std::mutex executing_mtx,stubs_mtx,completed_mtx,workers_mtx,NodeInfoBuffer_mtx;
  std::unique_lock<std::mutex> stubs_lock;
  std::condition_variable executing_cv;
  bool executing;
  void BroadcastFilePathToReducers(std::string &filePath);
 public:
  MasterServer(std::string &folderPath,std::string &ipPort);
  ~MasterServer() override;
  grpc::Status sendNodeInfo(::grpc::ClientContext* context, const ::NodeInfo* request, ::isReceived* response);
  grpc::Status sendFileInfo(::grpc::ClientContext* context, const ::FileInfo* request, ::isReceived* response);
  grpc::Status sendSignal(::grpc::ClientContext* context, const ::isReceived* request, ::isReceived* response);
  int getWorkers();
  
  void start(int mappers,int reducers);
};

void RunMasterServer(std::string &folderPath,std::string &ipPort);
void RunMaster();
//Client
class CommunicationServiceClient {
 public:
  void addStub(std::string ipPort); 
  void setFolderPath(std::string &folderpath);
  void getFile(int64_t startFrom,std::string fileName,std::string task,std::string,std::string extension,std::string ipPort,std::string filePath);
};



#endif
