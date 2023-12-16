#include <ohlcservice.hpp> 
#include <rpc/ohlcserver.hpp>
#include <memory>
#include <grpcpp/grpcpp.h>
#include <grpcpp/server.h> // Add this line
#include <grpcpp/server_builder.h> // Add this line
#include <sw/redis++/redis++.h>

using namespace OHLCService;
using namespace OHLCService::gRPC;

using namespace sw::redis;

void InitRedis(std::string address)
{
    auto redis = Redis(address);

    OHLC ohlc; 

    std::vector<std::string> stocks = {
        "TSLA", "AAPL", "GOOGL", "META"
    };

    for (auto stock : stocks)
    {
        ohlc.set_stock(stock);
        ohlc.set_period("2023....");
        ohlc.set_value(1000);
        ohlc.set_volume(100);
        ohlc.set_averageprice(10);
        
        redis.rpush(stock,  ohlc.SerializeAsString());
    }
}

int main(int argc, char** argv)
{
    InitRedis(argv[2]);
    OHLCServerImpl service = OHLCServerImpl(argv[2]);

    grpc::ServerBuilder builder;

    builder.AddListeningPort(argv[1], grpc::InsecureServerCredentials()); 
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Server listening on " << argv[1] << '\n';

    server->Wait();

    return 0;    
}
 