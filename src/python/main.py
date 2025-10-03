import satelliteTracker

config = satelliteTracker.Config()

config.read()

dataReceiver = satelliteTracker.DataReceiver(config)

spaceStationID = 25544

satPos = dataReceiver.getSatellitePosition(spaceStationID)

for pos in satPos.positionData:
    print(pos.altKm)

satsAbove = dataReceiver.getSatellitesAbove(satelliteTracker.SatelliteCategory.All)

for sat in satsAbove.satellitesAbove:
    print(sat.satName)


