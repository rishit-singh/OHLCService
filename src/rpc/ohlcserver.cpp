#include <ohlcserver.hpp>

OHLCService::gRPC::OHLCServerImpl::OHLCServerImpl(std::string dbAddress) : mRedis(Redis(dbAddress))
{
}

grpc::Status OHLCService::gRPC::OHLCServerImpl::GetOHLCsByStock(grpc::ServerContext* context, 
                                                                const OHLCService::Request* request, 
                                                                OHLCService::Response* response) 
{
    std::vector<std::string> fetched;
    
    this->mRedis.lrange(request->stock(), 0, -1, std::back_inserter(fetched));

    for (auto ohlcStr : fetched)
    {
        OHLC o;

        o.ParseFromString(ohlcStr);

        OHLCService::OHLC* ohlc = response->add_ohlcs();

        ohlc->set_stock(o.stock());
        ohlc->set_period(o.period());
        ohlc->set_value(o.value());
        ohlc->set_volume(o.volume());
        ohlc->set_averageprice(o.averageprice());
    }

    return grpc::Status::OK;
}
