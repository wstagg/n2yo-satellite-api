# N2YO-Satellite-API

## What it is

The N2YO Satellite API is a C++ library that allows easy API calls to [N2Y0.com](https://www.n2yo.com/). Users can easily retrieve different satellite information sets with a simple function call! This library also comes with optional python bindings.

API calls available:
- _TLE_
- _Satellite positions_	
- _Visual passes_	
- _Radio passes_	
- _Satellites above_

## Disclaimer

This is an independent project and is not affiliated with, endorsed by, or connected to [N2Y0.com](https://www.n2yo.com/). This library simply provides a C++ interface to their public API.

## Building 

### Dependencies
- [Curl](https://curl.se/libcurl/)
- [Boost test](https://www.boost.org/doc/libs/latest/libs/test/doc/html/index.html)
- [Boost python](https://www.boost.org/doc/libs/latest/libs/python/doc/html/index.html) [Optional for python bindings]
- CMake version 3.20 >=
- C++ 20 compatible compiler

### Linux

After cloning the repository, using the terminal, cd in into the project dir and run one of the following build configuration commands.

Debug with python bindings:

```
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_PY_BINDINGS=ON
```
Debug no python bindings:
```
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```
Release with python bindings:
```
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_PY_BINDINGS=ON
```
Release no python bindings:
```
cmake -B build -DCMAKE_BUILD_TYPE=Release 
```
Once configuration is complete run:

``` 
cd build && make -j14
```
After successfully compiling the following will be built:
- n2yoSatelliteApiTests 
- n2yoSatelliteApi.so

### Windows (in work)
....

## Running tests

1. After successfully compiling, you need to make an account at [N2Y0.com](https://www.n2yo.com/) to generate your API key. 

2. In the root directory of the repository make a copy of the "config_template.txt" and rename it to "config.txt".

3. Open the config.txt file and replace ```**YOUR API KEY HERE**``` with your API key and save the file.

4. In the terminal change directories to "build" and run: ``` ./n2yoSatelliteApiTests```

## How to use

Using the library is very simple. There are two ways to use instantiate the parameters needed for the API calls:

1. Use the config.txt file.
1. Directly pass API call parameters into the function calls.

### Using the config.txt

```
#include "SatelliteApi/Config.h"
#include "SatelliteApi/DataReceiver.h"

int main()
{
    // Create a Config object 
    SatelliteApi::Config config;

    // Pass in the path to the config.txt file to be read
    config.read("./config.txt");

    // Create an instance of the DataReceiver and pass the config object into the constructor 
    SatelliteApi::DataReceiver receiver(config);

    // Get TLE using config.txt configuration
    SatelliteApi::ResponseData::Tle tle = receiver.getTle();

    // Get satellite position data using config.txt configuration
    SatelliteApi::ResponseData::SatellitePosition satellitePosition = receiver.getSatellitePosition();

    // Get satellite visual pass data using config.txt configuration
    SatelliteApi::ResponseData::SatelliteVisualPass visualPass = receiver.getSatelliteVisualPass();

    // Get satellite radio pass data using config.txt configuration
    SatelliteApi::ResponseData::SatelliteRadioPass radioPass = receiver.getSatelliteRadioPass();

    // Get satellites above using config.txt configuration
    SatelliteApi::ResponseData::SatellitesAbove satellitesAbove = receiver.getSatellitesAbove();
    
}
```

### Parameter function calls

```
#include "SatelliteApi/Config.h"
#include "SatelliteApi/DataReceiver.h"

int main()
{
    const std::string apiKey {"589P8Q-SDRYX8-L842ZD-5Z9"};
    const int noradId {25544};
    const float observerLat{50.96081305800268};
    const float observerLon{ -0.11800587771065109};
    const float observerAlt{ 0.0};
    const int searchRadius{90};
    const SatelliteApi::SatelliteCategory satelliteCategory {SatelliteApi::SatelliteCategory::All};
    const int seconds{10};
    const int days{10};
    const int minimumVisibility{3};
    const int minimumElevation{3};

    // Create an instance of the DataReceiver
    SatelliteApi::DataReceiver receiver;

    // Get TLE using function parameters
    SatelliteApi::ResponseData::Tle tle = receiver.getTle(apiKey, noradId);

    // Get satellite position data using function parameters
    SatelliteApi::ResponseData::SatellitePosition satellitePosition = receiver.getSatellitePosition(apiKey, noradId, observerLat, observerLon, observerAlt, seconds);

    // Get satellite visual pass data using function parameters
    SatelliteApi::ResponseData::SatelliteVisualPass visualPass = receiver.getSatelliteVisualPass(apiKey, noradId, observerLat, observerLon, observerAlt, days, minimumVisibility);

    // Get satellite radio pass data using function parameters
    SatelliteApi::ResponseData::SatelliteRadioPass radioPass = receiver.getSatelliteRadioPass(apiKey, noradId, observerLat, observerLon, observerAlt, days, minimumElevation);

    // Get satellites above using function parameters
    SatelliteApi::ResponseData::SatellitesAbove satellitesAbove = receiver.getSatellitesAbove(apiKey, observerLat, observerLon, observerAlt, searchRadius, satelliteCategory);

}
```

### Getting config values

The config class has a helpful function that allows you to get individual values from the file that has been read in.

For example getting the API key from the file:

```
#include "SatelliteApi/Config.h"

int main()
{
    SatelliteApi::Config config;

    config.read("config.txt");

    // Get API key from config file
    auto apiKey = config.getConfigValues().apiKey;
}
```

### Response Data

Each function call returns a ```SatelliteApi::ResponseData``` struct that holds all the information from the API call, ready for you to use at your disposal. 


**Note**

Detailed explanations of each API call and its respective response can be found at https://www.n2yo.com/api/ along with usage limits for each call. 
