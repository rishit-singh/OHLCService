#ifndef OHLCSERVER_H
#define OHLCSERVER_H

#include <ohlc.grpc.pb.h>

namespace OHLCService::gRPC
{
    /// @brief OHLCServer RPC service implementation
    class OHLCServerImpl final : public OHLCServer::Service
    {
        grpc::Status GetOHLCsByStock(grpc::ServerContext* context, const Request* request, Response* response) override;
    };
}

#endif
 
