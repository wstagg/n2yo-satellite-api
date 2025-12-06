#include "OrbitFetcher/JsonParser.h"
#include "nlohmann/json.hpp"


void OrbitFetcher::JsonParser::parseTle(const std::string_view& dataString, ResponseData::Tle& tle)
{
    nlohmann::json json = nlohmann::json::parse(dataString);
    json.at("info").at("satid").get_to(tle.satId);
    json.at("info").at("satname").get_to(tle.satName);
    json.at("info").at("transactionscount").get_to(tle.transactionCount);
    json.at("tle").get_to(tle.tle);
}

void OrbitFetcher::JsonParser::parseSatellitePositions(const std::string_view &dataString, OrbitFetcher::ResponseData::SatellitePosition &satellitePosition)
{
    nlohmann::json json = nlohmann::json::parse(dataString);
    json.at("info").at("satid").get_to(satellitePosition.satId);
    json.at("info").at("satname").get_to(satellitePosition.satName);
    json.at("info").at("transactionscount").get_to(satellitePosition.transactionCount); 
    auto positions = json.at("positions");
    
    for (const auto& pos: positions)
    {
        ResponseData::PositionData positionData{};
        
        pos.at("satlatitude").get_to(positionData.lat);
        pos.at("satlongitude").get_to(positionData.lon);
        pos.at("sataltitude").get_to(positionData.altKm);
        pos.at("azimuth").get_to(positionData.azimuth);
        pos.at("elevation").get_to(positionData.elevation);
        pos.at("ra").get_to(positionData.rightAscension);
        pos.at("dec").get_to(positionData.declination);
        pos.at("timestamp").get_to(positionData.timeStamp);
        
        satellitePosition.positionData.push_back(positionData);
    }
}

void OrbitFetcher::JsonParser::parseVisualPass(const std::string_view &dataString, OrbitFetcher::ResponseData::SatelliteVisualPass &satelliteVisualPass)
{
    nlohmann::json json = nlohmann::json::parse(dataString);
    json.at("info").at("satid").get_to(satelliteVisualPass.satId);
    json.at("info").at("satname").get_to(satelliteVisualPass.satName);
    json.at("info").at("transactionscount").get_to(satelliteVisualPass.transactionCount); 
    json.at("info").at("passescount").get_to(satelliteVisualPass.passCount);

    if (satelliteVisualPass.passCount > 0)
    {
        auto passes = json.at("passes");

        for (const auto& pass : passes)
        {
            ResponseData::VisualPassData visualPassData{};
            pass.at("startAz").get_to(visualPassData.startAzimuth);
            pass.at("startAzCompass").get_to(visualPassData.startAzimuthCompass);
            pass.at("startEl").get_to(visualPassData.startElevation);
            pass.at("startUTC").get_to(visualPassData.startUTC);
            pass.at("maxAz").get_to(visualPassData.maxAzimuth);
            pass.at("maxAzCompass").get_to(visualPassData.maxAzimuthCompass);
            pass.at("maxEl").get_to(visualPassData.maxElevation);
            pass.at("maxUTC").get_to(visualPassData.maxUTC);
            pass.at("endAz").get_to(visualPassData.endAzimuth);
            pass.at("endAzCompass").get_to(visualPassData.endAzimuthCompass);
            pass.at("endEl").get_to(visualPassData.endElevation);
            pass.at("endUTC").get_to(visualPassData.endUTC);
            pass.at("mag").get_to(visualPassData.maxVisualMagnitude);
            pass.at("duration").get_to(visualPassData.visibleDuration);

            satelliteVisualPass.visualPassData.push_back(visualPassData);
        }
    }
}

void OrbitFetcher::JsonParser::parseRadioPass(const std::string_view &dataString, OrbitFetcher::ResponseData::SatelliteRadioPass &satelliteRadioPass)
{
    nlohmann::json json = nlohmann::json::parse(dataString);
    json.at("info").at("satid").get_to(satelliteRadioPass.satId);
    json.at("info").at("satname").get_to(satelliteRadioPass.satName);
    json.at("info").at("transactionscount").get_to(satelliteRadioPass.transactionCount); 
    json.at("info").at("passescount").get_to(satelliteRadioPass.passCount);

    if (satelliteRadioPass.passCount > 0)
    {
        auto passes = json.at("passes");

        for (const auto& pass : passes)
        {
            ResponseData::RadioPassData radioPassData{};
            pass.at("startAz").get_to(radioPassData.startAzimuth);
            pass.at("startAzCompass").get_to(radioPassData.startAzimuthCompass);
            pass.at("startUTC").get_to(radioPassData.startUTC);
            pass.at("maxAz").get_to(radioPassData.maxAzimuth);
            pass.at("maxAzCompass").get_to(radioPassData.maxAzimuthCompass);
            pass.at("maxEl").get_to(radioPassData.maxElevation);
            pass.at("maxUTC").get_to(radioPassData.maxUTC);
            pass.at("endAz").get_to(radioPassData.endAzimuth);
            pass.at("endAzCompass").get_to(radioPassData.endAzimuthCompass);
            pass.at("endUTC").get_to(radioPassData.endUTC);

            satelliteRadioPass.radioPassData.push_back(radioPassData);
        }
    }
}

void OrbitFetcher::JsonParser::parseWhatsAbove(const std::string_view &dataString, OrbitFetcher::ResponseData::SatellitesAbove &satellitesAbove)
{
    nlohmann::json json = nlohmann::json::parse(dataString);
    json.at("info").at("category").get_to(satellitesAbove.category);
    json.at("info").at("transactionscount").get_to(satellitesAbove.transactionCount);
    json.at("info").at("satcount").get_to(satellitesAbove.satelliteCount);

    if (satellitesAbove.satelliteCount > 0)
    {
        auto above = json.at("above");

        for (const auto& sat : above)
        {
            ResponseData::SatelliteData satelliteData{};
            sat.at("satid").get_to(satelliteData.satId);
            sat.at("satname").get_to(satelliteData.satName);
            sat.at("intDesignator").get_to(satelliteData.internationalDesignator);
            sat.at("launchDate").get_to(satelliteData.launchDate);
            sat.at("satlat").get_to(satelliteData.lat);
            sat.at("satlng").get_to(satelliteData.lon);
            sat.at("satalt").get_to(satelliteData.altKm);

            satellitesAbove.satellitesAbove.push_back(satelliteData);
        }
    }
}
