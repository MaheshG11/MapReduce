// #include <algorithm>
#include "Node.h"
#include <iostream>
#include "gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <vector>




// Server Code

// Constructor
NodeServer::NodeServer(std::string &folderPath)folderPath(folderPath) {
}
// Destructor
NodeServer::~NodeServer() {
}
grpc::Status NodeServer::getFile(grpc::ServerContext* context, 
 const FileRequest* fileRequest,
 grpc::ServerWriter<FileChunk>* writer){
 std::string fileName=fileRequest->filename(),extension=fileRequest->extension(),task=fileRequest->task();
 int64_t startFrom=fileRequest->startfrom();
 std::string filePath=folderPath+task+"/"+fileName+extension;
 FileChunk chunk;
 char buffer[1024*(this->data_transfer_rate)];// there is some error when trying variable sized array(tried using vector), also this is a const value
 std::ifstream file(filePath,std::ios::binary);
 if (!file.is_open()) {
  std::cout<<filePath<<'\n';
  return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found");
 }
 file.seekg(startFrom*(this->data_transfer_rate));
 while(file.read(buffer,sizeof(buffer)) || file.gcount()>0){
  chunk.set_data(buffer,file.gcount());
  chunk.set_chunk_number(startFrom);
  chunk.set_size(file.gcount());
  writer->Write(chunk);
  startFrom++;
 }
 return grpc::Status::OK;
}
void NodeServer::setFolderPath(std::string &folderpath){
  this->folderPath=folderpath;
}


//Client Code
NodeClient::NodeClient(std::string &folderPath)
{
 this->folderPath=folderPath;
}


void NodeClient::addStub(std::string ipPort){
  (this->stubs)[ipPort]=CommunicationService::NewStub(grpc::CreateChannel(ipPort,
   grpc::InsecureChannelCredentials()));
}


void NodeClient::getFile(int64_t startFrom,std::string fileName,std::string task,std::string,std::string extension,std::string ipPort,std::string filePath){
 FileRequest request;
 grpc::ClientContext context;
 FileChunk chunk;
 request.set_filename(fileName);
 request.set_task(task);
 request.set_extension(extension);
 request.set_startfrom(startFrom);
 std::ofstream file(filePath, std::ios::out | std::ios::binary); 
 std::unique_ptr<grpc::ClientReader<FileChunk>> reader(stubs[ipPort]->getFile(&context,request));
 while(reader->Read(&chunk)){
  file.write(chunk.data().data(),chunk.size());
 }
 grpc::Status status = reader->Finish();
  if (status.ok()) {
      std::cout << "ListFeatures rpc succeeded." << std::endl;
    }
    else {
      std::cerr<<status.error_message()<<'\n';
      std::cerr << "ListFeatures rpc failed." << std::endl;
    }

}

void NodeClient::setFolderPath(std::string &folderpath){
  this->folderPath=folderpath;
}

// // Method Implementation
// ::grpc::Status makeCall::makeSomeRpcCall(::grpc::ServerContext* context, 
//                                          const ::someMessage* request, 
//                                          ::someOtherMessage* response) {
//     std::cout << "RPC method called\n";
//     response->set_data(request->name());
//     return grpc::Status::OK;
// }

std::string getLocalIP() {
  struct ifaddrs *interfaces = nullptr;
  struct ifaddrs *ifa = nullptr;
  char ip[INET_ADDRSTRLEN];
  if (getifaddrs(&interfaces) == -1) {
   return ""; // Error retrieving interfaces
  }
  // Loop through the list of interfaces
  for (ifa = interfaces; ifa != nullptr; ifa = ifa->ifa_next) {
   // Check for IPv4 address and non-loopback interfaces
   if (ifa->ifa_addr->sa_family == AF_INET && 
    !(ifa->ifa_flags & IFF_LOOPBACK)) {
    struct sockaddr_in *sa_in = reinterpret_cast<struct sockaddr_in *>(ifa->ifa_addr);
    inet_ntop(AF_INET, &(sa_in->sin_addr), ip, INET_ADDRSTRLEN);
    freeifaddrs(interfaces);
    return std::string(ip); // Return the first valid IP address
   }
  }
  freeifaddrs(interfaces);
  return ""; // No valid IP address found 
 }