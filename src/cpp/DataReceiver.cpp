#include "DataReceiver.h"
#include <iostream>
#include <format>
#include <variant>

DataReceiver::DataReceiver(const Config& _config):
config{_config}
{
    curl = curl_easy_init();
}

DataReceiver::~DataReceiver()
{
    if (curl)
    {
        curl_easy_cleanup(curl);
    }
}

ResponseData::Tle DataReceiver::getTle(const int &noradId)
{
    return callApi<ResponseData::Tle>(ApiType::GetTle, noradId);
}

ResponseData::SatellitePosition DataReceiver::getSatellitePosition(const int &noradId)
{
    return callApi<ResponseData::SatellitePosition>(ApiType::GetSatellitePositions, noradId);
}

ResponseData::SatelliteVisualPass DataReceiver::getSatelliteVisualPass(const int &noradId)
{
    return callApi<ResponseData::SatelliteVisualPass>(ApiType::GetVisualPasses, noradId);
}

ResponseData::SatelliteRadioPass DataReceiver::getSatelliteRadioPass(const int &noradId)
{
    return callApi<ResponseData::SatelliteRadioPass>(ApiType::GetRadioPasses, noradId);
}

ResponseData::SatellitesAbove DataReceiver::getSatellitesAbove(const SatelliteCategory &satelliteCategory)
{
    return callApi<ResponseData::SatellitesAbove>(ApiType::WhatsUp, 0, satelliteCategory);
}

const std::string DataReceiver::createApiUrl(const ApiType apiType, const int &noradId, const SatelliteCategory &satelliteCategory)
{
    std::string apiUrl{baseUrl};

    switch (apiType)
    {
    case ApiType::GetTle:
        apiUrl.append(std::format("{}/{}{}", 
            apiTypeToString(apiType), 
            noradId,
            config.getConfigValues().apiKey)
        );
        break;
    
    case ApiType::GetSatellitePositions:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            noradId,
            config.getConfigValues().observerLat,
            config.getConfigValues().observerLon,
            config.getConfigValues().observerAlt,
            config.getConfigValues().seconds,
            config.getConfigValues().apiKey)
        );
        break;

    case ApiType::GetVisualPasses:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            noradId,
            config.getConfigValues().observerLat,
            config.getConfigValues().observerLon,
            config.getConfigValues().observerAlt,
            config.getConfigValues().days,
            config.getConfigValues().minVisibility,
            config.getConfigValues().apiKey)
        );
        break;  

    case ApiType::GetRadioPasses:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            noradId,
            config.getConfigValues().observerLat,
            config.getConfigValues().observerLon,
            config.getConfigValues().observerAlt,
            config.getConfigValues().days,
            config.getConfigValues().minElevation,
            config.getConfigValues().apiKey)
        );
        break;
    
    case ApiType::WhatsUp:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            config.getConfigValues().observerLat,
            config.getConfigValues().observerLon,
            config.getConfigValues().observerAlt,
            config.getConfigValues().searchRadius,
            static_cast<int>(satelliteCategory),
            config.getConfigValues().apiKey)
        );
        break;  
    
    default:
        break;
    }

    return apiUrl;
}

bool DataReceiver::makeCurlRequest(std::string apiCall)
{
    if (!curl) 
    {
        return false;
    }
    
    CURLcode code{};    
    code = curl_easy_setopt(curl, CURLOPT_URL, apiCall.c_str());
    code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataReceiver::writeCallback);
    code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    
    return res == CURLE_OK;
}

size_t DataReceiver::writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto sizeTotal = size * nmemb;
    std::string s{ptr, sizeTotal};
    static_cast<DataReceiver*>(userdata)->dataString.append(s);
 
    return sizeTotal;
}

std::string_view DataReceiver::apiTypeToString(const ApiType apiType)
{
    switch (apiType)
    {
    case ApiType::GetTle:
        return "tle";
        break;
    case ApiType::GetSatellitePositions:
        return "positions";
        break;
case ApiType::GetVisualPasses:
        return "visualpasses";
        break;
    case ApiType::GetRadioPasses:
        return "radiopasses";
        break;
    case ApiType::WhatsUp:
        return "above";
        break;
        default:
        return {};
        break;
    }
}
