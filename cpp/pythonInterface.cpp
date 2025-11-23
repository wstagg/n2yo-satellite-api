#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/return_value_policy.hpp>

#include "SatelliteApi/Config.h"
#include "SatelliteApi/DataReceiver.h"
#include "SatelliteApi/ResponseData.h"
#include "SatelliteApi/SatelliteCategories.h"


BOOST_PYTHON_MODULE(n2yoSatelliteApi)
{
    // Satellite categories
    boost::python::enum_<SatelliteApi::SatelliteCategory>("SatelliteApi::SatelliteCategory")
    .value("All", SatelliteApi::SatelliteCategory::All)
    .value("Brightest", SatelliteApi::SatelliteCategory::Brightest)
    .value("ISS", SatelliteApi::SatelliteCategory::ISS)
    .value("Weather", SatelliteApi::SatelliteCategory::Weather)
    .value("NOAA", SatelliteApi::SatelliteCategory::NOAA)
    .value("GOES", SatelliteApi::SatelliteCategory::GOES)
    .value("EarthResources", SatelliteApi::SatelliteCategory::EarthResources)
    .value("SearchAndRescue", SatelliteApi::SatelliteCategory::SearchAndRescue)
    .value("DisasterMonitoring", SatelliteApi::SatelliteCategory::DisasterMonitoring)
    .value("TrackingAndDataRelaySatelliteSystem", SatelliteApi::SatelliteCategory::TrackingAndDataRelaySatelliteSystem)
    .value("Geostationary", SatelliteApi::SatelliteCategory::Geostationary)
    .value("Intelsat", SatelliteApi::SatelliteCategory::Intelsat)
    .value("Gorizont", SatelliteApi::SatelliteCategory::Gorizont)
    .value("Raduga", SatelliteApi::SatelliteCategory::Raduga)
    .value("Molniya", SatelliteApi::SatelliteCategory::Molniya)
    .value("Iridium", SatelliteApi::SatelliteCategory::Iridium)
    .value("Orbcomm", SatelliteApi::SatelliteCategory::Orbcomm)
    .value("Globalstar", SatelliteApi::SatelliteCategory::Globalstar)
    .value("AmateurRadio", SatelliteApi::SatelliteCategory::AmateurRadio)
    .value("Experimental", SatelliteApi::SatelliteCategory::Experimental)
    .value("GPSOperational", SatelliteApi::SatelliteCategory::GPSOperational)
    .value("GlonassOperational", SatelliteApi::SatelliteCategory::GlonassOperational)
    .value("Galileo", SatelliteApi::SatelliteCategory::Galileo)
    .value("SatelliteBasedAugmentationSystem", SatelliteApi::SatelliteCategory::SatelliteBasedAugmentationSystem)
    .value("NavyNavigationSatelliteSystem", SatelliteApi::SatelliteCategory::NavyNavigationSatelliteSystem)
    .value("RussianLEONavigation", SatelliteApi::SatelliteCategory::RussianLEONavigation)
    .value("SpaceAndEarthScience", SatelliteApi::SatelliteCategory::SpaceAndEarthScience)
    .value("Geodetic", SatelliteApi::SatelliteCategory::Geodetic)
    .value("Engineering", SatelliteApi::SatelliteCategory::Engineering)
    .value("Education", SatelliteApi::SatelliteCategory::Education)
    .value("Military", SatelliteApi::SatelliteCategory::Military)
    .value("RadarCalibration", SatelliteApi::SatelliteCategory::RadarCalibration)
    .value("CubeSats", SatelliteApi::SatelliteCategory::CubeSats)
    .value("XMandSirius", SatelliteApi::SatelliteCategory::XMandSirius)
    .value("TV", SatelliteApi::SatelliteCategory::TV)
    .value("BeidouNavigationSystem", SatelliteApi::SatelliteCategory::BeidouNavigationSystem)
    .value("Yaogan", SatelliteApi::SatelliteCategory::Yaogan)
    .value("WestfordNeedles", SatelliteApi::SatelliteCategory::WestfordNeedles)
    .value("Parus", SatelliteApi::SatelliteCategory::Parus)
    .value("Strela", SatelliteApi::SatelliteCategory::Strela)
    .value("Gonets", SatelliteApi::SatelliteCategory::Gonets)
    .value("Tsiklon", SatelliteApi::SatelliteCategory::Tsiklon)
    .value("Tsikada", SatelliteApi::SatelliteCategory::Tsikada)
    .value("O3BNetworks", SatelliteApi::SatelliteCategory::O3BNetworks)
    .value("Tselina", SatelliteApi::SatelliteCategory::Tselina)
    .value("Celestis", SatelliteApi::SatelliteCategory::Celestis)
    .value("IRNSS", SatelliteApi::SatelliteCategory::IRNSS)
    .value("QZSS", SatelliteApi::SatelliteCategory::QZSS)
    .value("Flock", SatelliteApi::SatelliteCategory::Flock)
    .value("Lemur", SatelliteApi::SatelliteCategory::Lemur)
    .value("GPSConstellation", SatelliteApi::SatelliteCategory::GPSConstellation)
    .value("GlonassConstellation", SatelliteApi::SatelliteCategory::GlonassConstellation)
    .value("Starlink", SatelliteApi::SatelliteCategory::Starlink)
    .value("OneWeb", SatelliteApi::SatelliteCategory::OneWeb)
    .value("ChineseSpaceStation", SatelliteApi::SatelliteCategory::ChineseSpaceStation)
    .value("Qianfan", SatelliteApi::SatelliteCategory::Qianfan)
    .value("Kuiper", SatelliteApi::SatelliteCategory::Kuiper);

    // Config
    boost::python::class_<SatelliteApi::ConfigValues>("ConfigValues")
        .def_readonly("apiKey", &SatelliteApi::ConfigValues::apiKey)
        .def_readonly("observerLat", &SatelliteApi::ConfigValues::observerLat)
        .def_readonly("observerLon", &SatelliteApi::ConfigValues::observerLon)
        .def_readonly("observerAlt", &SatelliteApi::ConfigValues::observerAlt)
        .def_readonly("searchRadius", &SatelliteApi::ConfigValues::searchRadius)
        .def_readonly("seconds", &SatelliteApi::ConfigValues::seconds)
        .def_readonly("days", &SatelliteApi::ConfigValues::days)
        .def_readonly("minVisibility", &SatelliteApi::ConfigValues::minVisibility)
        .def_readonly("minElevation", &SatelliteApi::ConfigValues::minElevation);
    
    boost::python::class_<SatelliteApi::Config>("Config", boost::python::init<>())
        .def("read", &SatelliteApi::Config::read)
        .def("getConfigValues", &SatelliteApi::Config::getConfigValues, boost::python::return_value_policy<boost::python::reference_existing_object>());

    // DataReceiver function overloads
    SatelliteApi::ResponseData::Tle (SatelliteApi::DataReceiver::*getTleNoArgs)() = &SatelliteApi::DataReceiver::getTle;
    SatelliteApi::ResponseData::Tle (SatelliteApi::DataReceiver::*getTleWithArgs)(const std::string&, const int&) = &SatelliteApi::DataReceiver::getTle;

    SatelliteApi::ResponseData::SatellitePosition (SatelliteApi::DataReceiver::*getSatellitePositionNoArgs)() = &SatelliteApi::DataReceiver::getSatellitePosition;
    SatelliteApi::ResponseData::SatellitePosition (SatelliteApi::DataReceiver::*getSatellitePositionWithArgs)(
        const std::string&,
        const int&,
        const float&,
        const float&,
        const float&,
        const int&) = &SatelliteApi::DataReceiver::getSatellitePosition;

    SatelliteApi::ResponseData::SatelliteVisualPass (SatelliteApi::DataReceiver::*getSatelliteVisualPassNoArgs)() = &SatelliteApi::DataReceiver::getSatelliteVisualPass;
    SatelliteApi::ResponseData::SatelliteVisualPass (SatelliteApi::DataReceiver::*getSatelliteVisualWithArgs)(
        const std::string&,
        const int&,
        const float&,
        const float&,
        const float&,
        const int&,
        const int&) = &SatelliteApi::DataReceiver::getSatelliteVisualPass;

    SatelliteApi::ResponseData::SatelliteRadioPass (SatelliteApi::DataReceiver::*getSatelliteRadioPassNoArgs)() = &SatelliteApi::DataReceiver::getSatelliteRadioPass;
    SatelliteApi::ResponseData::SatelliteRadioPass (SatelliteApi::DataReceiver::*getSatelliteRadioWithArgs)(
        const std::string&,
        const int&,
        const float&,
        const float&,
        const float&,
        const int&,
        const int&) = &SatelliteApi::DataReceiver::getSatelliteRadioPass;

 SatelliteApi::ResponseData::SatellitesAbove (SatelliteApi::DataReceiver::*getSatellitesAboveNoArgs)() = &SatelliteApi::DataReceiver::getSatellitesAbove;
SatelliteApi::ResponseData::SatellitesAbove (SatelliteApi::DataReceiver::*getSatellitesAboveWithArgs)(
        const std::string&,
        const float&,
        const float&,
        const float&,
        const int&,
        const SatelliteApi::SatelliteCategory&) = &SatelliteApi::DataReceiver::getSatellitesAbove;

    // DataReceiver
    // TODO add overloaded constructor
    boost::python::class_<SatelliteApi::DataReceiver>("DataReceiver", boost::python::init<SatelliteApi::Config&>())
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
    boost::python::class_<SatelliteApi::ResponseData::Tle>("Tle")
        .def_readonly("satId", &SatelliteApi::ResponseData::Tle::satId)
        .def_readonly("satName", &SatelliteApi::ResponseData::Tle::satName)
        .def_readonly("transactionCount", &SatelliteApi::ResponseData::Tle::transactionCount)
        .def_readonly("tle", &SatelliteApi::ResponseData::Tle::tle);

    boost::python::class_<SatelliteApi::ResponseData::PositionData>("PositionData")
        .def_readonly("lat", &SatelliteApi::ResponseData::PositionData::lat)
        .def_readonly("lon", &SatelliteApi::ResponseData::PositionData::lon)
        .def_readonly("altKm", &SatelliteApi::ResponseData::PositionData::altKm)
        .def_readonly("azimuth", &SatelliteApi::ResponseData::PositionData::azimuth)
        .def_readonly("elevation", &SatelliteApi::ResponseData::PositionData::elevation)
        .def_readonly("rightAscension", &SatelliteApi::ResponseData::PositionData::rightAscension)
        .def_readonly("declination", &SatelliteApi::ResponseData::PositionData::declination)
        .def_readonly("timeStamp", &SatelliteApi::ResponseData::PositionData::timeStamp);

    boost::python::class_<std::vector<SatelliteApi::ResponseData::PositionData>>("PositionDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<SatelliteApi::ResponseData::PositionData>>());

    boost::python::class_<SatelliteApi::ResponseData::SatellitePosition>("SatellitePosition")
        .def_readonly("satId", &SatelliteApi::ResponseData::SatellitePosition::satId)
        .def_readonly("satName", &SatelliteApi::ResponseData::SatellitePosition::satName)
        .def_readonly("transactionCount", &SatelliteApi::ResponseData::SatellitePosition::transactionCount)
        .def_readonly("positionData", &SatelliteApi::ResponseData::SatellitePosition::positionData);

    boost::python::class_<SatelliteApi::ResponseData::VisualPassData>("VisualPassData")
        .def_readonly("startAzimuth", &SatelliteApi::ResponseData::VisualPassData::startAzimuth)
        .def_readonly("startAzimuthCompass", &SatelliteApi::ResponseData::VisualPassData::startAzimuthCompass)
        .def_readonly("startElevation", &SatelliteApi::ResponseData::VisualPassData::startElevation)
        .def_readonly("startUTC", &SatelliteApi::ResponseData::VisualPassData::startUTC)
        .def_readonly("maxAzimuth", &SatelliteApi::ResponseData::VisualPassData::maxAzimuth)
        .def_readonly("maxAzimuthCompass", &SatelliteApi::ResponseData::VisualPassData::maxAzimuthCompass)
        .def_readonly("maxElevation", &SatelliteApi::ResponseData::VisualPassData::maxElevation)
        .def_readonly("maxUTC", &SatelliteApi::ResponseData::VisualPassData::maxUTC)
        .def_readonly("endAzimuth", &SatelliteApi::ResponseData::VisualPassData::endAzimuth)
        .def_readonly("endAzimuthCompass", &SatelliteApi::ResponseData::VisualPassData::endAzimuthCompass)
        .def_readonly("endElevation", &SatelliteApi::ResponseData::VisualPassData::endElevation)
        .def_readonly("endUTC", &SatelliteApi::ResponseData::VisualPassData::endUTC)
        .def_readonly("maxVisualMagnitude", &SatelliteApi::ResponseData::VisualPassData::maxVisualMagnitude)
        .def_readonly("visibleDuration", &SatelliteApi::ResponseData::VisualPassData::visibleDuration);

    boost::python::class_<std::vector<SatelliteApi::ResponseData::VisualPassData>>("VisualPassDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<SatelliteApi::ResponseData::VisualPassData>>());

    boost::python::class_<SatelliteApi::ResponseData::SatelliteVisualPass>("SatelliteVisualPass")
        .def_readonly("satId", &SatelliteApi::ResponseData::SatelliteVisualPass::satId)
        .def_readonly("satName", &SatelliteApi::ResponseData::SatelliteVisualPass::satName)
        .def_readonly("transactionCount", &SatelliteApi::ResponseData::SatelliteVisualPass::transactionCount)
        .def_readonly("passCount", &SatelliteApi::ResponseData::SatelliteVisualPass::passCount)
        .def_readonly("visualPassData", &SatelliteApi::ResponseData::SatelliteVisualPass::visualPassData);

    boost::python::class_<SatelliteApi::ResponseData::RadioPassData>("RadioPassData")
        .def_readonly("startAzimuth", &SatelliteApi::ResponseData::RadioPassData::startAzimuth)
        .def_readonly("startAzimuthCompass", &SatelliteApi::ResponseData::RadioPassData::startAzimuthCompass)
        .def_readonly("startUTC", &SatelliteApi::ResponseData::RadioPassData::startUTC)
        .def_readonly("maxAzimuth", &SatelliteApi::ResponseData::RadioPassData::maxAzimuth)
        .def_readonly("maxAzimuthCompass", &SatelliteApi::ResponseData::RadioPassData::maxAzimuthCompass)
        .def_readonly("maxElevation", &SatelliteApi::ResponseData::RadioPassData::maxElevation)
        .def_readonly("maxUTC", &SatelliteApi::ResponseData::RadioPassData::maxUTC)
        .def_readonly("endAzimuth", &SatelliteApi::ResponseData::RadioPassData::endAzimuth)
        .def_readonly("endAzimuthCompass", &SatelliteApi::ResponseData::RadioPassData::endAzimuthCompass)
        .def_readonly("endUTC", &SatelliteApi::ResponseData::RadioPassData::endUTC);

    boost::python::class_<std::vector<SatelliteApi::ResponseData::RadioPassData>>("RadioPassDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<SatelliteApi::ResponseData::RadioPassData>>());

    boost::python::class_<SatelliteApi::ResponseData::SatelliteRadioPass>("SatelliteRadioPass")
        .def_readonly("satId", &SatelliteApi::ResponseData::SatelliteRadioPass::satId)
        .def_readonly("satName", &SatelliteApi::ResponseData::SatelliteRadioPass::satName)
        .def_readonly("transactionCount", &SatelliteApi::ResponseData::SatelliteRadioPass::transactionCount)
        .def_readonly("passCount", &SatelliteApi::ResponseData::SatelliteRadioPass::passCount)
        .def_readonly("radioPassData", &SatelliteApi::ResponseData::SatelliteRadioPass::radioPassData);

     boost::python::class_<SatelliteApi::ResponseData::SatelliteData>("SatelliteData")
        .def_readonly("satId", &SatelliteApi::ResponseData::SatelliteData::satId)
        .def_readonly("satName", &SatelliteApi::ResponseData::SatelliteData::satName)
        .def_readonly("internationalDesignator", &SatelliteApi::ResponseData::SatelliteData::internationalDesignator)
        .def_readonly("launchDate", &SatelliteApi::ResponseData::SatelliteData::launchDate)
        .def_readonly("lat", &SatelliteApi::ResponseData::SatelliteData::lat)
        .def_readonly("lon", &SatelliteApi::ResponseData::SatelliteData::lon)
        .def_readonly("altKm", &SatelliteApi::ResponseData::SatelliteData::altKm);
    
    boost::python::class_<std::vector<SatelliteApi::ResponseData::SatelliteData>>("SatelliteDataVector")
        .def(boost::python::vector_indexing_suite<std::vector<SatelliteApi::ResponseData::SatelliteData>>());

    boost::python::class_<SatelliteApi::ResponseData::SatellitesAbove>("SatellitesAbove")
        .def_readonly("category", &SatelliteApi::ResponseData::SatellitesAbove::category)
        .def_readonly("transactionCount", &SatelliteApi::ResponseData::SatellitesAbove::transactionCount)
        .def_readonly("satelliteCount", &SatelliteApi::ResponseData::SatellitesAbove::satelliteCount)
        .def_readonly("satellitesAbove", &SatelliteApi::ResponseData::SatellitesAbove::satellitesAbove);
}