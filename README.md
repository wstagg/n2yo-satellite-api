# N2YO-Satellite-API

## What it is!

The N2YO Satellite API is a C++ library that allows easy API calls to [N2Y0.com](https://www.n2yo.com/). Users can easily retrieve different satellite information sets with a simple function call! This library also comes with optional python bindings.

API calls available:
- _TLE_
- _Satellite positions_	
- _Visual passes_	
- _Radio passes_	
- _Satellites above_

## Building 

### Dependencies
- [Curl](https://curl.se/libcurl/)
- [Boost test](https://www.boost.org/doc/libs/latest/libs/test/doc/html/index.html)
- [Boost python](https://www.boost.org/doc/libs/latest/libs/python/doc/html/index.html) [Optional for python bindings]
- CMake version 3.20 >=
- C++ 20 compatible compiler

### Linux

After clone the repository, in the terminal, cd in into the project dir and run one of the following build configuration commands.

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

2. In the root directory of the repository make a copy of the "config_tempate.txt" and rename it to "config.txt".

3. Open the config.txt file and replace ```**YOUR API KEY HERE**``` with your API key and save the file.

4. In the terminal change directories to "build" and run: ``` ./n2yoSatelliteApiTests```
