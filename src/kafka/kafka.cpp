#include "kafka.hpp"

OHLCService::Kafka::KafkaConfig::KafkaConfig(std::string broker, std::string topic, const size_t partition, std::string groupId, const size_t pollDelay, std::string logFile)
    : Broker(broker), Topic(topic), Partition(partition), GroupId(groupId), PollDelay(pollDelay), LogFile(logFile)
{
}

OHLCService::Kafka::KafkaConfig OHLCService::Kafka::KafkaConfig::FromFile(const std::string_view file)
{
    std::ifstream fp(file.data());

    std::array<std::string_view, 6> requiredKeys = {
        "broker",
        "topic",
        "partition",
        "group_id",
        "poll_delay",
        "log_file"    
    }; 

    json data = json::parse(fp);

    for (auto key : requiredKeys)
        if (!data.contains(key.data()))
        {
            std::string error = std::string(key);
            throw std::runtime_error(error + " is required but not provided in the config.");
        }

    return KafkaConfig(data["broker"].template get<std::string>(), 
                        data["topic"].template get<std::string>(),
                        data["partition"].template get<size_t>(),
                        data["group_id"].template get<std::string>(),
                        data["poll_delay"].template get<size_t>(), 
                        data["log_file"].template get<std::string>()); 
}

    

OHLCService::Kafka::KafkaProducer::KafkaProducer(KafkaConfig config) : Config(config), Builder(config.Topic), mProducer({
                { "metadata.broker.list", config.Broker }
        })
        {
            this->Builder.partition(config.Partition);
        }

void OHLCService::Kafka::KafkaProducer::Stream(std::vector<std::string> messages)
{
    for (auto message : messages)
    {  
        this->Builder.payload(message);
        this->mProducer.produce(this->Builder);
    }

    this->mProducer.flush();
}


OHLCService::Kafka::KafkaConsumer::KafkaConsumer(KafkaConfig config) 
    : Config(config), mConsumer({
                { "metadata.broker.list", config.Broker },
                { "group.id", config.GroupId },
                { "enable.auto.commit", false }
        }), IsRunning(false)
    {
    // signal(SIGINT, [this](int) { this->IsRunning = false; });

    	// Print the assigned partitions on assignment
	this->mConsumer.set_assignment_callback(
		[](const cppkafka::TopicPartitionList& partitions) {
			std::stringstream ss("Got assigned: ");
			ss << partitions;
		});

    this->mConsumer.set_revocation_callback([](const cppkafka::TopicPartitionList& partitions) {
			std::stringstream ss("Got revoked: ");
			ss << partitions;
		});
}


void OHLCService::Kafka::KafkaConsumer::Run()
{
    this->mConsumer.subscribe({this->Config.Topic});

    this->IsRunning = true;

    while (this->IsRunning)
    {
        Message message = this->mConsumer.poll(std::chrono::milliseconds{this->Config.PollDelay});

        if (message)
        {
            if (message.get_error())
            {
                if (!message.is_eof())
                {
                    std::stringstream stream;

                    stream << "Received error: " << message.get_payload();
                    std::cerr << stream.str();
                }
            }
            else
            {
                this->OnReceiveCallback(message);
                this->mConsumer.commit(message); 
            }
        }
    }

}

void OHLCService::Kafka::KafkaConsumer::SetOnReceiveCallback(std::function<void(const Message&)> callback)
{
    this->OnReceiveCallback = callback;
}