#ifndef Node
#define Node
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>
#include <fstream>
#include <vector>

// const std::string folderPath;
//Server
class NodeServer : public CommunicationService :: Service{
 private:
  static const int data_transfer_rate=16;// file transfer rate In kilobytes
  std::string folderPath;
  
 public:
  NodeServer(std::string &folderPath);
  ~NodeServer() override;
  ::grpc::Status getFile(::grpc::ServerContext* context, const ::FileRequest* request, ::grpc::ServerWriter< ::FileChunk>* writer)override;
  void setFolderPath(std::string &folderpath);
};

//Client
class NodeClient {
 private:
  std::map<std::string,std::unique_ptr<CommunicationService::Stub>> stubs;
  std::string folderPath;
 public:
  NodeClient(std::string &folderPath);
  void addStub(std::string ipPort); 
  void setFolderPath(std::string &folderpath);
  void getFile(int64_t startFrom,std::string fileName,std::string task,std::string,std::string extension,std::string ipPort,std::string filePath);
};

std::string getLocalIP();
#endif
