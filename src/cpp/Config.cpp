#include "Config.h"
#include <fstream>
#include <iostream>

Config::Config()
{
}

void Config::read()
{
    std::fstream f{};

    f.open("config.txt", std::ios_base::in);

    if(!f.is_open())
    {
        throw std::runtime_error("Cannot open config.txt file");
    }

    std::string line{};
    
    while (std::getline(f, line))
    {
        if(line.empty()) continue;
        
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

        setConfigValue(option, value);
    }
}

const ConfigValues &Config::getConfigValues()
{
    return configValues;
}

void Config::setConfigValue(const std::string& option, const std::string& value)
{   

    if(option == "API_KEY")
    {
        configValues.apiKey.append(value);
    }

    else if(option == "OBSERVER_LAT")
    {
        configValues.observerLat = std::stof(value);
    }

    else if(option == "OBSERVER_LON")
    {
        configValues.observerLon = std::stof(value);  
    }

    else if(option == "OBSERVER_ALT")
    {
        configValues.observerAlt = std::stof(value);
    }

    else if(option == "SEARCH_RAD")
    {
        configValues.searchRadius = std::stoi(value);
    }

    else if(option == "SECONDS")
    {
        configValues.seconds = std::stoi(value);
    }

    else if(option == "DAYS")
    {
        configValues.days = std::stoi(value);
    }

    else if(option == "MIN_VISIBILITY")
    {
        configValues.minVisibility = std::stoi(value);
    }

    else if(option == "MIN_ELEVATION")
    {
        configValues.minElevation = std::stoi(value);
    }
}
