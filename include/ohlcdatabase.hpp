#include <ohlcservice.hpp> 
#include <string_view>
#include <sw/redis++/redis++.h>

namespace OHLCService::Database
{   
    using namespace sw::redis;
    
    /// @brief Redis database wrapper
    class OHLCDatabase
    {
    private:
        /// @brief Redis instance
        Redis mRedis;

    public:
        /// @brief Inserts an OHLC at the given stock key
        /// @param key Key to insert at
        /// @param ohlc OHLC to insert
        void InsertOHLC(std::string_view stock, OHLC ohlc);

        /// @brief Gets the OHLCs of the given stock
        /// @param stock Stock to get the OHLCs of
        /// @return Fetched OHLCs inside a gRPC compatible Request
        Response GetOHLC(std::string_view stock);

        OHLCDatabase(std::string address);
    };
}

