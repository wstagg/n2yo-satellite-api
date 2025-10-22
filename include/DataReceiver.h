#pragma once
#include <curl/curl.h>
#include <memory>
#include <string>
#include <iostream>

#include "Config.h" 
#include "SatelliteCategories.h"
#include "ApiType.h"
#include "JsonParser.h"

class DataReceiver
{
public:
    DataReceiver(Config& _config);
    ~DataReceiver();

    ResponseData::Tle getTle();
    ResponseData::SatellitePosition getSatellitePosition();
    ResponseData::SatelliteVisualPass getSatelliteVisualPass();
    ResponseData::SatelliteRadioPass getSatelliteRadioPass();
    ResponseData::SatellitesAbove getSatellitesAbove();

private:
    template<typename T>
    T callApi(const ApiType apiType);    
    const std::string createApiUrl(const ApiType apiType);
    
    int makeCurlRequest(const std::string& apiCallUrl);
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    
    std::string dataString{};
    CURL* curl{nullptr};
    Config config;
};

template <typename T>
inline T DataReceiver::callApi(const ApiType apiType)
{
    if (!dataString.empty())
    {
        dataString.clear();
    }

    auto apiUrl = createApiUrl(apiType);
    
    auto res = makeCurlRequest(apiUrl);
    
    if (res == CURLcode::CURLE_OK)
    {
        JsonParser jsonParser;
        T responseData{};
        return jsonParser.parse(apiType, dataString, responseData);
    }
    else
    {
        std::cout << "Failed to make curl request, curl code: " << res << std::endl;
    }

    return T{};
}
