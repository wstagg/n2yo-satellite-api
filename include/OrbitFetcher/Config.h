#pragma once
#include <string>

namespace OrbitFetcher
{
    struct ConfigValues
    {
        std::string apiKey{};
        float observerLat{};
        float observerLon{};
        float observerAlt{};
        int searchRadius{};
        int noradId{};
        int satelliteCategory{};
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



    class Config
    {
    public:
        Config();
        bool read(const std::string& filePath);
        const ConfigValues& getConfigValues();

    private:
        void setConfigValue(const std::string& option, const std::string& value, int& totalConfigValuesSet);
        ConfigValues configValues;
    };
}