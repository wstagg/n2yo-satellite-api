#pragma once
#include "SatelliteApi/ResponseData.h"
#include "ApiType.h"
#include <variant>

namespace SatelliteApi
{
    class JsonParser
    {
    public:
        JsonParser() = default;

        template<typename T>
        void parse(const SatelliteApi::ApiType &apiType, const std::string_view& dataString, T& responseData);

    private:
        const SatelliteApi::ApiType apiType{};
        const std::string_view data{};

        void parseTle(const std::string_view& dataString, ResponseData::Tle& tle);
        void parseSatellitePositions(const std::string_view& dataString, ResponseData::SatellitePosition& satellitePosition);
        void parseVisualPass(const std::string_view& dataString, ResponseData::SatelliteVisualPass& satelliteVisualPass);
        void parseRadioPass(const std::string_view& dataString, ResponseData::SatelliteRadioPass& satelliteRadioPass);
        void parseWhatsAbove(const std::string_view& dataString, ResponseData::SatellitesAbove& satellitesAbove);
    };

    template <typename T>
    inline void JsonParser::parse(const SatelliteApi::ApiType &apiType, const std::string_view& dataString, T& responseData)
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
    }
}