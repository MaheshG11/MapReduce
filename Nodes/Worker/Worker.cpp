#include "../Node.h"
#include <iostream>
#include "../../protofiles/gRPC_Communication.grpc.pb.h"
#include "gRPC_Communication.pb.h"
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <memory>
#include "Worker.h"
#include <vector>
#include <cstdlib> 
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
extern char **environ; 
WorkerServer::WorkerServer(std::string &folderPath,std::string &master_ipPort):
NodeServer(folderPath),node_client(folderPath,master_ipPort){
    node_client.sendNodeInfo();
}
WorkerServer::~WorkerServer(){}
grpc::Status WorkerServer::sendSignal(::grpc::ClientContext* context, 
const ::isReceived* request, ::isReceived* response){
    int32_t type=request->received();
    std::string filePath="/project/Nodes/Worker";
    if(type>0){
        //Mapper
        std::string filePath_=node_client.folderPath+"/mapper_.cpp";
        node_client.getFile((int64_t)0,"mapper.cpp","","",node_client.master_stub,
        filePath_);
        std::string command = "cmake -S"+filePath+" -B "+filePath+"/build ";
        system(command.c_str());
        pid_t pid;
        char *args[] = {"/project/Nodes/Worker/build/MAPPER",NULL};  // Binary path & args
        posix_spawn(&pid,args[0],NULL,NULL,args,environ);
        waitpid(pid, NULL, 0); 
    }
    else{
        //Reducer
        filePath=node_client.folderPath+"/reducer_.cpp";
        node_client.getFile((int64_t)0,"reducer.cpp","","",node_client.master_stub,
        filePath);
    }
    
    // std::string command = "g++ -fPIC -shared " + filePath + " -o "+filePath+".so";
    // system(command.c_str());
    // filepath+=".so";
    // void* handle=dlopen(filepath, RTLD_NOW);
    

}