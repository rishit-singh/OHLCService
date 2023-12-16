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
    
    OHLCDatabase database(argv[2]);

    consumer.SetOnReceiveCallback([&database](const Message& message) {
        OHLC ohlc;
        
        std::stringstream ss; 

        std::string str;

        auto& buffer = message.get_payload(); 

        str = std::string(buffer.begin(), buffer.end());

        std::cout << str << '\n';

        if (!ohlc.ParseFromString(str))
            std::cout << "Failed to parse the string." << '\n';
       
        std::cout << "Inserting: OHLC(Stock=" << ohlc.stock()
            << ", Period=" << ohlc.period()
            << ", Value=" << ohlc.value()
            << ", Volume=" << ohlc.volume()
            << ", AvgPrice=" << ohlc.averageprice()
            << ");\n"; 

        database.InsertOHLC(ohlc.stock(), ohlc);
    });

    consumer.Run();

    return 0;
}

 