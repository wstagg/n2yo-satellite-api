# OrbitFetcher

## What it is

OrbitFetcher is a C++ library that allows easy API calls to [N2YO.com](https://www.n2yo.com/). Users can easily retrieve different satellite data sets with a simple function call! This library also comes with optional Python bindings.

API calls available:
- _TLE_
- _Satellite positions_
- _Visual passes_
- _Radio passes_
- _Satellites above_

## Disclaimer

This is an independent project and is not affiliated with, endorsed by, or connected to [N2YO.com](https://www.n2yo.com/). This library simply provides a C++ interface to their public API.

## Building

### Dependencies
- [Curl](https://curl.se/libcurl/)
- [Boost test](https://www.boost.org/doc/libs/latest/libs/test/doc/html/index.html)
- [Boost Python](https://www.boost.org/doc/libs/latest/libs/python/doc/html/index.html) [Optional for Python bindings]
- CMake version 3.20 >=
- C++ 20 compatible compiler

### Linux

After cloning the repository, using the terminal, cd into the project dir and run one of the following build configuration commands.

Debug with Python bindings:

```
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_PY_BINDINGS=ON
```
Debug no Python bindings:
```
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```
Release with Python bindings:
```
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_PY_BINDINGS=ON
```
Release no Python bindings:
```
cmake -B build -DCMAKE_BUILD_TYPE=Release 
```
Once configuration is complete run:

``` 
cd build && make
```
After successfully compiling the following will be built:
- OrbitFetcherTests
- OrbitFetcher.so

### Windows (in work)
....

## Running tests

1. After successfully compiling, you need to make an account at [N2YO.com](https://www.n2yo.com/) to generate your API key.

2. In the root directory of the repository make a copy of the "config_template.txt" and rename it to "config.txt".

3. Open the config.txt file and replace ```**YOUR API KEY HERE**``` with your API key and save the file.

4. In the terminal change directories to "build" and run: ``` ./OrbitFetcherTests```

## How to use

Using the library is very simple. There are two ways to instantiate the parameters needed for the API calls:

1. Use the config.txt file.
1. Directly pass API call parameters into the function calls.

### Using the config.txt

```cpp
#include "OrbitFetcher/Config.h"
#include "OrbitFetcher/DataReceiver.h"

int main()
{
    // Create a Config object 
    OrbitFetcher::Config config;

    // Pass in the path to the config.txt file to be read
    bool ok = config.read("./config.txt");
    
    if (!ok)
    {
        return 1;
    }

    // Create an instance of the DataReceiver and pass the config object into the constructor 
    OrbitFetcher::DataReceiver receiver(config);

    // Get TLE using config.txt configuration
    OrbitFetcher::ResponseData::Tle tle = receiver.getTle();

    // Get satellite position data using config.txt configuration
    OrbitFetcher::ResponseData::SatellitePosition satellitePosition = receiver.getSatellitePosition();

    // Get satellite visual pass data using config.txt configuration
    OrbitFetcher::ResponseData::SatelliteVisualPass visualPass = receiver.getSatelliteVisualPass();

    // Get satellite radio pass data using config.txt configuration
    OrbitFetcher::ResponseData::SatelliteRadioPass radioPass = receiver.getSatelliteRadioPass();

    // Get satellites above using config.txt configuration
    OrbitFetcher::ResponseData::SatellitesAbove satellitesAbove = receiver.getSatellitesAbove();
    
}
```

### Parameter function calls

```cpp
#include "OrbitFetcher/Config.h"
#include "OrbitFetcher/DataReceiver.h"

int main()
{
    const std::string apiKey {"589P8Q-SDRYX8-L842ZD-5Z9"};
    const int noradId {25544};
    const float observerLat {50.96081305800268};
    const float observerLon {-0.11800587771065109};
    const float observerAlt {0.0};
    const int searchRadius {90};
    const OrbitFetcher::SatelliteCategory satelliteCategory {OrbitFetcher::SatelliteCategory::All};
    const int seconds {10};
    const int days {10};
    const int minimumVisibility {3};
    const int minimumElevation {3};

    // Create an instance of the DataReceiver
    OrbitFetcher::DataReceiver receiver;

    // Get TLE using function parameters
    OrbitFetcher::ResponseData::Tle tle = receiver.getTle(apiKey, noradId);

    // Get satellite position data using function parameters
    OrbitFetcher::ResponseData::SatellitePosition satellitePosition = receiver.getSatellitePosition(apiKey, noradId, observerLat, observerLon, observerAlt, seconds);

    // Get satellite visual pass data using function parameters
    OrbitFetcher::ResponseData::SatelliteVisualPass visualPass = receiver.getSatelliteVisualPass(apiKey, noradId, observerLat, observerLon, observerAlt, days, minimumVisibility);

    // Get satellite radio pass data using function parameters
    OrbitFetcher::ResponseData::SatelliteRadioPass radioPass = receiver.getSatelliteRadioPass(apiKey, noradId, observerLat, observerLon, observerAlt, days, minimumElevation);

    // Get satellites above using function parameters
    OrbitFetcher::ResponseData::SatellitesAbove satellitesAbove = receiver.getSatellitesAbove(apiKey, observerLat, observerLon, observerAlt, searchRadius, satelliteCategory);

}
```

### Getting config values

The config class has a helpful function that allows you to get individual values from the file that has been read in.

For example getting the API key from the file:

```cpp
#include "OrbitFetcher/Config.h"

int main()
{
    OrbitFetcher::Config config;

    bool ok = config.read("./config.txt");
    
    if (!ok)
    {
        return 1;
    }

    // Get API key from config file
    auto apiKey = config.getConfigValues().apiKey;
}
```

### Response Data

Each function call returns a ```OrbitFetcher::ResponseData``` struct that holds all the information from the API call, ready for you to use at your disposal.


## Python
Using the library with python is super simple. Build the library with ```--DBUILD_PY_BINDINGS=ON```. 

Copy the OrbitFetcher.so file and the config.txt file into the root dir of your python project, and you are good to go!

```
├── config.txt
├── main.py
└── OrbitFetcher.so
```

**Example:**
```python
import OrbitFetcher

config = OrbitFetcher.Config()

ok = config.read("config.txt")

if ok:
    dataReceiver = OrbitFetcher.DataReceiver(config)

    tle = dataReceiver.getTle()
    positions = dataReceiver.getSatellitePosition()
    visualPass = dataReceiver.getSatelliteVisualPass()
    radioPass = dataReceiver.getSatelliteRadioPass()
    satsAbove = dataReceiver.getSatellitesAbove()


```
I have built a very basic satellite tracking application using matplotlib as an example [satellite tracker](https://github.com/wstagg/Satellite-Tracker-Matplotlib). Feel free to check it out and have a play.

# **Note**

Detailed explanations of each API call and its respective response can be found at https://www.n2yo.com/api/ along with usage limits for each call.