#pragma once
#include <string>
#include <vector>

namespace ResponseData
{
    struct Tle
    {
        int satId;
        std::string satName;
        int transactionCount;
        std::string tle;
    };

    struct PositionData
    {
        float lat;
        float lon;
        float altKm;
        float azimuth;
        float elevation;
        float rightAscension;
        float declination;
        int timeStamp;
    };

    struct SatellitePosition
    {
        int satId;
        std::string satName;
        int transactionCount;
        std::vector<PositionData> positionData;
    };

    struct VisualPassData
    {
        float startAzimuth;
        std::string startAzimuthCompass;
        float startElevation;
        int startUTC;
        float maxAzimuth;
        std::string maxAzimuthCompass;
        float maxElevation;
        int maxUTC;
        float endAzimuth;
        std::string endAzimuthCompass;
        float endElevation;
        int endUTC;
        float maxVisualMagnitude;
        int visibleDuration;
    };

    struct SatelliteVisualPass
    {
        int satId;
        std::string satName;
        int transactionCount;
        int passCount;
        std::vector<VisualPassData> visualPassData;
    };

       struct RadioPassData
    {
        float startAzimuth;
        std::string startAzimuthCompass;
        int startUTC;
        float maxAzimuth;
        std::string maxAzimuthCompass;
        float maxElevation;
        int maxUTC;
        float endAzimuth;
        std::string endAzimuthCompass;
        int endUTC;
    };
    
     struct SatelliteRadioPass
    {
        int satId;
        std::string satName;
        int transactionCount;
        int passCount;
        std::vector<RadioPassData> radioPassData;
    };

    struct SatelliteData
    {
        int satId;
        std::string satName;
        std::string internationalDesignator;
        std::string launchDate;
        float lat;
        float lon;
        float altKm;
    };
    
    struct SatellitesAbove
    {
        std::string category;
        int transactionCount;
        int satelliteCount;
        std::vector<SatelliteData> satellitesAbove;
    };
}