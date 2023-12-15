#include <ohlcservice.hpp>


OHLCService::Transaction::Transaction(size_t quantity, size_t price)
    : Quantity(quantity), Price(price)
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

    for (auto const& [key, val] : this->Transactions)
    { 
        ohlc.set_period(key);
        ohlc.set_value(this->GetValue(val));
        ohlc.set_volume(this->GetVolume(val));
        
        if (!ohlc.value() && !ohlc.volume())
            continue;

        ohlc.set_averageprice(ohlc.value() / ohlc.volume());

        this->OHLCs.push_back(ohlc);

        ohlc = OHLC(); 
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
                }
                catch (std::exception& e)
                {
                    std::cout << "Exception occured while parsing a transaction: " << e.what() << std::endl;
                }

                transactions.emplace_back(quantity, price);
            }
            
            this->Transactions[period] = transactions;

            transactions.clear();

            stream.close();
        } 
}


