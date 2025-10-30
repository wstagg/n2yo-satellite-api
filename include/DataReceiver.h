#pragma once
#include <curl/curl.h>
#include <memory>
#include <string>
#include <iostream>
#include <optional>

#include "Config.h" 
#include "SatelliteCategories.h"
#include "ApiType.h"
#include "JsonParser.h"

class DataReceiver
{
public:
    DataReceiver();
    explicit DataReceiver(Config& _config);
    ~DataReceiver();

    ResponseData::Tle getTle();
    ResponseData::Tle getTle(const std::string& apiKey, const int& noradId);

    ResponseData::SatellitePosition getSatellitePosition();
    ResponseData::SatellitePosition getSatellitePosition(
        const std::string& apiKey,
        const int& noradId,
        const float& observerLat,
        const float& observerLon,
        const float& observerAlt,
        const int& seconds);

    ResponseData::SatelliteVisualPass getSatelliteVisualPass();
    ResponseData::SatelliteVisualPass getSatelliteVisualPass(
        const std::string& apiKey,
        const int& noradId,
        const float& observerLat,
        const float& observerLon,
        const float& observerAlt,
        const int& days,
        const int& minimumVisibility);

    ResponseData::SatelliteRadioPass getSatelliteRadioPass();
    ResponseData::SatelliteRadioPass getSatelliteRadioPass(
        const std::string& apiKey,
        const int& noradId,
        const float& observerLat,
        const float& observerLon,
        const float& observerAlt,
        const int& days,
        const int& minimumElevation);

    ResponseData::SatellitesAbove getSatellitesAbove();
    ResponseData::SatellitesAbove getSatellitesAbove(
        const std::string& apiKey,
        const float& observerLat,
        const float& observerLon,
        const float& observerAlt,
        const int& searchRadius,
        const SatelliteCategory& satelliteCategory);

private:
    struct ApiCallParameters
    {
        std::string apiKey;
        std::optional<int> noradId;
        std::optional<float> observerLat;
        std::optional<float> observerLon;
        std::optional<float> observerAlt;
        std::optional<int> searchRadius;
        std::optional<int> searchCategory;
        std::optional<int> seconds;
        std::optional<int> days;
        std::optional<int> minimumVisibility;
        std::optional<int> minimumElevation;
    };

    struct ApiRequestTemplates
    {
        std::string tle{"https://api.n2yo.com/rest/v1/satellite/tle/{id}/&apiKey="};
        std::string satellitePositions{"https://api.n2yo.com/rest/v1/satellite/positions/{id}/{observer_lat}/{observer_lng}/{observer_alt}/{seconds}/&apiKey="};
        std::string visualPasses{"https://api.n2yo.com/rest/v1/satellite/visualpasses/{id}/{observer_lat}/{observer_lng}/{observer_alt}/{days}/{min_visibility}/&apiKey="};
        std::string radioPasses{"https://api.n2yo.com/rest/v1/satellite/radiopasses/{id}/{observer_lat}/{observer_lng}/{observer_alt}/{days}/{min_elevation}/&apiKey="};
        std::string above{"https://api.n2yo.com/rest/v1/satellite/above/{observer_lat}/{observer_lng}/{observer_alt}/{search_radius}/{category_id}/&apiKey="};
    }apiRequestTemplates;

    template<typename T>
    T callApi(const ApiType apiType, const ApiCallParameters& apiCallParameters);
    const std::string createApiUrl(const ApiType apiType, const ApiCallParameters& apiCallParameters);
    int makeCurlRequest(const std::string& apiCallUrl);
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    std::string getApiRequestTemplate(const ApiType apiType);
    
    std::string dataString{};
    CURL* curl{nullptr};
    Config config;
};

template <typename T>
inline T DataReceiver::callApi(const ApiType apiType, const ApiCallParameters& apiCallParameters)
{
    if (!dataString.empty())
    {
        dataString.clear();
    }

    auto apiUrl = createApiUrl(apiType, apiCallParameters);

    std::cout << apiUrl << std::endl;

    auto res = makeCurlRequest(apiUrl);
    
    if (res == CURLcode::CURLE_OK)
    {
        T responseData{};

        try
        {
            JsonParser jsonParser;
            jsonParser.parse(apiType, dataString, responseData);
            return responseData;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return T{};
        }
    }
    else
    {
        std::cout << "Failed to make curl request, curl code: " << res << std::endl;
        return T{};
    }
}
