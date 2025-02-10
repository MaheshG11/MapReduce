#include "Mapper/Mapper.h"

class myTask:public mapper<std::string,int>{
    '''
    substitute string , int with some other datatype that you want as 
    key,value, note it must be a datatype which which can be used with
    cout<<key<<value;// and note this line must not be space seperated;
    '''
    myTask(std::string folderPath,std::string master_ipPort,int32_t mappers
        ,int32_t num_entries,std::string input_file_path):
        mapper(folderPath,master_ipPort,mappers,num_entries,input_file_path){}
    

        
    //again, replace the key value datatype here as well
    std::pair<std::string,int32_t> task() override{
        //complete this task and use 'file' insted of 'cin' for reading input from a file
        std::string s;
        file>>s;
        return {s,1};
    }


    // replace with datatype of key
    int32_t keyGenerator(std::string &key){
        int32_t ans=0;
        for(char i:key)ans+=(int32_t)i;
        return ans;
    }  
};

int main(int argc, char* argv[]){
    //args = folderPath,master_ipPort,mappers,num_entries,input_file_path
    // ignore these
    myTask taskOBJ(argv[1],argv[2],argv[3],argv[4],argv[5]);
    taskOBJ.start();
}