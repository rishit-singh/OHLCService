#include <ohlcservice.hpp> 
#include <rpc/ohlcserver.hpp>
#include <memory>
#include <grpcpp/grpcpp.h>
#include <grpcpp/server.h> // Add this line
#include <grpcpp/server_builder.h> // Add this line

using namespace OHLCService;
using namespace OHLCService::gRPC;

int main(int argc, char** argv)
{
    OHLCServerImpl service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(argv[1], grpc::InsecureServerCredentials()); 
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Server listening on " << argv[1] << '\n';

    server->Wait();

    return 0;    
}
 