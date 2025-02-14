#ifndef MAPPER
#define MAPPER
#include <iostream>
#include "protofiles/gRPC_Communication.grpc.pb.h"
#include "protofiles/gRPC_Communication.pb.h"
#include <grpcpp/grpcpp.h>
#include "Node.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>
#include<bits/stdc++.h>
template <class K,class V>
class mapper:public NodeClient{
    private: 
        std::vector<std::unique_ptr<std::vector<std::pair<K,V>>> > writer_buffer;
        std::mutex isBusy_mtx;
        std::condition_variable isBusy_cv;
        std::unique_lock<std::mutex> isBusy_lock;
        int32_t completed;
        void keepBusy();
    public:
        std::ifstream file;
        int32_t mappers,f_number,num_entries;
        mapper(std::string folderPath,std::string master_ipPort,int32_t mappers,int32_t num_entries,std::string input_file_path);
        virtual int32_t keyGenerator(K &key)=0;
        void writer(std::unique_ptr<std::vector<std::pair<K,V>>>&& map_ptr,int32_t f_number);
        virtual std::pair<K,V> task()=0;

        void start();
};
#endif