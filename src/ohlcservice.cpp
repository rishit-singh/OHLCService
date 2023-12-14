#include <ohlcservice.hpp>

OHLCService::Transaction::Transaction(size_t quantity, size_t price)
    : Quantity(quantity), Price(price)
{
}

std::vector<OHLCService::OHLC> OHLCService::OHLCGenerator::GenerateOHLCs()
{
    return this->OHLCs;
}

std::vector<OHLCService::OHLC> OHLCService::OHLCGenerator::GetOHLCs()
{
    return this->OHLCs;
}

std::vector<OHLCService::Transaction> OHLCService::OHLCGenerator::GetTransactions(const std::string_view period)
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

                transaction = json::parse(line);

                try
                {
                    if (transaction.contains("quantity"))
                        quantity = transaction["quantity"].template get<size_t>();
                    else if (transaction.contains("executed_quantity"))
                        quantity = transaction["executed_quantity"].template get<size_t>();

                    if (transaction.contains("price"))
                        price = transaction["price"].template get<size_t>();
                    else if (transaction.contains("executed_price"))
                        price = transaction["executed_price"].template get<size_t>();
                }
                catch (std::exception& e)
                {
                    std::cout << "Exception occured while parsing a transaction: " << e.what() << std::endl;
                }

                transactions.emplace_back(quantity, price);

                auto t = *(transactions.end() - 1);

                std::cout << "Transaction(Quantity=" << t.Quantity << ", Price=" << t.Price << ");\n";
            }

            stream.close();
        } 
}


