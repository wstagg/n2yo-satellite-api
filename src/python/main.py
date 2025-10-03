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



# import matplotlib
# matplotlib.use('TkAgg')  # Set interactive backend first

# from mpl_toolkits.basemap import Basemap
# import numpy as np
# import matplotlib.pyplot as plt

# import satelliteTracker
# # lon_0, lat_0 are the center point of the projection.
# # resolution = 'l' means use low resolution coastlines.

# config = satelliteTracker.Config()

# config.read()

# m = Basemap(projection='ortho',lon_0 = config.getConfigValues().observerLat, lat_0 = config.getConfigValues().observerLon, resolution = 'l')
# m.drawcoastlines()
# m.fillcontinents(color='coral',lake_color='aqua')
# # draw parallels and meridians.
# m.drawparallels(np.arange(-90.,120.,30.))
# m.drawmeridians(np.arange(0.,420.,60.))
# m.drawmapboundary(fill_color='aqua') 
# plt.title("Full Disk Orthographic Projection")
# plt.show()


