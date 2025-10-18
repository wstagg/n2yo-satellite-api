#include "DataReceiver.h"
#include <iostream>
#include <string>
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

ResponseData::SatellitesAbove DataReceiver::getSatellitesAbove()
{
    return callApi<ResponseData::SatellitesAbove>(ApiType::WhatsUp, 0);
}

const std::string DataReceiver::createApiUrl(const ApiType apiType, const int &noradId)
{
    auto apiRequestTemplate = config.getApiRequestTemplate(apiType);

    while (apiRequestTemplate.find('{') != std::string::npos && apiRequestTemplate.find('}') != std::string::npos) 
    {
        auto openPos = apiRequestTemplate.find_first_of('{');
        auto closePos = apiRequestTemplate.find_first_of('}', openPos);
        auto bracketsSub = apiRequestTemplate.substr(openPos, (closePos + 1) - openPos);
        auto word = bracketsSub.substr(1, bracketsSub.length());
        word.pop_back();

        if(word == "id")
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos, std::to_string(noradId));
        }
        else if (word == "observer_lat") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos  + 1, std::to_string(config.getConfigValues().observerLat));
        }
        else if (word == "observer_lng") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos  - openPos  + 1, std::to_string(config.getConfigValues().observerLon));
        }
        else if (word == "observer_alt") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos  + 1, std::to_string(config.getConfigValues().observerAlt));
        }
        else if (word == "search_radius") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1, std::to_string(config.getConfigValues().searchRadius));
        }
        else if (word == "category_id") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1, std::to_string(config.getConfigValues().satelliteCategory));
        }
        else if (word == "seconds") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1, std::to_string(config.getConfigValues().seconds));
        }
        else if (word == "days") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1, std::to_string(config.getConfigValues().days));
        }
        else if (word == "min_visibility") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1, std::to_string(config.getConfigValues().minVisibility));
        }
        else if (word == "min_elevation") 
        {
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1, std::to_string(config.getConfigValues().minElevation));
        }
    }
    
    apiRequestTemplate.append(config.getConfigValues().apiKey);

    return apiRequestTemplate;
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