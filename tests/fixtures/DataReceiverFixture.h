#include <iostream>
#include <print>
#include "Config.h"
#include "DataReceiver.h"


struct DataReceiverFixture
{
    std::unique_ptr<DataReceiver>dataReceiver;
    Config config{};
    bool configReadSuccess{};
    
    DataReceiverFixture()
    {
        configReadSuccess = config.read("config.txt");
        dataReceiver = std::make_unique<DataReceiver>(config);
    }

    ~DataReceiverFixture()
    {

    }
};