#include <ohlcserver.hpp>

OHLCService::gRPC::OHLCServerImpl::OHLCServerImpl(std::string dbAddress) : mRedis(Redis(dbAddress))
{
}

grpc::Status OHLCService::gRPC::OHLCServerImpl::GetOHLCsByStock(grpc::ServerContext* context, 
                                                                const OHLCService::Request* request, 
                                                                OHLCService::Response* response) 
{
    OHLCService::OHLC* ohlc = response->add_ohlcs();

    StringView out;

    this->mRedis.hget(request->stock(), out);

    OHLC parsed;

    parsed.ParseFromString(out);

    ohlc->set_stock(parsed.stock());
    ohlc->set_period(parsed.period());
    ohlc->set_value(parsed.value());
    ohlc->set_volume(parsed.volume());
    ohlc->set_averageprice(parsed.averageprice());

    return grpc::Status::OK;
}
