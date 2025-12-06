#pragma once
#include <iostream>
#include "OrbitFetcher/Config.h"
#include "OrbitFetcher/DataReceiver.h"


struct DataReceiverWithConfigFileFixture
{
    std::unique_ptr<OrbitFetcher::DataReceiver>dataReceiver;
    OrbitFetcher::Config config{};
    bool configReadSuccess{};
    
    DataReceiverWithConfigFileFixture()
    {
        configReadSuccess = config.read("../config.txt");
        dataReceiver = std::make_unique<OrbitFetcher::DataReceiver>(config);
    }

    ~DataReceiverWithConfigFileFixture()
    = default;
};

struct DataReceiverFixture
{
    OrbitFetcher::Config config{};
    std::unique_ptr<OrbitFetcher::DataReceiver>dataReceiver;
    std::string apiKey{};
    int noradId {25544};
    float observerLat{50.96081305800268};
    float observerLon{ -0.11800587771065109};
    float observerAlt{ 0.0};
    int searchRadius{90};
    int searchCategory{2};
    int seconds{10};
    int days{10};
    int minimumVisibility{3};
    int minimumElevation{3};

    DataReceiverFixture()
    {
        config.read("../config.txt");
        apiKey = config.getConfigValues().apiKey;
        dataReceiver = std::make_unique<OrbitFetcher::DataReceiver>();
    }

    ~DataReceiverFixture()
    = default;
};