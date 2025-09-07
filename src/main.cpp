#include <iostream>
#include "DataReceiver.h"
#include "Config.h"


int main()
{
    Config config;
    config.read();
    DataReceiver dataReceiver{config};

    const int internationalSpaceStationID{25544}; 
    
    auto tle = dataReceiver.getTle(internationalSpaceStationID);
    auto pos = dataReceiver.getSatellitePosition(internationalSpaceStationID);
    
    auto visualPass =  dataReceiver.getSatelliteVisualPass(internationalSpaceStationID);
    auto radioPass = dataReceiver.getSatelliteRadioPass(internationalSpaceStationID);
    auto satsAbove = dataReceiver.getSatellitesAbove(SatelliteCategory::All);

}