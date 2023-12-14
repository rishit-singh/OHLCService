#ifndef OHLCSERVICE_H
#define OHLCSERVICE_H 

#include <util.hpp>
#include <ohlc.pb.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string_view> 
#include <fstream>
#include <filesystem>
#include <iostream>

using json = nlohmann::json;

namespace OHLCService
{
    struct Transaction
    {
        size_t Quantity;

        size_t Price;

        Transaction(size_t, size_t );
    };

    /// @brief Helper class for generating and managing OHLCs
    class OHLCGenerator
    {     
    private:
        /// @brief Generated OHLCs
        std::vector<OHLC> OHLCs;

        /// @brief Loaded transactions
        std::map<const std::string_view, std::vector<Transaction>> Transactions;
    public:
        /// @brief Loads the transactions from the ndjson files in the given path
        /// @param path Path to transaction period files 
        void LoadTransactions(const std::filesystem::path);
        
        /// @brief Generates OHLCs from the loaded transactions
        /// @return Copy of generated OLCS
        std::vector<OHLC> GenerateOHLCs();  

        /// @brief Gets the transactions from the given period
        /// @param period Transaction period  
        /// @return Fetched transactions.
        std::vector<Transaction> GetTransactions(const std::string_view); 
        
        /// @brief Getter for OHLCs 
        /// @return OHLCs
        std::vector<OHLC> GetOHLCs(); 

        OHLCGenerator() = default;
        ~OHLCGenerator() = default;
    };
};

#endif