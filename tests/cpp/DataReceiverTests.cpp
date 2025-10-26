#include <boost/test/unit_test.hpp>
#include "DataReceiverFixtures.h"

BOOST_FIXTURE_TEST_CASE(testGetTle, DataReceiverFixture)
{
    auto tle = dataReceiver->getTle(apiKey, noradId);
    BOOST_TEST(tle.satId == noradId);
    BOOST_TEST(!tle.satName.empty());
    BOOST_TEST(tle.transactionCount >= 0);
    BOOST_TEST(!tle.tle.empty());
}

BOOST_FIXTURE_TEST_CASE(testGetSatellitePosition, DataReceiverFixture)
{
    auto satellitePositions = dataReceiver->getSatellitePosition(
        apiKey,
        noradId,
        observerLat,
        observerLon,
        observerAlt,
        seconds);

    BOOST_TEST(satellitePositions.satId == noradId);
    BOOST_TEST(!satellitePositions.satName.empty());
    BOOST_TEST(satellitePositions.transactionCount >= 0);
    BOOST_TEST(satellitePositions.positionData.size() == seconds);
};

BOOST_FIXTURE_TEST_CASE(testGetSatelliteVisualPass, DataReceiverFixture)
{
    auto satelliteVisualPass = dataReceiver->getSatelliteVisualPass(
        apiKey,
        noradId,
        observerLat,
        observerLon,
        observerAlt,
        days,
        minimumVisibility);

    BOOST_TEST(satelliteVisualPass.satId == noradId);
    BOOST_TEST(!satelliteVisualPass.satName.empty());
    BOOST_TEST(satelliteVisualPass.transactionCount >= 0);
    BOOST_TEST(satelliteVisualPass.passCount == satelliteVisualPass.visualPassData.size());
};

BOOST_FIXTURE_TEST_CASE(testGetSatelliteRadioPass, DataReceiverFixture)
{
    auto satelliteRadioPass = dataReceiver->getSatelliteRadioPass(
        apiKey,
        noradId,
        observerLat,
        observerLon,
        observerAlt,
        days,
        minimumElevation);
    BOOST_TEST(satelliteRadioPass.satId == noradId);
    BOOST_TEST(!satelliteRadioPass.satName.empty());
    BOOST_TEST(satelliteRadioPass.transactionCount >= 0);
    BOOST_TEST(satelliteRadioPass.passCount == satelliteRadioPass.radioPassData.size());
};

BOOST_FIXTURE_TEST_CASE(testGetSatellitesAbove, DataReceiverFixture)
{
    auto satellitesAbove = dataReceiver->getSatellitesAbove(
        apiKey,
        observerLat,
        observerLon,
        observerAlt,
        searchRadius,
        SatelliteCategory::All);
    BOOST_TEST(satellitesAbove.transactionCount >= 0);
    BOOST_TEST(!satellitesAbove.category.empty());
    BOOST_TEST(!satellitesAbove.satelliteCount >= 0);
};
