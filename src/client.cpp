#include <grpcpp/grpcpp.h>
#include <rpc/ohlcserver.hpp>
#include <ohlcservice.hpp>
#include <string>
#include <memory>

using namespace OHLCService;

class OHLCClient
{   
private:
    grpc::ClientContext mClient;

    grpc::ChannelArguments mChannelArgs;

    std::shared_ptr<grpc::Channel> mChannel; 

    std::unique_ptr<OHLCServer::Stub> mStub;

public:
    void Connect(std::string);

    OHLC GetOHLCsByStock(std::string);

    OHLCClient();
};

OHLCClient::OHLCClient() : mChannel(nullptr), mStub(nullptr) 
{
}

void OHLCClient::Connect(std::string address)
{
    if (address.empty())
        throw std::runtime_error("Invalid address provided");

    this->mChannel = grpc::CreateCustomChannel(address, grpc::InsecureChannelCredentials(), this->mChannelArgs);
    this->mStub = OHLCServer::NewStub(this->mChannel);
}

OHLC OHLCClient::GetOHLCsByStock(std::string stock)
{
    OHLC response;

    OHLCService::Request request;

    request.set_stock(stock); 

    grpc::Status status = this->mStub->GetOHLCByStock(&this->mClient, request, &response);

    return response;
} 

int main(int argc, char** argv)
{
    // grpc::ChannelArguments args;

    // std::shared_ptr<grpc::Channel> channel = grpc::CreateCustomChannel(argv[1], grpc::InsecureChannelCredentials(), args);

    // std::unique_ptr<OHLCServer::Stub> stub = OHLCServer::NewStub(channel);

    // OHLCService::Request request;

    // request.set_stock("TSLA");

    // OHLCService::OHLC response;

    // grpc::ClientContext client;

    // grpc::Status status = stub->GetOHLCByStock(&client,  request, &response);
         
    OHLCClient client;

    client.Connect(argv[1]);

    OHLC response = client.GetOHLCsByStock(argv[2]);

    std::cout
        << "Payload: OHLC(Stock=" << response.stock()
        << ", Period=" << response.period()
        << ", Value=" << response.value()
        << ", Volume=" << response.volume()
        << ", AvgPrice=" << response.averageprice()
        << ");" 
        << '\n'; 

    return 0;    
}