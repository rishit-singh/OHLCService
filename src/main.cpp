#include <ohlcservice.hpp>

int main(int argc, char** argv)
{
    OHLCService::OHLCGenerator generator;

    generator.LoadTransactions(argv[1]);
    
    // for (auto t : generator.GetTransactions())

    return 0;
}