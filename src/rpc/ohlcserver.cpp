#include <ohlcserver.hpp>

grpc::Status OHLCService::gRPC::OHLCServerImpl::GetOHLCByStock(grpc::ServerContext* context, 
                                                                const OHLCService::Request* request, 
                                                                OHLCService::OHLC* response) 
{
    response->set_stock("TSLA");
    response->set_period("2023....");
    response->set_value(1000);
    response->set_volume(100);
    response->set_averageprice(10);

    return grpc::Status::OK;
}
