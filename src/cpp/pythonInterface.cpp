#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/return_value_policy.hpp>

#include "Config.h"
#include "DataReceiver.h"
#include "ResponseData.h"
#include "SatelliteCategories.h"


BOOST_PYTHON_MODULE(satelliteTracker)
{
    // Config
    boost::python::class_<ConfigValues>("ConfigValues")
        .def_readonly("apiKey", &ConfigValues::apiKey)
        .def_readonly("observerLat", &ConfigValues::observerLat)
        .def_readonly("observerLon", &ConfigValues::observerLon)
        .def_readonly("observerAlt", &ConfigValues::observerAlt)
        .def_readonly("searchRadius", &ConfigValues::searchRadius)
        .def_readonly("seconds", &ConfigValues::seconds)
        .def_readonly("days", &ConfigValues::days)
        .def_readonly("minVisibility", &ConfigValues::minVisibility)
        .def_readonly("minElevation", &ConfigValues::minElevation);
    
    boost::python::class_<Config>("Config", boost::python::init<>())
        .def("read", &Config::read)
        .def("getConfigValues", &Config::getConfigValues, boost::python::return_value_policy<boost::python::reference_existing_object>());

    // DataReceiver
    boost::python::class_<DataReceiver>("DataReceiver", boost::python::init<const Config&>())
        .def("getTle", &DataReceiver::getTle)
        .def("getSatellitePosition", &DataReceiver::getSatellitePosition)
        .def("getSatelliteVisualPass", &DataReceiver::getSatelliteVisualPass)
        .def("getSatelliteRadioPass", &DataReceiver::getSatelliteRadioPass)
        .def("getSatellitesAbove", &DataReceiver::getSatellitesAbove);
    
    // Response Data
    boost::python::class_<ResponseData::Tle>("Tle")
        .def_readonly("satId", &ResponseData::Tle::satId)
        .def_readonly("satName", &ResponseData::Tle::satName)
        .def_readonly("transactionCount", &ResponseData::Tle::transactionCount)
        .def_readonly("tle", &ResponseData::Tle::tle);

    boost::python::class_<ResponseData::PositionData>("PositionData")
        .def_readonly("lat", &ResponseData::PositionData::lat)
        .def_readonly("lon", &ResponseData::PositionData::lon)
        .def_readonly("altKm", &ResponseData::PositionData::altKm)
        .def_readonly("azimuth", &ResponseData::PositionData::azimuth)
        .def_readonly("elevation", &ResponseData::PositionData::elevation)
        .def_readonly("rightAscension", &ResponseData::PositionData::rightAscension)
        .def_readonly("declination", &ResponseData::PositionData::declination)
        .def_readonly("timeStamp", &ResponseData::PositionData::timeStamp);

    boost::python::class_<std::vector<ResponseData::PositionData>>("PositionDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<ResponseData::PositionData>>());

    boost::python::class_<ResponseData::SatellitePosition>("SatellitePosition")
        .def_readonly("satId", &ResponseData::SatellitePosition::satId)
        .def_readonly("satName", &ResponseData::SatellitePosition::satName)
        .def_readonly("transactionCount", &ResponseData::SatellitePosition::transactionCount)
        .def_readonly("positionData", &ResponseData::SatellitePosition::positionData);

    boost::python::class_<ResponseData::VisualPassData>("VisualPassData")
        .def_readonly("startAzimuth", &ResponseData::VisualPassData::startAzimuth)
        .def_readonly("startAzimuthCompass", &ResponseData::VisualPassData::startAzimuthCompass)
        .def_readonly("startElevation", &ResponseData::VisualPassData::startElevation)
        .def_readonly("startUTC", &ResponseData::VisualPassData::startUTC)
        .def_readonly("maxAzimuth", &ResponseData::VisualPassData::maxAzimuth)
        .def_readonly("maxAzimuthCompass", &ResponseData::VisualPassData::maxAzimuthCompass)
        .def_readonly("maxElevation", &ResponseData::VisualPassData::maxElevation)
        .def_readonly("maxUTC", &ResponseData::VisualPassData::maxUTC)
        .def_readonly("endAzimuth", &ResponseData::VisualPassData::endAzimuth)
        .def_readonly("endAzimuthCompass", &ResponseData::VisualPassData::endAzimuthCompass)
        .def_readonly("endElevation", &ResponseData::VisualPassData::endElevation)
        .def_readonly("endUTC", &ResponseData::VisualPassData::endUTC)
        .def_readonly("maxVisualMagnitude", &ResponseData::VisualPassData::maxVisualMagnitude)
        .def_readonly("visibleDuration", &ResponseData::VisualPassData::visibleDuration);

    boost::python::class_<std::vector<ResponseData::VisualPassData>>("VisualPassDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<ResponseData::VisualPassData>>());

    boost::python::class_<ResponseData::SatelliteVisualPass>("SatelliteVisualPass")
        .def_readonly("satId", &ResponseData::SatelliteVisualPass::satId)
        .def_readonly("satName", &ResponseData::SatelliteVisualPass::satName)
        .def_readonly("transactionCount", &ResponseData::SatelliteVisualPass::transactionCount)
        .def_readonly("passCount", &ResponseData::SatelliteVisualPass::passCount)
        .def_readonly("visualPassData", &ResponseData::SatelliteVisualPass::visualPassData);

    boost::python::class_<ResponseData::RadioPassData>("RadioPassData")
        .def_readonly("startAzimuth", &ResponseData::RadioPassData::startAzimuth)
        .def_readonly("startAzimuthCompass", &ResponseData::RadioPassData::startAzimuthCompass)
        .def_readonly("startUTC", &ResponseData::RadioPassData::startUTC)
        .def_readonly("maxAzimuth", &ResponseData::RadioPassData::maxAzimuth)
        .def_readonly("maxAzimuthCompass", &ResponseData::RadioPassData::maxAzimuthCompass)
        .def_readonly("maxElevation", &ResponseData::RadioPassData::maxElevation)
        .def_readonly("maxUTC", &ResponseData::RadioPassData::maxUTC)
        .def_readonly("endAzimuth", &ResponseData::RadioPassData::endAzimuth)
        .def_readonly("endAzimuthCompass", &ResponseData::RadioPassData::endAzimuthCompass)
        .def_readonly("endUTC", &ResponseData::RadioPassData::endUTC);

    boost::python::class_<std::vector<ResponseData::RadioPassData>>("RadioPassDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<ResponseData::RadioPassData>>());

    boost::python::class_<ResponseData::SatelliteRadioPass>("SatelliteRadioPass")
        .def_readonly("satId", &ResponseData::SatelliteRadioPass::satId)
        .def_readonly("satName", &ResponseData::SatelliteRadioPass::satName)
        .def_readonly("transactionCount", &ResponseData::SatelliteRadioPass::transactionCount)
        .def_readonly("passCount", &ResponseData::SatelliteRadioPass::passCount)
        .def_readonly("radioPassData", &ResponseData::SatelliteRadioPass::radioPassData);

     boost::python::class_<ResponseData::SatelliteData>("SatelliteData")
        .def_readonly("satId", &ResponseData::SatelliteData::satId)
        .def_readonly("satName", &ResponseData::SatelliteData::satName)
        .def_readonly("internationalDesignator", &ResponseData::SatelliteData::internationalDesignator)
        .def_readonly("launchDate", &ResponseData::SatelliteData::launchDate)
        .def_readonly("lat", &ResponseData::SatelliteData::lat)
        .def_readonly("lon", &ResponseData::SatelliteData::lon)
        .def_readonly("altKm", &ResponseData::SatelliteData::altKm);
    
    boost::python::class_<std::vector<ResponseData::SatelliteData>>("SatelliteDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<ResponseData::SatelliteData>>());

    boost::python::class_<ResponseData::SatellitesAbove>("SatellitesAbove")
        .def_readonly("category", &ResponseData::SatellitesAbove::category)
        .def_readonly("transactionCount", &ResponseData::SatellitesAbove::transactionCount)
        .def_readonly("satelliteCount", &ResponseData::SatellitesAbove::satelliteCount)
        .def_readonly("satellitesAbove", &ResponseData::SatellitesAbove::satellitesAbove);

    // Satellite categories
    boost::python::enum_<SatelliteCategory>("SatelliteCategory")
    .value("All", SatelliteCategory::All)
    .value("Brightest", SatelliteCategory::Brightest)
    .value("ISS", SatelliteCategory::ISS)
    .value("Weather", SatelliteCategory::Weather)
    .value("NOAA", SatelliteCategory::NOAA)
    .value("GOES", SatelliteCategory::GOES)
    .value("EarthResources", SatelliteCategory::EarthResources)
    .value("SearchAndRescue", SatelliteCategory::SearchAndRescue)
    .value("DisasterMonitoring", SatelliteCategory::DisasterMonitoring)
    .value("TrackingAndDataRelaySatelliteSystem", SatelliteCategory::TrackingAndDataRelaySatelliteSystem)
    .value("Geostationary", SatelliteCategory::Geostationary)
    .value("Intelsat", SatelliteCategory::Intelsat)
    .value("Gorizont", SatelliteCategory::Gorizont)
    .value("Raduga", SatelliteCategory::Raduga)
    .value("Molniya", SatelliteCategory::Molniya)
    .value("Iridium", SatelliteCategory::Iridium)
    .value("Orbcomm", SatelliteCategory::Orbcomm)
    .value("Globalstar", SatelliteCategory::Globalstar)
    .value("AmateurRadio", SatelliteCategory::AmateurRadio)
    .value("Experimental", SatelliteCategory::Experimental)
    .value("GPSOperational", SatelliteCategory::GPSOperational)
    .value("GlonassOperational", SatelliteCategory::GlonassOperational)
    .value("Galileo", SatelliteCategory::Galileo)
    .value("SatelliteBasedAugmentationSystem", SatelliteCategory::SatelliteBasedAugmentationSystem)
    .value("NavyNavigationSatelliteSystem", SatelliteCategory::NavyNavigationSatelliteSystem)
    .value("RussianLEONavigation", SatelliteCategory::RussianLEONavigation)
    .value("SpaceAndEarthScience", SatelliteCategory::SpaceAndEarthScience)
    .value("Geodetic", SatelliteCategory::Geodetic)
    .value("Engineering", SatelliteCategory::Engineering)
    .value("Education", SatelliteCategory::Education)
    .value("Military", SatelliteCategory::Military)
    .value("RadarCalibration", SatelliteCategory::RadarCalibration)
    .value("CubeSats", SatelliteCategory::CubeSats)
    .value("XMandSirius", SatelliteCategory::XMandSirius)
    .value("TV", SatelliteCategory::TV)
    .value("BeidouNavigationSystem", SatelliteCategory::BeidouNavigationSystem)
    .value("Yaogan", SatelliteCategory::Yaogan)
    .value("WestfordNeedles", SatelliteCategory::WestfordNeedles)
    .value("Parus", SatelliteCategory::Parus)
    .value("Strela", SatelliteCategory::Strela)
    .value("Gonets", SatelliteCategory::Gonets)
    .value("Tsiklon", SatelliteCategory::Tsiklon)
    .value("Tsikada", SatelliteCategory::Tsikada)
    .value("O3BNetworks", SatelliteCategory::O3BNetworks)
    .value("Tselina", SatelliteCategory::Tselina)
    .value("Celestis", SatelliteCategory::Celestis)
    .value("IRNSS", SatelliteCategory::IRNSS)
    .value("QZSS", SatelliteCategory::QZSS)
    .value("Flock", SatelliteCategory::Flock)
    .value("Lemur", SatelliteCategory::Lemur)
    .value("GPSConstellation", SatelliteCategory::GPSConstellation)
    .value("GlonassConstellation", SatelliteCategory::GlonassConstellation)
    .value("Starlink", SatelliteCategory::Starlink)
    .value("OneWeb", SatelliteCategory::OneWeb)
    .value("ChineseSpaceStation", SatelliteCategory::ChineseSpaceStation)
    .value("Qianfan", SatelliteCategory::Qianfan)
    .value("Kuiper", SatelliteCategory::Kuiper);
}