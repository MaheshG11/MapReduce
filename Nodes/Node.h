#ifndef Node
#define Node
#include <iostream>
#include "protofiles/gRPC_Communication.grpc.pb.h"
#include "protofiles/gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>
#include <fstream>
#include <vector>
#include <ifaddrs.h>
#include <net/if.h>

#include <netinet/in.h>
#include <arpa/inet.h>
// const std::string folderPath;
//Server
class NodeServer : public CommunicationService :: Service{
 private:
  static const int data_transfer_rate=16;// file transfer rate In kilobytes
  std::string folderPath;
  
 public:
  NodeServer(std::string &folderPath);
  ~NodeServer() override;
  ::grpc::Status getFile(::grpc::ServerContext* context, const ::FileRequest* 
                  request, ::grpc::ServerWriter< ::FileChunk>* writer)override;

  void setFolderPath(std::string &folderpath);
};

//Client
class NodeClient {
  private:
  std::unordered_map<std::string,std::unique_ptr<CommunicationService::Stub>> stubs;
  
 public:
  bool sendNodeInfo();// Will register/subscribe this worker with master 
  std::string folderPath;
  std::string master_ipPort,ipPort;
  std::unique_ptr<CommunicationService::Stub> master_stub;

  void setFolderPath(std::string &folderpath);
  NodeClient(std::string &folderPath,std::string master_ipPort);
  std::unique_ptr<CommunicationService::Stub>& getStub(std::string &ipPort);
  void getFile(int64_t startFrom,std::string fileName,std::string task,
  std::string extension,std::unique_ptr<CommunicationService::Stub>& stub,std::string& filePath);
  bool sendFileInfo(std::string &filePath);
  bool sendSignal();
};

std::string getLocalIP();
#endif
