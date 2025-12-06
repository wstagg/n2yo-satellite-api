#include "OrbitFetcher/DataReceiver.h"
#include <iostream>
#include <string>

OrbitFetcher::DataReceiver::DataReceiver()
{
    curl = curl_easy_init();
}

OrbitFetcher::DataReceiver::DataReceiver(Config& _config):
config{_config}
{
    curl = curl_easy_init();
}

OrbitFetcher::DataReceiver::~DataReceiver()
{
    if (curl)
    {
        curl_easy_cleanup(curl);
    }
}

OrbitFetcher::ResponseData::Tle OrbitFetcher::DataReceiver::getTle()
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = config.getConfigValues().apiKey;
    apiCallParams.noradId = config.getConfigValues().noradId;
    return callApi<ResponseData::Tle>(ApiType::GetTle, apiCallParams);
}

OrbitFetcher::ResponseData::Tle OrbitFetcher::DataReceiver::getTle(const std::string& apiKey, const int& noradId)
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = apiKey;
    apiCallParams.noradId = noradId;
    return callApi<ResponseData::Tle>(ApiType::GetTle, apiCallParams);
}

OrbitFetcher::ResponseData::SatellitePosition OrbitFetcher::DataReceiver::getSatellitePosition()
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = config.getConfigValues().apiKey;
    apiCallParams.noradId = config.getConfigValues().noradId;
    apiCallParams.observerLat = config.getConfigValues().observerLat;
    apiCallParams.observerLon = config.getConfigValues().observerLon;
    apiCallParams.observerAlt = config.getConfigValues().observerAlt;
    apiCallParams.seconds = config.getConfigValues().seconds;
    return callApi<ResponseData::SatellitePosition>(ApiType::GetSatellitePositions, apiCallParams);
}

OrbitFetcher::ResponseData::SatellitePosition OrbitFetcher::DataReceiver::getSatellitePosition(
    const std::string& apiKey,
    const int& noradId,
    const float& observerLat,
    const float& observerLon,
    const float& observerAlt,
    const int& seconds)
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = apiKey;
    apiCallParams.noradId = noradId;
    apiCallParams.observerLat = observerLat;
    apiCallParams.observerLon = observerLon;
    apiCallParams.observerAlt = observerAlt;
    apiCallParams.seconds = seconds;
    return callApi<ResponseData::SatellitePosition>(ApiType::GetSatellitePositions, apiCallParams);
}

OrbitFetcher::ResponseData::SatelliteVisualPass OrbitFetcher::DataReceiver::getSatelliteVisualPass()
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = config.getConfigValues().apiKey;
    apiCallParams.noradId = config.getConfigValues().noradId;
    apiCallParams.observerLat = config.getConfigValues().observerLat;
    apiCallParams.observerLon = config.getConfigValues().observerLon;
    apiCallParams.observerAlt = config.getConfigValues().observerAlt;
    apiCallParams.days = config.getConfigValues().days;
    apiCallParams.minimumVisibility = config.getConfigValues().minVisibility;
    return callApi<ResponseData::SatelliteVisualPass>(ApiType::GetVisualPasses, apiCallParams);
}

OrbitFetcher::ResponseData::SatelliteVisualPass OrbitFetcher::DataReceiver::getSatelliteVisualPass(
    const std::string& apiKey,
    const int& noradId,
    const float& observerLat,
    const float& observerLon,
    const float& observerAlt,
    const int& days,
    const int& minimumVisibility)
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = apiKey;
    apiCallParams.noradId = noradId;
    apiCallParams.observerLat = observerLat;
    apiCallParams.observerLon = observerLon;
    apiCallParams.observerAlt = observerAlt;
    apiCallParams.days = days;
    apiCallParams.minimumVisibility = minimumVisibility;
    return callApi<ResponseData::SatelliteVisualPass>(ApiType::GetVisualPasses, apiCallParams);
}

OrbitFetcher::ResponseData::SatelliteRadioPass OrbitFetcher::DataReceiver::getSatelliteRadioPass()
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = config.getConfigValues().apiKey;
    apiCallParams.noradId = config.getConfigValues().noradId;
    apiCallParams.observerLat = config.getConfigValues().observerLat;
    apiCallParams.observerLon = config.getConfigValues().observerLon;
    apiCallParams.observerAlt = config.getConfigValues().observerAlt;
    apiCallParams.days = config.getConfigValues().days;
    apiCallParams.minimumElevation = config.getConfigValues().minElevation;
    return callApi<ResponseData::SatelliteRadioPass>(ApiType::GetRadioPasses, apiCallParams);
}

OrbitFetcher::ResponseData::SatelliteRadioPass OrbitFetcher::DataReceiver::getSatelliteRadioPass(const std::string& apiKey, const int& noradId,
    const float& observerLat, const float& observerLon, const float& observerAlt, const int& days,
    const int& minimumElevation)
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = apiKey;
    apiCallParams.noradId = noradId;
    apiCallParams.observerLat = observerLat;
    apiCallParams.observerLon = observerLon;
    apiCallParams.observerAlt = observerAlt;
    apiCallParams.days = days;
    apiCallParams.minimumElevation = minimumElevation;
    return callApi<ResponseData::SatelliteRadioPass>(ApiType::GetRadioPasses, apiCallParams);
}

OrbitFetcher::ResponseData::SatellitesAbove OrbitFetcher::DataReceiver::getSatellitesAbove()
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = config.getConfigValues().apiKey;
    apiCallParams.observerLat = config.getConfigValues().observerLat;
    apiCallParams.observerLon = config.getConfigValues().observerLon;
    apiCallParams.observerAlt = config.getConfigValues().observerAlt;
    apiCallParams.searchCategory = config.getConfigValues().satelliteCategory;
    apiCallParams.searchRadius = config.getConfigValues().searchRadius;
    return callApi<ResponseData::SatellitesAbove>(ApiType::WhatsUp, apiCallParams);
}

OrbitFetcher::ResponseData::SatellitesAbove OrbitFetcher::DataReceiver::getSatellitesAbove(
    const std::string& apiKey,
    const float& observerLat,
    const float& observerLon,
    const float& observerAlt,
    const int& searchRadius,
    const SatelliteCategory& satelliteCategory)
{
    ApiCallParameters apiCallParams;
    apiCallParams.apiKey = apiKey;
    apiCallParams.observerLat = observerLat;
    apiCallParams.observerLon = observerLon;
    apiCallParams.observerAlt = observerAlt;
    apiCallParams.searchRadius = searchRadius;
    apiCallParams.searchCategory = static_cast<int>(satelliteCategory);
    return callApi<ResponseData::SatellitesAbove>(ApiType::WhatsUp, apiCallParams);
}

const std::string OrbitFetcher::DataReceiver::createApiUrl(const ApiType apiType, const ApiCallParameters& apiCallParameters)
{
    auto apiRequestTemplate = getApiRequestTemplate(apiType);

    while (apiRequestTemplate.find('{') != std::string::npos && apiRequestTemplate.find('}') != std::string::npos) 
    {
        auto openPos = apiRequestTemplate.find_first_of('{');
        auto closePos = apiRequestTemplate.find_first_of('}', openPos);
        auto bracketsSub = apiRequestTemplate.substr(openPos, (closePos + 1) - openPos);
        auto word = bracketsSub.substr(1, bracketsSub.length());
        word.pop_back();

        if(word == "id")
        {
            if (apiCallParameters.noradId.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos  + 1,
                                 std::to_string(apiCallParameters.noradId.value()));
            }
        }
        else if (word == "observer_lat") 
        {
            if (apiCallParameters.observerLat.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos  + 1,
                                 std::to_string(apiCallParameters.observerLat.value()));
            }
        }
        else if (word == "observer_lng") 
        {
            if (apiCallParameters.observerLon.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos  - openPos  + 1,
                                 std::to_string(apiCallParameters.observerLon.value()));
            }
        }
        else if (word == "observer_alt")
        {
            if (apiCallParameters.observerAlt.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos  + 1,
                                 std::to_string(apiCallParameters.observerAlt.value()));
            }
        }
        else if (word == "search_radius") 
        {
            if (apiCallParameters.searchRadius.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1,
                                 std::to_string(apiCallParameters.searchRadius.value()));
            }
        }
        else if (word == "category_id") 
        {
            if (apiCallParameters.searchCategory.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1,
                                 std::to_string(apiCallParameters.searchCategory.value()));
            }
        }
        else if (word == "seconds") 
        {
            if (apiCallParameters.seconds.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1,
                                 std::to_string(apiCallParameters.seconds.value()));
            }
        }
        else if (word == "days") 
        {
            if (apiCallParameters.days.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1,
                                 std::to_string(apiCallParameters.days.value()));
            }
        }
        else if (word == "min_visibility") 
        {
            if (apiCallParameters.minimumVisibility.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1,
                                 std::to_string(apiCallParameters.minimumVisibility.value()));
            }
        }
        else if (word == "min_elevation") 
        {
            if (apiCallParameters.minimumElevation.has_value())
            {
                apiRequestTemplate = apiRequestTemplate.replace(openPos, closePos - openPos + 1,
                                 std::to_string(apiCallParameters.minimumElevation.value()));
            }
        }
    }


    apiRequestTemplate.append(apiCallParameters.apiKey);

    return apiRequestTemplate;
}

int OrbitFetcher::DataReceiver::makeCurlRequest(const std::string& apiCallUrl)
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

size_t OrbitFetcher::DataReceiver::writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto sizeTotal = size * nmemb;
    std::string s{ptr, sizeTotal};
    static_cast<DataReceiver*>(userdata)->dataString.append(s);
 
    return sizeTotal;
}

std::string OrbitFetcher::DataReceiver::getApiRequestTemplate(const ApiType apiType)
{
    switch (apiType)
    {
    case ApiType::GetTle:
        return apiRequestTemplates.tle;
    case ApiType::GetSatellitePositions:
        return apiRequestTemplates.satellitePositions;
    case ApiType::GetVisualPasses:
        return apiRequestTemplates.visualPasses;
    case ApiType::GetRadioPasses:
        return apiRequestTemplates.radioPasses;
    case ApiType::WhatsUp:
        return apiRequestTemplates.above;
    default:
        return {};
    }
}
