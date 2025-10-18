#pragma once
#include <string>
#include "ApiType.h"

struct ConfigValues
{
    std::string apiKey{};
    float observerLat{};
    float observerLon{};
    float observerAlt{};
    int searchRadius{};
    int noradId{};
    int seconds{};
    int days{};
    int minVisibility{};
    int minElevation{};

    bool operator == (const ConfigValues& configValues2)
        {
            return (this->apiKey == configValues2.apiKey &&
                    this->observerLat == configValues2.observerLat &&
                    this->observerLon == configValues2.observerLon &&
                    this->observerAlt == configValues2.observerAlt &&
                    this->searchRadius == configValues2.searchRadius &&
                    this->seconds == configValues2.seconds &&
                    this->days == configValues2.days &&
                    this->minVisibility == configValues2.minVisibility &&
                    this->minElevation == configValues2.minElevation);
        }
};

struct ApiRequestTemplates
{
    std::string tle{};
    std::string satellitePositions{};
    std::string visualPasses{};
    std::string radioPasses{};
    std::string above{};
};

class Config
{
public:
    Config();
    void read();    
    const ConfigValues& getConfigValues();
    std::string getApiRequestTemplate(const ApiType& apiType);
    
private:
    void setConfigValue(const std::string& option, const std::string& value);
    ConfigValues configValues;
    ApiRequestTemplates apiRequestTemplates;
};
