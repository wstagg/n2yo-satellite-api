#include "DataReceiver.h"
#include <iostream>
#include <string>

DataReceiver::DataReceiver(Config& _config):
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

ResponseData::Tle DataReceiver::getTle()
{
    return callApi<ResponseData::Tle>(ApiType::GetTle);
}

ResponseData::SatellitePosition DataReceiver::getSatellitePosition()
{
    return callApi<ResponseData::SatellitePosition>(ApiType::GetSatellitePositions);
}

ResponseData::SatelliteVisualPass DataReceiver::getSatelliteVisualPass()
{
    return callApi<ResponseData::SatelliteVisualPass>(ApiType::GetVisualPasses);
}

ResponseData::SatelliteRadioPass DataReceiver::getSatelliteRadioPass()
{
    return callApi<ResponseData::SatelliteRadioPass>(ApiType::GetRadioPasses);
}

ResponseData::SatellitesAbove DataReceiver::getSatellitesAbove()
{
    return callApi<ResponseData::SatellitesAbove>(ApiType::WhatsUp);
}

const std::string DataReceiver::createApiUrl(const ApiType apiType)
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
            apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos  + 1, std::to_string(config.getConfigValues().noradId));
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

int DataReceiver::makeCurlRequest(const std::string& apiCallUrl)
{
    if (!curl) 
    {
        std::cout << "curl nullptr" << std::endl;
        return -1;
    }
    
    CURLcode code{};    
    code = curl_easy_setopt(curl, CURLOPT_URL, apiCallUrl.c_str());
    code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataReceiver::writeCallback);
    code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);    
    return res;
}

size_t DataReceiver::writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto sizeTotal = size * nmemb;
    std::string s{ptr, sizeTotal};
    static_cast<DataReceiver*>(userdata)->dataString.append(s);
 
    return sizeTotal;
}