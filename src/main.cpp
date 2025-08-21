#include <iostream>
#include "DataReceiver.h"
#include "Config.h"

int main()
{
    Config config;
    config.read();

    const int internationalSpaceStationID{25544}; 
    
    DataReceiver dataReceiver{config};
    
    //dataReceiver.callApi(ApiType::GetTle, internationalSpaceStationID);
    //dataReceiver.callApi(ApiType::GetSatellitePositions, internationalSpaceStationID);
    //dataReceiver.callApi(ApiType::GetVisualPasses, internationalSpaceStationID);
    //dataReceiver.callApi(ApiType::GetRadioPasses, internationalSpaceStationID);
    //dataReceiver.callApi(ApiType::WhatsUp, 0, SatelliteCategory::All);
    
    
    std::cout << dataReceiver.getDataString() << std::endl;


} 