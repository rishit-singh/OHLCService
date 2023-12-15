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
        messages.push_back(ohlc.SerializeAsString());

    producer.Stream(messages);
    
    return 0;
}
