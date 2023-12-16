#include <ohlcdatabase.hpp>

OHLCService::Database::OHLCDatabase::OHLCDatabase(std::string address) : mRedis(Redis(address))
{   
}

void OHLCService::Database::OHLCDatabase::InsertOHLC(std::string_view stock, OHLC ohlc)
{
    this->mRedis.rpush(stock, ohlc.SerializeAsString());
}

OHLCService::Response OHLCService::Database::OHLCDatabase::GetOHLC(std::string_view stock)
{
    Response response;

    OptionalString fetched = this->mRedis.get(stock); 

    response.ParseFromString(fetched.value());

    return response;
}

