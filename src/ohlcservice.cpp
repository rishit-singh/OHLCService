#include <ohlcservice.hpp>


OHLCService::Transaction::Transaction(std::string stock, size_t quantity, size_t price)
    : Stock(stock), Quantity(quantity), Price(price)
{
}

size_t OHLCService::OHLCGenerator::GetVolume(const std::vector<Transaction>& transactions)
{
    size_t volume = 0; 

    for (auto t : transactions)
        volume += t.Quantity;

    return volume;
}

size_t OHLCService::OHLCGenerator::GetValue(const std::vector<Transaction>& transactions)
{
    size_t value = 0; 

    for (auto t : transactions)
        value += (t.Quantity * t.Price);

    return value;
}

std::vector<OHLCService::OHLC> OHLCService::OHLCGenerator::GenerateOHLCs()
{
    OHLCService::OHLC ohlc;

    std::unordered_map<std::string, std::vector<Transaction>> transactionMap;

    for (auto const& [key, val] : this->Transactions) // for each period
    { 
        for (auto t : val) // for each transaction in the period
        {
            if (!transactionMap.contains(t.Stock))
                transactionMap[t.Stock] = {};
            
            transactionMap[t.Stock].push_back(t); // segregate transactions by stock
        }

        for (auto const& [stockKey, transactions] : transactionMap) // for each stock in the period
        {
            for (auto t : transactions) // for each transaction in stock
            {
                ohlc.set_period(key);
                ohlc.set_stock(stockKey);
                ohlc.set_value(this->GetValue(transactions));
                ohlc.set_volume(this->GetVolume(transactions));
                
                if (!ohlc.value() && !ohlc.volume())
                    continue;

                ohlc.set_averageprice(ohlc.value() / ohlc.volume());
                
                this->OHLCs.push_back(ohlc);
                
                ohlc = OHLC();
            }
        }

        transactionMap.clear();
    }

    return this->OHLCs;
}

std::vector<OHLCService::OHLC> OHLCService::OHLCGenerator::GetOHLCs()
{
    return this->OHLCs;
}

std::vector<OHLCService::Transaction> OHLCService::OHLCGenerator::GetTransactions(const std::string period)
{
    return this->Transactions.at(period);
} 

void OHLCService::OHLCGenerator::LoadTransactions(const std::filesystem::path path)
{
    auto dirIt = std::filesystem::directory_iterator{path};

    for (auto entry : dirIt)
        if (entry.is_regular_file())
        {
            std::string line, path, period;

            std::ifstream stream(path = entry.path());

            std::vector<Transaction> transactions;

            period = *(Util::Split((*(Util::Split(path, '/').end() - 1)), '.').begin());

            while (!stream.eof())
            {
                json transaction;

                std::getline(stream, line);

                size_t quantity = 0, price = 0;

                std::string stock;

                try
                {
                    transaction = json::parse(line);
                   
                    if (transaction.contains("quantity"))
                        quantity = std::atoi(transaction["quantity"].template get<std::string>().c_str());
                    else if (transaction.contains("executed_quantity"))
                        quantity = std::atoi(transaction["executed_quantity"].template get<std::string>().c_str());

                    if (transaction.contains("price"))
                        price = std::atoi(transaction["price"].template get<std::string>().c_str());
                    else if (transaction.contains("executed_price"))
                        price = std::atoi(transaction["executed_price"].template get<std::string>().c_str());
                    
                    if (transaction.contains("stock_code"))
                        stock = transaction["stock_code"].template get<std::string>();
                }
                catch (std::exception& e)
                {
                    std::cout << "Exception occured while parsing a transaction: " << e.what() << std::endl;
                }

                transactions.emplace_back(stock, quantity, price);
            }
            
            this->Transactions[period] = transactions;
            transactions.clear();


            stream.close();
        } 
}


