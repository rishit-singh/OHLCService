#ifndef OHLCSERVER_H
#define OHLCSERVER_H

#include <ohlc.grpc.pb.h>

namespace OHLCService::gRPC
{
    class OHLCServerImpl final : public OHLCServer::Service
    {
        grpc::Status GetOHLCByStock(grpc::ServerContext* context, const Request* request, OHLC* response) override;
    };
}

#endif
 
