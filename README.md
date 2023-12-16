# OHLCService

A service to parse raw stock price changes into gRPC compatible OHLC objects with support for Kafka.

## Build instructions

### Dependencies

#### CppKafka
Kafka API.

#### Redis-plus-plus
Redis client.

#### gRPC
Protocol for the server.

#### Protobuf
Protocol buffer serialization

### Compiling 

```
git clone https://github.com/rishit-singh/OHLCService.git;

cd OHLCService;

cmake -Bbuild;

cd build; 

make;
```

### Running

#### OHLCProducer
```
./OHLCProducer <config> <data dir>
```
#### OHLCConsumer
```
./OHLCServer <config> <redis address> 
```

#### OHLCServer
```
./OHLCClient <address> <redis address> 
```

#### OHLCClient
```
./OHLCClient <server address> <stock code> 
```


