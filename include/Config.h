#pragma once
#include <string>
#include <variant>

class Config
{
public:
    Config();
    void read();
    
    enum class Option
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
    
    const std::variant<int, float, std::string> getConfigValue(const Option configOption);
    
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
