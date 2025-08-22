#pragma once
#include <string>
#include <variant>

enum class ConfigOption
{
    ApiKey,
    ObserverLat,
    ObserverLon,
    ObserverAlt,
    SearchRadius,
    Seconds,
    Days,
    MinVisibility,
    MinElevation
};

class Config
{
public:
    Config();
    void read();
    const std::variant<int, float, std::string> getConfigValue(const ConfigOption configOption);

private:
    void setConfigValue(const std::string& option, const std::string& value);

    std::string apiKey{"&apiKey="};
    float observerLat{};
    float observerLon{};
    float observerAlt{};
    int searchRadius{};
    int seconds{};
    int days{};
    int minVisibility{};
    int minElevation{};


};
