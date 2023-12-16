#include <kafka/kafka.hpp>
#include <ohlcservice.hpp>

using namespace OHLCService;
using namespace OHLCService::Kafka;

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);
    
    OHLCService::OHLCGenerator generator;

    generator.LoadTransactions(argv[2]);

    std::vector<OHLC> ohlcs = generator.GenerateOHLCs();

    KafkaProducer producer(config);

    std::vector<std::string> messages;
    
    for (auto ohlc : ohlcs)
    {
        std::string s;

        ohlc.SerializeToString(&s); 

        OHLC ohlcc;
        ohlcc.ParseFromString(s);

        std::cout << "Producing: OHLC(Stock=" << ohlcc.stock()
            << ", Period=" << ohlcc.period()
            << ", Value=" << ohlcc.value()
            << ", Volume=" << ohlcc.volume()
            << ", AvgPrice=" << ohlcc.averageprice()
            << ");\n"
            << s << '\n';

        messages.push_back(s);
    }

    producer.Stream(messages);
    
    return 0;
}
