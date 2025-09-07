#pragma once
#include "ResponseData.h"
#include "ApiType.h"

#include <variant>

class JsonParser
{
public:
    JsonParser() = default;

    template<typename T>
    T parse(const ApiType &apiType, const std::string_view& dataString, T& responseData);

private:
    const ApiType apiType{};
    const std::string_view data{};

    void parseTle(const std::string_view& dataString, ResponseData::Tle& tle);
    void parseSatellitePositions(const std::string_view& dataString, ResponseData::SatellitePosition& satellitePosition);
    void parseVisualPass(const std::string_view& dataString, ResponseData::SatelliteVisualPass& satelliteVisualPass);
    void parseRadioPass(const std::string_view& dataString, ResponseData::SatelliteRadioPass& satelliteRadioPass);
    void parseWhatsAbove(const std::string_view& dataString, ResponseData::SatellitesAbove& satellitesAbove);
};

template <typename T>
inline T JsonParser::parse(const ApiType &apiType, const std::string_view& dataString, T& responseData)
{
    if constexpr(std::is_same_v<T, ResponseData::Tle>)
    {
        parseTle(dataString, responseData);
    }
    else if constexpr(std::is_same_v<T, ResponseData::SatellitePosition>)
    {
        parseSatellitePositions(dataString, responseData);
    }
    else if constexpr(std::is_same_v<T, ResponseData::SatelliteVisualPass>)
    {
        parseVisualPass(dataString, responseData);
    }
    else if constexpr(std::is_same_v<T, ResponseData::SatelliteRadioPass>)
    {
        parseRadioPass(dataString, responseData);
    }
    else if constexpr(std::is_same_v<T, ResponseData::SatellitesAbove>)
    {
        parseWhatsAbove(dataString, responseData);
    }
    return responseData;
}
