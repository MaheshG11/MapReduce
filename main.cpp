// #include <iostream>
// #include "masterNode.h"
// #include <grpcpp/grpcpp.h>
// #include <bits/stdc++.h>

// // using namespace std;




// int main(int argc, char** argv) {
// //argv
// //1 w/m Worker Node/Master Node
// //
// //  if(argc<2) {
// //   std::cout<<"Invalid input please inter S/s :Server or C/c :Client\n";
// //   return -1;
// //   }
// //  // string nodeType=argv[1];
// //  // if(nodeType=="W" or nodeType=="w")cout<<"This is a worker Node\n";
// //  // else if(nodeType=="M" or nodeType=="m")cout<<"This is a master Node\n";
// //  // else cout<<"Invalid input please inter W/w :worker or M/m :master\n";
// //  // cout<<nodeHandling::add(5,5)<<endl;;
// //  // makeCall temp;
// //  // grpc::ServerBuilder builder;
// //  // builder.AddListeningPort("0.0.0.0:9999", grpc::InsecureServerCredentials());
// //  // builder.RegisterService(&temp);
// //  // std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
// //  // server->Wait();
// //  std::string nodeType=argv[1];
// //  // std::cout<<"here\n";
// //  // std::cout<<nodeType<<'\n';
// //  if(nodeType=="s" or nodeType=="S"){
// //   std::cout<<"here\n";
// //   std::string ga="ga";
// //   CommunicationServiceServer server(ga);
// //   grpc::ServerBuilder builder;
// //   builder.AddListeningPort("0.0.0.0:50053",grpc::InsecureServerCredentials());
// //   builder.RegisterService(&server);
// //   std::unique_ptr<grpc::Server> sserver(builder.BuildAndStart());
// //   sserver->Wait();
// //  }
// //  // else {
// //  //  std::cout<<"here_\n";
// //  //  // CommunicationServiceClient client(grpc::CreateChannel("localhost:50053",
// //  //   // grpc::InsecureChannelCredentials()));
// //  //  // client.getFile(0,0,0,0);
// //  // } 


// }