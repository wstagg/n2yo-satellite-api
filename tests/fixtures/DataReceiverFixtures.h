#include <iostream>
#include <print>
#include "Config.h"
#include "DataReceiver.h"


struct DataReceiverWithConfigFileFixture
{
    std::unique_ptr<DataReceiver>dataReceiver;
    Config config{};
    bool configReadSuccess{};
    
    DataReceiverWithConfigFileFixture()
    {
        configReadSuccess = config.read("config.txt");
        dataReceiver = std::make_unique<DataReceiver>(config);
    }

    ~DataReceiverWithConfigFileFixture()
    = default;
};

struct DataReceiverFixture
{
    std::unique_ptr<DataReceiver>dataReceiver;
    std::string apiKey{"SJA8ER-PMNRT5-VZCVR5-5JOP"};
    int noradId {25544};
    float observerLat{50.96081305800268};
    float observerLon{ -0.11800587771065109};
    float observerAlt{ 0.0};
    int searchRadius{90};
    int searchCategory{2};
    int seconds{10};
    int days{3};
    int minimumVisibility{3};
    int minimumElevation{3};

    DataReceiverFixture()
    {
        dataReceiver = std::make_unique<DataReceiver>();
    }

    ~DataReceiverFixture()
    = default;
};