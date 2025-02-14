#include <iostream>
#include "protofiles/gRPC_Communication.grpc.pb.h"
#include "protofiles/gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include <vector>
#include "Mapper.h"

#include <map> 
constexpr int32_t zero=0;
template<class K, class V>
mapper<K,V>::mapper(std::string folderPath,std::string master_ipPort,int32_t mappers,int32_t num_entries,std::string input_file_path):
NodeClient(folderPath,master_ipPort),mappers(mappers),f_number(zero),
num_entries(num_entries),isBusy_lock(isBusy_mtx,std::defer_lock),file(input_file_path)
{}

template<class K, class V>
void mapper<K,V>::keepBusy(){
    while(true){
        isBusy_lock.lock();
        isBusy_cv.wait(isBusy_lock,[this]{return writer_buffer.size()>zero;});
        std::unique_ptr<std::vector<std::pair<K,V>>> map_ptr=std::move(writer_buffer.back());
        writer_buffer.pop_back();
        isBusy_lock.unlock();        
        writer(std::move(map_ptr),f_number++);
        isBusy_lock.lock();
        if(completed && writer_buffer.size()==zero){
            isBusy_lock.unlock();
            break;
        }
        isBusy_lock.unlock();
    }
}

template<class K, class V>
void mapper<K,V>::writer(std::unique_ptr<std::vector<std::pair<K,V>>>&& map_ptr,int32_t f_number){
    if(!map_ptr){
        throw std::runtime_error("Map pointer is null");
    }
    // std::sort(map_ptr->begin(),map_ptr->end());
    int32_t mappers=this->mappers;
    std::string path_=this->folderPath+"/"+std::to_string(f_number)+"_";
    std::vector<std::ofstream> files;
    for(int32_t i=zero;i<mappers;i++)
        files.emplace_back(path_+std::to_string(i)+".txt");
    
    for(auto &[key,value]:(*map_ptr)){
        files[(this->keyGenerator(key))%mappers]<<key<<" "<<value<<'\n';
    }
    for(auto &file : files)file.close();
    this->sendFileInfo(path_);
}

template<class K, class V>
void mapper<K,V>::start(){
    std::thread keepBusyThread(keepBusy);
    keepBusyThread.detach();
    std::unique_ptr<std::vector<std::pair<K,V>>> map_ptr=std::make_unique<std::vector<std::pair<K,V>>>();
    while(file.peek() != EOF){
        map_ptr->push_back(task());
        if((map_ptr->size())>num_entries){
            isBusy_lock.lock();
            writer_buffer.push_back(std::move(map_ptr));
            isBusy_cv.notify_one();
            isBusy_lock.unlock();
        }
    }
    
    isBusy_lock.lock();
    writer_buffer.push_back(std::move(map_ptr));
    completed=1;
    isBusy_cv.notify_one();
    isBusy_lock.unlock();
    
    keepBusyThread.join();
}