import matplotlib
matplotlib.use('TkAgg') # Set interactive backend first
from mpl_toolkits.basemap import Basemap
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import satelliteTracker

# Create the figure and axis FIRST
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111)

# Create basemap
m = Basemap(projection='robin', lon_0=0, resolution='c', ax=ax)
m.drawcoastlines()
m.fillcontinents(color='coral', lake_color='aqua')
m.drawparallels(np.arange(-90., 120., 30.))
m.drawmeridians(np.arange(0., 360., 60.))
m.drawmapboundary(fill_color='aqua')

config = satelliteTracker.Config()
config.read()

dataReceiver = satelliteTracker.DataReceiver(config)

sat_plots = []

def init():

    satsAbove = dataReceiver.getSatellitesAbove(satelliteTracker.SatelliteCategory.ISS)
    print(satsAbove.transactionCount)
    for sat in satsAbove.satellitesAbove:
        xpt, ypt = m(sat.lon, sat.lat)
        plot, = m.plot(xpt, ypt, 'bo', markersize=8)
        sat_plots.append(plot)
        #sat_names.append(text)
    
    return sat_plots


def update(frame):

    # Clear previous satellite markers
    for plot in sat_plots:
        plot.remove()
        
    sat_plots.clear()
    
    # for name in sat_names:
    #     name.remove()
    # sat_names.clear()
    
    # Get and plot new positions
    satsAbove = dataReceiver.getSatellitesAbove(satelliteTracker.SatelliteCategory.ISS)
    print(satsAbove.transactionCount)
    for sat in satsAbove.satellitesAbove:
        xpt, ypt = m(sat.lon, sat.lat)
        plot, = m.plot(xpt, ypt, 'bo', markersize=8)
        sat_plots.append(plot)
        #sat_names.append(text)
    
    return sat_plots

plt.title("Satellite Tracker")

ani = animation.FuncAnimation(
    fig,
    update,
    init_func=init,
    interval=36000,
    blit=True
)

plt.show()