#ifndef OHLCSERVER_H
#define OHLCSERVER_H

#include <ohlc.grpc.pb.h>
#include <sw/redis++/redis++.h> 

namespace OHLCService::gRPC
{
    using namespace sw::redis;
    
    /// @brief OHLCServer RPC service implementation
    class OHLCServerImpl final : public OHLCServer::Service
    {
    private:
        Redis mRedis;

    public:
        grpc::Status GetOHLCsByStock(grpc::ServerContext* context, const Request* request, Response* response) override;

        OHLCServerImpl(const std::string);
    };
}

#endif
 
