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

const std::variant<int, float, std::string> Config::getConfigValue(const ConfigOption configOption)
{
    switch (configOption)
    {

    case ConfigOption::ApiKey:
        return apiKey;
        break;
    
        case ConfigOption::ObserverLat:
        return observerLat;
        break;
    
    case ConfigOption::ObserverLon:
        return observerLon;
        break;
    
    case ConfigOption::ObserverAlt:
        return observerAlt;
        break;
    
    case ConfigOption::SearchRadius:
        return searchRadius;
        break;

    case ConfigOption::Seconds:
        return seconds;
        break;

    case ConfigOption::Days:
        return days;
        break;

    case ConfigOption::MinVisibility:
        return minVisibility;
        break;
    
    case ConfigOption::MinElevation:
        return minElevation;
        break;

    default:
        return 0;
        break;
    }
}

void Config::setConfigValue(const std::string& option, const std::string& value)
{   

    if(option == "API_KEY")
    {
        apiKey.append(value);
    }

    else if(option == "OBSERVER_LAT")
    {
        observerLat = std::stof(value);
    }

    else if(option == "OBSERVER_LON")
    {
        observerLon = std::stof(value);  
    }

    else if(option == "OBSERVER_ALT")
    {
        observerAlt = std::stof(value);
    }

    else if(option == "SEARCH_RAD")
    {
        searchRadius = std::stoi(value);
    }

    else if(option == "SECONDS")
    {
        seconds = std::stoi(value);
    }

    else if(option == "DAYS")
    {
        days = std::stoi(value);
    }

    else if(option == "MIN_VISIBILITY")
    {
        minVisibility = std::stoi(value);
    }

    else if(option == "MIN_ELEVATION")
    {
        minElevation = std::stoi(value);
    }
}
