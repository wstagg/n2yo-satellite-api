#pragma once
#include <curl/curl.h>
#include <memory>
#include <string>

#include "Config.h" 
#include "SatelliteCategories.h"



enum class ApiType
{
    GetTle,
    GetSatellitePositions,
    GetVisualPasses,
    GetRadioPasses,
    WhatsUp
};

class DataReceiver
{
public:
    DataReceiver(const Config& _config);
    ~DataReceiver();
    const std::string_view getDataString();    
    void callApi(const ApiType apiType, const int& noradId = 0, const SatelliteCategory& satelliteCategory = SatelliteCategory::All);    

private:
    bool startReceiver(std::string apiCall);
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    std::string_view apiTypeToString(const ApiType apiType);
    
    std::string data{};
    CURL* curl{nullptr};
    std::string baseUrl{"https://api.n2yo.com/rest/v1/satellite/"};
    Config config;
};
