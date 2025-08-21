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

bool DataReceiver::startReceiver(std::string apiCall)
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

const std::string_view DataReceiver::getDataString()
{
    return data;
}

void DataReceiver::callApi(const ApiType apiType, const int &noradId, const SatelliteCategory &satelliteCategory)
{
    std::string apiUrl{baseUrl};

    switch (apiType)
    {
    case ApiType::GetTle:
        apiUrl.append(std::format("{}/{}{}", 
            apiTypeToString(apiType), 
            noradId,
            std::get<std::string>(config.getConfigValue(ConfigOption::ApiKey)))
        );
        break;
    
    case ApiType::GetSatellitePositions:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            noradId,
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLat)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLon)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverAlt)),
            std::get<int>(config.getConfigValue(ConfigOption::Seconds)),
            std::get<std::string>(config.getConfigValue(ConfigOption::ApiKey)))
        );
        break;
    
    case ApiType::GetVisualPasses:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            noradId,
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLat)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLon)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverAlt)),
            std::get<int>(config.getConfigValue(ConfigOption::Days)),
            std::get<int>(config.getConfigValue(ConfigOption::MinVisibility)),
            std::get<std::string>(config.getConfigValue(ConfigOption::ApiKey)))
        );
        break;
    
        case ApiType::GetRadioPasses:
         apiUrl.append(std::format("{}/{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            noradId,
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLat)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLon)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverAlt)),
            std::get<int>(config.getConfigValue(ConfigOption::Days)),
            std::get<int>(config.getConfigValue(ConfigOption::MinElevation)),
            std::get<std::string>(config.getConfigValue(ConfigOption::ApiKey)))
        );

        break;
    case ApiType::WhatsUp:
        apiUrl.append(std::format("{}/{}/{}/{}/{}/{}{}", 
            apiTypeToString(apiType),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLat)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverLon)),
            std::get<float>(config.getConfigValue(ConfigOption::ObserverAlt)),
            std::get<int>(config.getConfigValue(ConfigOption::SearchRadius)),
            static_cast<int>(satelliteCategory),
            std::get<std::string>(config.getConfigValue(ConfigOption::ApiKey)))
        );
        break;
    
    default:
        break;
    }

    startReceiver(apiUrl);
}

size_t DataReceiver::writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto sizeTotal = size * nmemb;
    std::string s{ptr, sizeTotal};
    static_cast<DataReceiver*>(userdata)->data.append(s);
 
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
