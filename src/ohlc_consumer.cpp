#include <kafka/kafka.hpp>
#include <ohlcservice.hpp>
#include <iostream>

using namespace OHLCService;
using namespace OHLCService::Kafka;

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);

    KafkaConsumer consumer(config);    

    consumer.SetOnReceiveCallback([](const Message& message){
        std::cout << message.get_payload() << '\n'; 
    });

    consumer.Run();

    return 0;
}
 
