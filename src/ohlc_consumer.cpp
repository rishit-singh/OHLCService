#include <kafka/kafka.hpp>
#include <ohlcservice.hpp>
#include <sw/redis++/redis++.h> 
#include <ohlcdatabase.hpp>
#include <iostream>

using namespace OHLCService;
using namespace OHLCService::Kafka;
using namespace OHLCService::Database;

using namespace sw::redis;

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);

    KafkaConsumer consumer(config);     

    Redis redis(argv[2]);

    Response response;

    consumer.SetOnReceiveCallback([&response, &redis](const Message& message){
        OHLC* ohlc = response.add_ohlcs();

        std::stringstream ss; 

        ss << message.get_payload();

        ohlc->ParseFromString(ss.str());
    });

    consumer.Run();

    return 0;
}

 