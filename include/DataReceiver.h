#pragma once
#include <curl/curl.h>
#include <memory>
#include <string>
#include <format>

#include "Config.h" 
#include "SatelliteCategories.h"
#include "ApiType.h"
#include "JsonParser.h"

class DataReceiver
{
public:
    DataReceiver(const Config& _config);
    ~DataReceiver();

    ResponseData::Tle getTle(const int &noradId);
    ResponseData::SatellitePosition getSatellitePosition(const int& noradId);
    ResponseData::SatelliteVisualPass getSatelliteVisualPass(const int& noradId);
    ResponseData::SatelliteRadioPass getSatelliteRadioPass(const int& noradId);
    ResponseData::SatellitesAbove getSatellitesAbove(const SatelliteCategory& satelliteCategory = 
    SatelliteCategory::All);

    
private:
    template<typename T>
    T callApi(const ApiType apiType, const int& noradId = 0, const SatelliteCategory& satelliteCategory = 
    SatelliteCategory::All);    
    const std::string createApiUrl(const ApiType apiType, const int &noradId, const SatelliteCategory &satelliteCategory);
    
    bool makeCurlRequest(std::string apiCall);
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    std::string_view apiTypeToString(const ApiType apiType);
    
    std::string dataString{};
    CURL* curl{nullptr};
    std::string baseUrl{"https://api.n2yo.com/rest/v1/satellite/"};
    Config config;
};

template <typename T>
inline T DataReceiver::callApi(const ApiType apiType, const int &noradId, const SatelliteCategory &satelliteCategory)
{
    if (!dataString.empty())
    {
        dataString.clear();
    }

    auto apiUrl = createApiUrl(apiType, noradId, satelliteCategory); 
    
    if (makeCurlRequest(apiUrl))
    {
        JsonParser jsonParser;
        T responseData{};
        return jsonParser.parse(apiType, dataString, responseData);
    }

    return T{};
}
