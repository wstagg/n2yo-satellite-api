#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/return_value_policy.hpp>

#include "OrbitFetcher/Config.h"
#include "OrbitFetcher/DataReceiver.h"
#include "OrbitFetcher/ResponseData.h"
#include "OrbitFetcher/SatelliteCategories.h"


BOOST_PYTHON_MODULE(OrbitFetcher)
{
    // Satellite categories
    boost::python::enum_<OrbitFetcher::SatelliteCategory>("OrbitFetcher::SatelliteCategory")
    .value("All", OrbitFetcher::SatelliteCategory::All)
    .value("Brightest", OrbitFetcher::SatelliteCategory::Brightest)
    .value("ISS", OrbitFetcher::SatelliteCategory::ISS)
    .value("Weather", OrbitFetcher::SatelliteCategory::Weather)
    .value("NOAA", OrbitFetcher::SatelliteCategory::NOAA)
    .value("GOES", OrbitFetcher::SatelliteCategory::GOES)
    .value("EarthResources", OrbitFetcher::SatelliteCategory::EarthResources)
    .value("SearchAndRescue", OrbitFetcher::SatelliteCategory::SearchAndRescue)
    .value("DisasterMonitoring", OrbitFetcher::SatelliteCategory::DisasterMonitoring)
    .value("TrackingAndDataRelaySatelliteSystem", OrbitFetcher::SatelliteCategory::TrackingAndDataRelaySatelliteSystem)
    .value("Geostationary", OrbitFetcher::SatelliteCategory::Geostationary)
    .value("Intelsat", OrbitFetcher::SatelliteCategory::Intelsat)
    .value("Gorizont", OrbitFetcher::SatelliteCategory::Gorizont)
    .value("Raduga", OrbitFetcher::SatelliteCategory::Raduga)
    .value("Molniya", OrbitFetcher::SatelliteCategory::Molniya)
    .value("Iridium", OrbitFetcher::SatelliteCategory::Iridium)
    .value("Orbcomm", OrbitFetcher::SatelliteCategory::Orbcomm)
    .value("Globalstar", OrbitFetcher::SatelliteCategory::Globalstar)
    .value("AmateurRadio", OrbitFetcher::SatelliteCategory::AmateurRadio)
    .value("Experimental", OrbitFetcher::SatelliteCategory::Experimental)
    .value("GPSOperational", OrbitFetcher::SatelliteCategory::GPSOperational)
    .value("GlonassOperational", OrbitFetcher::SatelliteCategory::GlonassOperational)
    .value("Galileo", OrbitFetcher::SatelliteCategory::Galileo)
    .value("SatelliteBasedAugmentationSystem", OrbitFetcher::SatelliteCategory::SatelliteBasedAugmentationSystem)
    .value("NavyNavigationSatelliteSystem", OrbitFetcher::SatelliteCategory::NavyNavigationSatelliteSystem)
    .value("RussianLEONavigation", OrbitFetcher::SatelliteCategory::RussianLEONavigation)
    .value("SpaceAndEarthScience", OrbitFetcher::SatelliteCategory::SpaceAndEarthScience)
    .value("Geodetic", OrbitFetcher::SatelliteCategory::Geodetic)
    .value("Engineering", OrbitFetcher::SatelliteCategory::Engineering)
    .value("Education", OrbitFetcher::SatelliteCategory::Education)
    .value("Military", OrbitFetcher::SatelliteCategory::Military)
    .value("RadarCalibration", OrbitFetcher::SatelliteCategory::RadarCalibration)
    .value("CubeSats", OrbitFetcher::SatelliteCategory::CubeSats)
    .value("XMandSirius", OrbitFetcher::SatelliteCategory::XMandSirius)
    .value("TV", OrbitFetcher::SatelliteCategory::TV)
    .value("BeidouNavigationSystem", OrbitFetcher::SatelliteCategory::BeidouNavigationSystem)
    .value("Yaogan", OrbitFetcher::SatelliteCategory::Yaogan)
    .value("WestfordNeedles", OrbitFetcher::SatelliteCategory::WestfordNeedles)
    .value("Parus", OrbitFetcher::SatelliteCategory::Parus)
    .value("Strela", OrbitFetcher::SatelliteCategory::Strela)
    .value("Gonets", OrbitFetcher::SatelliteCategory::Gonets)
    .value("Tsiklon", OrbitFetcher::SatelliteCategory::Tsiklon)
    .value("Tsikada", OrbitFetcher::SatelliteCategory::Tsikada)
    .value("O3BNetworks", OrbitFetcher::SatelliteCategory::O3BNetworks)
    .value("Tselina", OrbitFetcher::SatelliteCategory::Tselina)
    .value("Celestis", OrbitFetcher::SatelliteCategory::Celestis)
    .value("IRNSS", OrbitFetcher::SatelliteCategory::IRNSS)
    .value("QZSS", OrbitFetcher::SatelliteCategory::QZSS)
    .value("Flock", OrbitFetcher::SatelliteCategory::Flock)
    .value("Lemur", OrbitFetcher::SatelliteCategory::Lemur)
    .value("GPSConstellation", OrbitFetcher::SatelliteCategory::GPSConstellation)
    .value("GlonassConstellation", OrbitFetcher::SatelliteCategory::GlonassConstellation)
    .value("Starlink", OrbitFetcher::SatelliteCategory::Starlink)
    .value("OneWeb", OrbitFetcher::SatelliteCategory::OneWeb)
    .value("ChineseSpaceStation", OrbitFetcher::SatelliteCategory::ChineseSpaceStation)
    .value("Qianfan", OrbitFetcher::SatelliteCategory::Qianfan)
    .value("Kuiper", OrbitFetcher::SatelliteCategory::Kuiper);

    // Config
    boost::python::class_<OrbitFetcher::ConfigValues>("ConfigValues")
        .def_readonly("apiKey", &OrbitFetcher::ConfigValues::apiKey)
        .def_readonly("observerLat", &OrbitFetcher::ConfigValues::observerLat)
        .def_readonly("observerLon", &OrbitFetcher::ConfigValues::observerLon)
        .def_readonly("observerAlt", &OrbitFetcher::ConfigValues::observerAlt)
        .def_readonly("searchRadius", &OrbitFetcher::ConfigValues::searchRadius)
        .def_readonly("seconds", &OrbitFetcher::ConfigValues::seconds)
        .def_readonly("days", &OrbitFetcher::ConfigValues::days)
        .def_readonly("minVisibility", &OrbitFetcher::ConfigValues::minVisibility)
        .def_readonly("minElevation", &OrbitFetcher::ConfigValues::minElevation);
    
    boost::python::class_<OrbitFetcher::Config>("Config", boost::python::init<>())
        .def("read", &OrbitFetcher::Config::read)
        .def("getConfigValues", &OrbitFetcher::Config::getConfigValues, boost::python::return_value_policy<boost::python::reference_existing_object>());

    // DataReceiver function overloads
    OrbitFetcher::ResponseData::Tle (OrbitFetcher::DataReceiver::*getTleNoArgs)() = &OrbitFetcher::DataReceiver::getTle;
    OrbitFetcher::ResponseData::Tle (OrbitFetcher::DataReceiver::*getTleWithArgs)(const std::string&, const int&) = &OrbitFetcher::DataReceiver::getTle;

    OrbitFetcher::ResponseData::SatellitePosition (OrbitFetcher::DataReceiver::*getSatellitePositionNoArgs)() = &OrbitFetcher::DataReceiver::getSatellitePosition;
    OrbitFetcher::ResponseData::SatellitePosition (OrbitFetcher::DataReceiver::*getSatellitePositionWithArgs)(
        const std::string&,
        const int&,
        const float&,
        const float&,
        const float&,
        const int&) = &OrbitFetcher::DataReceiver::getSatellitePosition;

    OrbitFetcher::ResponseData::SatelliteVisualPass (OrbitFetcher::DataReceiver::*getSatelliteVisualPassNoArgs)() = &OrbitFetcher::DataReceiver::getSatelliteVisualPass;
    OrbitFetcher::ResponseData::SatelliteVisualPass (OrbitFetcher::DataReceiver::*getSatelliteVisualWithArgs)(
        const std::string&,
        const int&,
        const float&,
        const float&,
        const float&,
        const int&,
        const int&) = &OrbitFetcher::DataReceiver::getSatelliteVisualPass;

    OrbitFetcher::ResponseData::SatelliteRadioPass (OrbitFetcher::DataReceiver::*getSatelliteRadioPassNoArgs)() = &OrbitFetcher::DataReceiver::getSatelliteRadioPass;
    OrbitFetcher::ResponseData::SatelliteRadioPass (OrbitFetcher::DataReceiver::*getSatelliteRadioWithArgs)(
        const std::string&,
        const int&,
        const float&,
        const float&,
        const float&,
        const int&,
        const int&) = &OrbitFetcher::DataReceiver::getSatelliteRadioPass;

    OrbitFetcher::ResponseData::SatellitesAbove (OrbitFetcher::DataReceiver::*getSatellitesAboveNoArgs)() = &OrbitFetcher::DataReceiver::getSatellitesAbove;
    OrbitFetcher::ResponseData::SatellitesAbove (OrbitFetcher::DataReceiver::*getSatellitesAboveWithArgs)(
        const std::string&,
        const float&,
        const float&,
        const float&,
        const int&,
        const OrbitFetcher::SatelliteCategory&) = &OrbitFetcher::DataReceiver::getSatellitesAbove;

    // DataReceiver
    boost::python::class_<OrbitFetcher::DataReceiver>("DataReceiver")
        .def(boost::python::init<>())  // No-argument constructor
        .def(boost::python::init<OrbitFetcher::Config&>())  // Constructor with Config
        .def("getTle", getTleNoArgs)
        .def("getTle", getTleWithArgs)
        .def("getSatellitePosition", getSatellitePositionNoArgs)
        .def("getSatellitePosition", getSatellitePositionWithArgs)
        .def("getSatelliteVisualPass", getSatelliteVisualPassNoArgs)
        .def("getSatelliteVisualPass", getSatelliteVisualWithArgs)
        .def("getSatelliteRadioPass", getSatelliteRadioPassNoArgs)
        .def("getSatelliteRadioPass", getSatelliteRadioWithArgs)
        .def("getSatellitesAbove", getSatellitesAboveNoArgs)
        .def("getSatellitesAbove", getSatellitesAboveWithArgs);

    // Response Data
    boost::python::class_<OrbitFetcher::ResponseData::Tle>("Tle")
        .def_readonly("satId", &OrbitFetcher::ResponseData::Tle::satId)
        .def_readonly("satName", &OrbitFetcher::ResponseData::Tle::satName)
        .def_readonly("transactionCount", &OrbitFetcher::ResponseData::Tle::transactionCount)
        .def_readonly("tle", &OrbitFetcher::ResponseData::Tle::tle);

    boost::python::class_<OrbitFetcher::ResponseData::PositionData>("PositionData")
        .def_readonly("lat", &OrbitFetcher::ResponseData::PositionData::lat)
        .def_readonly("lon", &OrbitFetcher::ResponseData::PositionData::lon)
        .def_readonly("altKm", &OrbitFetcher::ResponseData::PositionData::altKm)
        .def_readonly("azimuth", &OrbitFetcher::ResponseData::PositionData::azimuth)
        .def_readonly("elevation", &OrbitFetcher::ResponseData::PositionData::elevation)
        .def_readonly("rightAscension", &OrbitFetcher::ResponseData::PositionData::rightAscension)
        .def_readonly("declination", &OrbitFetcher::ResponseData::PositionData::declination)
        .def_readonly("timeStamp", &OrbitFetcher::ResponseData::PositionData::timeStamp);

    boost::python::class_<std::vector<OrbitFetcher::ResponseData::PositionData>>("PositionDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<OrbitFetcher::ResponseData::PositionData>>());

    boost::python::class_<OrbitFetcher::ResponseData::SatellitePosition>("SatellitePosition")
        .def_readonly("satId", &OrbitFetcher::ResponseData::SatellitePosition::satId)
        .def_readonly("satName", &OrbitFetcher::ResponseData::SatellitePosition::satName)
        .def_readonly("transactionCount", &OrbitFetcher::ResponseData::SatellitePosition::transactionCount)
        .def_readonly("positionData", &OrbitFetcher::ResponseData::SatellitePosition::positionData);

    boost::python::class_<OrbitFetcher::ResponseData::VisualPassData>("VisualPassData")
        .def_readonly("startAzimuth", &OrbitFetcher::ResponseData::VisualPassData::startAzimuth)
        .def_readonly("startAzimuthCompass", &OrbitFetcher::ResponseData::VisualPassData::startAzimuthCompass)
        .def_readonly("startElevation", &OrbitFetcher::ResponseData::VisualPassData::startElevation)
        .def_readonly("startUTC", &OrbitFetcher::ResponseData::VisualPassData::startUTC)
        .def_readonly("maxAzimuth", &OrbitFetcher::ResponseData::VisualPassData::maxAzimuth)
        .def_readonly("maxAzimuthCompass", &OrbitFetcher::ResponseData::VisualPassData::maxAzimuthCompass)
        .def_readonly("maxElevation", &OrbitFetcher::ResponseData::VisualPassData::maxElevation)
        .def_readonly("maxUTC", &OrbitFetcher::ResponseData::VisualPassData::maxUTC)
        .def_readonly("endAzimuth", &OrbitFetcher::ResponseData::VisualPassData::endAzimuth)
        .def_readonly("endAzimuthCompass", &OrbitFetcher::ResponseData::VisualPassData::endAzimuthCompass)
        .def_readonly("endElevation", &OrbitFetcher::ResponseData::VisualPassData::endElevation)
        .def_readonly("endUTC", &OrbitFetcher::ResponseData::VisualPassData::endUTC)
        .def_readonly("maxVisualMagnitude", &OrbitFetcher::ResponseData::VisualPassData::maxVisualMagnitude)
        .def_readonly("visibleDuration", &OrbitFetcher::ResponseData::VisualPassData::visibleDuration);

    boost::python::class_<std::vector<OrbitFetcher::ResponseData::VisualPassData>>("VisualPassDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<OrbitFetcher::ResponseData::VisualPassData>>());

    boost::python::class_<OrbitFetcher::ResponseData::SatelliteVisualPass>("SatelliteVisualPass")
        .def_readonly("satId", &OrbitFetcher::ResponseData::SatelliteVisualPass::satId)
        .def_readonly("satName", &OrbitFetcher::ResponseData::SatelliteVisualPass::satName)
        .def_readonly("transactionCount", &OrbitFetcher::ResponseData::SatelliteVisualPass::transactionCount)
        .def_readonly("passCount", &OrbitFetcher::ResponseData::SatelliteVisualPass::passCount)
        .def_readonly("visualPassData", &OrbitFetcher::ResponseData::SatelliteVisualPass::visualPassData);

    boost::python::class_<OrbitFetcher::ResponseData::RadioPassData>("RadioPassData")
        .def_readonly("startAzimuth", &OrbitFetcher::ResponseData::RadioPassData::startAzimuth)
        .def_readonly("startAzimuthCompass", &OrbitFetcher::ResponseData::RadioPassData::startAzimuthCompass)
        .def_readonly("startUTC", &OrbitFetcher::ResponseData::RadioPassData::startUTC)
        .def_readonly("maxAzimuth", &OrbitFetcher::ResponseData::RadioPassData::maxAzimuth)
        .def_readonly("maxAzimuthCompass", &OrbitFetcher::ResponseData::RadioPassData::maxAzimuthCompass)
        .def_readonly("maxElevation", &OrbitFetcher::ResponseData::RadioPassData::maxElevation)
        .def_readonly("maxUTC", &OrbitFetcher::ResponseData::RadioPassData::maxUTC)
        .def_readonly("endAzimuth", &OrbitFetcher::ResponseData::RadioPassData::endAzimuth)
        .def_readonly("endAzimuthCompass", &OrbitFetcher::ResponseData::RadioPassData::endAzimuthCompass)
        .def_readonly("endUTC", &OrbitFetcher::ResponseData::RadioPassData::endUTC);

    boost::python::class_<std::vector<OrbitFetcher::ResponseData::RadioPassData>>("RadioPassDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<OrbitFetcher::ResponseData::RadioPassData>>());

    boost::python::class_<OrbitFetcher::ResponseData::SatelliteRadioPass>("SatelliteRadioPass")
        .def_readonly("satId", &OrbitFetcher::ResponseData::SatelliteRadioPass::satId)
        .def_readonly("satName", &OrbitFetcher::ResponseData::SatelliteRadioPass::satName)
        .def_readonly("transactionCount", &OrbitFetcher::ResponseData::SatelliteRadioPass::transactionCount)
        .def_readonly("passCount", &OrbitFetcher::ResponseData::SatelliteRadioPass::passCount)
        .def_readonly("radioPassData", &OrbitFetcher::ResponseData::SatelliteRadioPass::radioPassData);

     boost::python::class_<OrbitFetcher::ResponseData::SatelliteData>("SatelliteData")
        .def_readonly("satId", &OrbitFetcher::ResponseData::SatelliteData::satId)
        .def_readonly("satName", &OrbitFetcher::ResponseData::SatelliteData::satName)
        .def_readonly("internationalDesignator", &OrbitFetcher::ResponseData::SatelliteData::internationalDesignator)
        .def_readonly("launchDate", &OrbitFetcher::ResponseData::SatelliteData::launchDate)
        .def_readonly("lat", &OrbitFetcher::ResponseData::SatelliteData::lat)
        .def_readonly("lon", &OrbitFetcher::ResponseData::SatelliteData::lon)
        .def_readonly("altKm", &OrbitFetcher::ResponseData::SatelliteData::altKm);
    
    boost::python::class_<std::vector<OrbitFetcher::ResponseData::SatelliteData>>("SatelliteDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<OrbitFetcher::ResponseData::SatelliteData>>());

    boost::python::class_<OrbitFetcher::ResponseData::SatellitesAbove>("SatellitesAbove")
        .def_readonly("category", &OrbitFetcher::ResponseData::SatellitesAbove::category)
        .def_readonly("transactionCount", &OrbitFetcher::ResponseData::SatellitesAbove::transactionCount)
        .def_readonly("satelliteCount", &OrbitFetcher::ResponseData::SatellitesAbove::satelliteCount)
        .def_readonly("satellitesAbove", &OrbitFetcher::ResponseData::SatellitesAbove::satellitesAbove);
}