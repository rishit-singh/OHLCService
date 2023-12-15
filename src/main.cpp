#include <ohlcservice.hpp>

int main(int argc, char** argv)
{
    OHLCService::OHLCGenerator generator;

    generator.LoadTransactions(argv[1]);

    generator.GenerateOHLCs();

    for (auto ohlc : generator.GetOHLCs())
        std::cout << "OHLC(" << "Period=" << ohlc.period() << "Stock=" << ohlc.stock() << ", Value=" << ohlc.value() << ", Volume=" << ohlc.volume() << ", AvgPrice=" << ohlc.averageprice() << ");\n";

    return 0;
}