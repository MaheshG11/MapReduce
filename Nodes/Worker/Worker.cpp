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

#include <dlfcn.h>
extern char **environ; 


WorkerServer::WorkerServer(std::string &folderPath,std::string &master_ipPort):
NodeServer(folderPath),node_client(folderPath,master_ipPort),isBusy_lock(isBusy_mtx,std::defer_lock),
file_lock(file_mtx,std::defer_lock),completed((int32_t)0){
    node_client.sendNodeInfo();
}
WorkerServer::~WorkerServer(){}

void WorkerServer::keepBusy(){
    while(true){
        isBusy_lock.lock();
        '''
           use getFile to get the file which container K V pairs. 
        '''
        std::string filePath=fileInfoBuffer.back().first,ipPort=fileInfoBuffer.back().second;
        this->fileInfoBuffer.pop_back();
        isBusy_lock.unlock();
        node_client.getFile(0,filePath,"","","",this->getStub(ipPort),filePath);
        file_lock.lock();
        fileBuffer.push_back(filePath);
        file_cv.notify_one();
        file_lock.unlock();
    }
}
void WorkerServer::reducer_func(std::string &path,std::map<std::string,int32_t> &mpp){
    std::ifstream file(path.c_str());
    while(file.peek() != EOF){
        std::string s;
        file>>s;
        mpp[s]++;
    }
} 
grpc::Status WorkerServer::sendSignal(::grpc::ClientContext* context, 
const ::isReceived* request, ::isReceived* response){
    this->completed++;
    if(this->completed==2){
        (this->node_client).sendSignal();
        return grpc::Status::OK;
    }
    int32_t type=request->received();
    std::string filePath="/project/Nodes/Worker";
    if(type>0){
        //Mapper
        int n_r=type; // number of reducers
        std::string filePath_=node_client.folderPath+"/mapper_.cpp";
        node_client.getFile((int64_t)0,"mapper.cpp","","",node_client.master_stub,
        filePath_);
        std::string command = "cmake -S"+filePath+" -B "+filePath+"/build ";
        system(command.c_str());
        pid_t pid;

        // proper arguments are remaining
        char *args[] = {"/project/Nodes/Worker/build/MAPPER",NULL};  // Binary path & args
        posix_spawn(&pid,args[0],NULL,NULL,args,environ); // this is like fork() + exec() but without the copying of the entire process
        waitpid(pid, NULL, 0); 
    }
    else{
        //Reducer
        // int r_id=-type;// reducer id
        // filePath=node_client.folderPath+"/reducer_.cpp";
        // node_client.getFile((int64_t)0,"reducer.cpp","","",node_client.master_stub,
        // filePath);
        // std::string command="g++ -fPIC -shared /project/Nodes/Worker/reducer_.cpp -o /project/Nodes/Worker/reducer_.so";
        // system(command.c_str());
        // command="/project/Nodes/Worker/reducer_.so";
        // void *handle=dlopen(command,RTLD_NOW);
        // using ReducerFuncType = void(*)(std::string&, std::map<std::string, int32_t>&);
        // ReducerFuncType reducer_func=(ReducerFuncType)dlsym(handle,"reducer_func");
        this->r_id=-type;// reducer id
        std::map<std::string,int32_t> mpp;
        while(true){
            (this->file_lock).lock();
            if((this->completed)==2 and (this->file_buffer).size()){
                this->file_lock.unlock();
                break;
            }
            file_cv.wait(file_lock,[this]{return file_buffer.size()>zero});
            std::string path=(this->file_buffer).back();
            file_buffer.pop_back();
            file_lock.unlock();
            this->reducer_func(path,mpp);
        }
    }
    (this->node_client).sendSignal();
    this->completed=0;
    return grpc::Status::OK;

}
grpc::Status WorkerServer::sendFileInfo(::grpc::ClientContext* context, const ::FileInfo* request, ::isReceived* response){
    std::string filePath=request->filepath();
    std::string ipPort=request->ipport();
    this->isBusy_lock.lock();
    (this->fileInfoBuffer).push_back({filePath+std::stoi(this->r_id)+".txt",ipPort});
    this->isBusy_lock.unlock();
    response->set_received((int32_t)1);
    return grpc::Status::OK;
}
