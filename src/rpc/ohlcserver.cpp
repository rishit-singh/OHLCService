#include <ohlcserver.hpp>

grpc::Status OHLCService::gRPC::OHLCServerImpl::GetOHLCsByStock(grpc::ServerContext* context, 
                                                                const OHLCService::Request* request, 
                                                                OHLCService::Response* response) 
{
    OHLCService::OHLC* ohlc = response->add_ohlcs();
    ohlc->set_stock("TSLA");
    ohlc->set_period("2023....");
    ohlc->set_value(1000);
    ohlc->set_volume(100);
    ohlc->set_averageprice(10);

    return grpc::Status::OK;
}
