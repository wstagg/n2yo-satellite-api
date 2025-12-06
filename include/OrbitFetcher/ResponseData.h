#pragma once
#include <string>
#include <vector>

namespace OrbitFetcher::ResponseData
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

        bool operator == (const PositionData& positionData2)
        {
            return (this->lat == positionData2.lat &&
                    this->lon == positionData2.lon &&
                    this->altKm == positionData2.altKm &&
                    this->azimuth == positionData2.azimuth &&
                    this->elevation == positionData2.elevation &&
                    this->rightAscension == positionData2.rightAscension &&
                    this->declination == positionData2.declination &&
                    this->timeStamp == positionData2.timeStamp);
        }
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

        bool operator == (const VisualPassData& visualPassData2)
        {
            return (this->startAzimuth == visualPassData2.startAzimuth &&
                    this->startAzimuthCompass == visualPassData2.startAzimuthCompass &&
                    this->startElevation == visualPassData2.startElevation &&
                    this->startUTC == visualPassData2.startUTC &&
                    this->maxAzimuth == visualPassData2.maxAzimuth &&
                    this->maxAzimuthCompass == visualPassData2.maxAzimuthCompass &&
                    this->maxElevation == visualPassData2.maxElevation &&
                    this->maxUTC == visualPassData2.maxUTC &&
                    this->endAzimuth == visualPassData2.endAzimuth &&
                    this->endAzimuthCompass == visualPassData2.endAzimuthCompass &&
                    this->endElevation == visualPassData2.endElevation &&
                    this->endUTC == visualPassData2.endUTC &&
                    this->maxVisualMagnitude == visualPassData2.maxVisualMagnitude &&
                    this->visibleDuration == visualPassData2.visibleDuration
            );
        }
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

        bool operator == (const RadioPassData& RadioPassData2)
        {
            return (this->startAzimuth == RadioPassData2.startAzimuth &&
                    this->startAzimuthCompass == RadioPassData2.startAzimuthCompass &&
                    this->startUTC == RadioPassData2.startUTC &&
                    this->maxAzimuth == RadioPassData2.maxAzimuth &&
                    this->maxAzimuthCompass == RadioPassData2.maxAzimuthCompass &&
                    this->maxElevation == RadioPassData2.maxElevation &&
                    this->maxUTC == RadioPassData2.maxUTC &&
                    this->endAzimuth == RadioPassData2.endAzimuth &&
                    this->endAzimuthCompass == RadioPassData2.endAzimuthCompass &&
                    this->endUTC == RadioPassData2.endUTC);
        }
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

        bool operator == (const SatelliteData& satelliteData2)
        {
            return (this->satId == satelliteData2.satId &&
                    this->satName == satelliteData2.satName &&
                    this->internationalDesignator == satelliteData2.internationalDesignator &&
                    this->launchDate == satelliteData2.launchDate &&
                    this->lat == satelliteData2.lat &&
                    this->lon == satelliteData2.lon &&
                    this->altKm == satelliteData2.altKm);
        }
    };

    struct SatellitesAbove
    {
        std::string category;
        int transactionCount;
        int satelliteCount;
        std::vector<SatelliteData> satellitesAbove;
    };
}
