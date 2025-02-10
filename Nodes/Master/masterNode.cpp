#include <iostream>
#include "../../protofiles/gRPC_Communication.grpc.pb.h"
#include "../../protofiles/gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include "../Node.h"
#include "masterNode.h"
#include <memory>
#include <fstream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>


MasterServer::MasterServer(std::string &folderPath,std::string &ipPort):
NodeServer(folderPath),ipPort(ipPort),workers(0),mappers(-1),reducers(-1),
stubs_lock(stubs_mtx,std::defer_lock),executing(false),completed(0),working(0)
{
    NodeInfoBuffer.reserve((int)100);
}
MasterServer::~MasterServer(){}
grpc::Status MasterServer::sendNodeInfo(::grpc::ClientContext* context, const ::NodeInfo* request, ::isReceived* response){
    // This function is used for registering the nodes with master    


    //TODO implement is ipPort valid check (as the assumption is that worker will always send correct data)
    std::unique_lock<std::mutex> lock1(this->executing_mtx);
    std::string ipPort=request->ipport(); 
    if(this->executing){
        std::unique_lock<std::mutex> lock(this->NodeInfoBuffer_mtx);
        this->NodeInfoBuffer.push_back(ipPort);
    }
    else{
        this->stubs_lock.lock();

        this->stubs[ipPort]=CommunicationService::NewStub(grpc::CreateChannel(ipPort,
                                    grpc::InsecureChannelCredentials()));
        this->workers++;
        this->stubs_lock.unlock();
    }
    response->set_received((int32_t)1);
    return grpc::Status::OK;
}
grpc::Status MasterServer::sendSignal(::grpc::ClientContext* context, const ::isReceived* request, ::isReceived* response){
    std::unique_lock<std::mutex> lock(this->completed_mtx);
    this->completed++;
    if(this->completed==this->working){
        this->working=0;
        this->completed=0;
        std::unique_lock<std::mutex> executing_lock(executing_mtx);
        this->executing = false;
        this->executing_cv.notify_one();
    }
    else if(this->completed==this->mappers){
        std::map<std::string,std::unique_ptr<CommunicationService::Stub>>::iterator it=(this->stubs).end();
        int reducers=(this->workers)-(this->mappers);
        isReceived response,request;
        request.set_received((int32_t)1);
        grpc::ClientContext context;
        grpc::Status status;
        while(reducers--){
            it--;
            status=(it->second)->sendSignal(&context,request,&response);
        }
    }
    return grpc::Status::OK;
}
void MasterServer::BroadcastFilePathToReducers(const ::FileInfo* request){
    std::map<std::string,std::unique_ptr<CommunicationService::Stub>>::iterator it=(this->stubs).end();
    int reducers=(this->workers)-(this->mappers);
    isReceived response;
    grpc::ClientContext context;
    grpc::Status status;
    while(reducers--){
        it--;
        status=(it->second)->sendFileInfo(&context,(*request),&response);
    }
}
int32_t MasterServer::getWorkers(){
    return this->workers;
}

grpc::Status MasterServer::sendFileInfo(::grpc::ClientContext* context, const ::FileInfo* request, ::isReceived* response){
    
    // TODO try to get BroadcastFilePathToReducers task in detached mode
    BroadcastFilePathToReducers(request);

    response->set_received((int32_t)1);
    return grpc::Status::OK;

}


void MasterServer::start(int32_t mappers,int32_t reducers){   
    std::cout<<"Setting up...\n";
    this->executing=true;
    this->mappers=mappers;
    this->reducers=reducers;
    this->working=mappers+reducers;
    grpc::ClientContext context;
    isReceived request,response;
    
    
    grpc::Status status;
    // executing_lock.lock();
    stubs_lock.lock();
    std::map<std::string,std::unique_ptr<CommunicationService::Stub
        >>::iterator it=(this->stubs).end();
    while(reducers--){
        it--;
        request.set_received(-reducers);
        status=(it->second)->sendSignal(&context,request,&response);   
        // start Execution Reducers
    }
    it=(this->stubs).begin();
    request.set_received(this->reducers);
    while(mappers--){
        status=(it->second)->sendSignal(&context,request,&response);
        // start Execution Mappers
        it++;
    }
    stubs_lock.unlock();
    std::cout<<"Executing....\n";
    std::unique_lock<std::mutex> executing_lock(executing_mtx);
    // Wait until 'executing' becomes false
    executing_cv.wait(executing_lock, [this]{ return !executing; });

    std::cout<<"Execution Finished\n";
   
}
void RunMasterServer(std::string &ipPort,MasterServer &ServerImplementation){
    grpc::ServerBuilder builder;
    builder.AddListeningPort(ipPort,grpc::InsecureServerCredentials());
    builder.RegisterService(&ServerImplementation);
    std::unique_ptr<grpc::Server> master_server(builder.BuildAndStart());
    std::cout<<"started Master Server at : "<<getLocalIP()<<"\nWith this setting on Machine : "<<ipPort<<'\n';
    while(true){
        std::cout<< "Enter \'1\' to start execution of the Process\n";
        // std::cout<<"Enter \'2\' to Change ipPort\n"; TODO
        // std::cout<<"Enter \'3\' to Change folderPath\n"; TODO
        std::cout<<"Enter any other number to exit\n";
        int op;
        std::cin>>op;
        int workers=ServerImplementation.getWorkers();
        if(op==1){
            std::cout<<"The Number of Workers are : "<<workers
            <<"\nEnter number of Mappers and Reducers :\n";
            int mappers,reducers;
            std::cin>>mappers>>reducers;
            if(mappers+reducers<=workers){
                std::cout<<"number of mappers+reducers greater than workers";
                continue;
            }
            std::cout<<"No changes will be allowed during Execution";
            ServerImplementation.start(mappers,reducers);


        }
        else return;
    }
}
void RunMaster(){
    std::string ipPort,folderPath;
    std::cout<<"enter IP address and port number like this <IP address:Port Number> (e.g., 0.0.0.0:8003)\n";
    std::cout<<"Enter folderPath where Mapper and Reducer Code is present\n";
    std::cin>>ipPort>>folderPath;
    MasterServer ServerImplementation(folderPath,ipPort);

}