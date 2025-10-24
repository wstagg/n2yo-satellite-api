#include "Config.h"
#include <fstream>
#include <iostream>

Config::Config()
{
}

bool Config::read(const std::string& filePath)
{
    std::fstream f{};

    f.open(filePath, std::ios_base::in);

    if(!f.is_open())
    {
        throw std::runtime_error("Cannot open config.txt file - " + filePath);
    }

    std::string line{};

    int totalOptionsFound{};
    int totalConfigValuesSet{};
    
    while (std::getline(f, line))
    {
        if(line.empty())
        {
            continue;
        }
        
        if (line.front() == '#')
        {
            continue;
        }
        
        // remove white space from config line 
       for (auto itt = line.begin() ; itt != line.end() ;)
       {
            if (*itt == ' ')
            {
                itt = line.erase(itt);
            }
            else
            {
                ++itt;
            }
       }

        auto equalPos = line.find_first_of('=');
        auto option = line.substr(0 ,equalPos);
        auto value = line.substr(equalPos + 1);

        ++totalOptionsFound;

        setConfigValue(option, value, totalConfigValuesSet);
    }

    return totalOptionsFound == totalConfigValuesSet;
}

const ConfigValues &Config::getConfigValues()
{
    return configValues;
}

std::string Config::getApiRequestTemplate(const ApiType &apiType)
{
    switch (apiType)
    {
    case ApiType::GetTle:
        return apiRequestTemplates.tle;
    case ApiType::GetSatellitePositions:
        return apiRequestTemplates.satellitePositions;
    case ApiType::GetVisualPasses:
        return apiRequestTemplates.visualPasses;
    case ApiType::GetRadioPasses:
        return apiRequestTemplates.radioPasses;
    case ApiType::WhatsUp:
        return apiRequestTemplates.above;
    default:
        return {};
    }
}

void Config::setConfigValue(const std::string& option, const std::string& value, int& totalConfigValuesSet)
{
    if(option == "API_KEY")
    {
        if (!value.empty())
        {
            configValues.apiKey= value;
            ++totalConfigValuesSet;
        }
    }
    else if(option == "OBSERVER_LAT")
    {
        if (!value.empty())
        {
            configValues.observerLat = std::stof(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "OBSERVER_LON")
    {
        if (!value.empty())
        {
            configValues.observerLon = std::stof(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "OBSERVER_ALT")
    {
        if (!value.empty())
        {
            configValues.observerAlt = std::stof(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "SEARCH_RAD")
    {
        if (!value.empty())
        {
            configValues.searchRadius = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "NORAD_ID")
    {
        if (!value.empty())
        {
            configValues.noradId = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "SEARCH_CATEGORY")
    {
        if (!value.empty())
        {
            configValues.satelliteCategory = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "SECONDS")
    {
        if (!value.empty())
        {
            configValues.seconds = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "DAYS")
    {
        if (!value.empty())
        {
            configValues.days = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "MIN_VISIBILITY")
    {
        if (!value.empty())
        {
            configValues.minVisibility = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "MIN_ELEVATION")
    {
        if (!value.empty())
        {
            configValues.minElevation = std::stoi(value);
            ++totalConfigValuesSet;
        }
    }
    else if(option == "API_TLE")
    {
        if (!value.empty())
        {
            apiRequestTemplates.tle = value;
            ++totalConfigValuesSet;
        }
    }
    else if(option == "API_SATELLITE_POSITIONS")
    {
        if (!value.empty())
        {
            apiRequestTemplates.satellitePositions = value;
            ++totalConfigValuesSet;
        }
    }
    else if(option == "API_VISUAL_PASSES")
    {
        if (!value.empty())
        {
            apiRequestTemplates.visualPasses = value;
            ++totalConfigValuesSet;
        }
    }
    else if(option == "API_RADIO_PASSES")
    {
        if (!value.empty())
        {
            apiRequestTemplates.radioPasses = value;
            ++totalConfigValuesSet;
        }
    }
    else if(option == "API_ABOVE")
    {
        if (!value.empty())
        {
            apiRequestTemplates.above = value;
            ++totalConfigValuesSet;
        }
    }
}