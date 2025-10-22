#include <boost/test/unit_test.hpp> 
#include "DataReceiverFixture.h"
#include "ApiType.h"

BOOST_FIXTURE_TEST_CASE(testGetTle, DataReceiverFixture)
{
    BOOST_REQUIRE(configReadSuccess);
    auto tle = dataReceiver->getTle();
    BOOST_TEST(tle.satId == config.getConfigValues().noradId);
    BOOST_TEST(!tle.satName.empty());
    BOOST_TEST(tle.transactionCount >= 0);
    BOOST_TEST(!tle.tle.empty());
};

BOOST_FIXTURE_TEST_CASE(testGetSatellitePosition, DataReceiverFixture)
{
    BOOST_REQUIRE(configReadSuccess);
    auto satellitePositions = dataReceiver->getSatellitePosition();
    BOOST_TEST(satellitePositions.satId == config.getConfigValues().noradId);
    BOOST_TEST(!satellitePositions.satName.empty());
    BOOST_TEST(satellitePositions.transactionCount >= 0);
    BOOST_TEST(satellitePositions.positionData.size() == config.getConfigValues().seconds);
};

BOOST_FIXTURE_TEST_CASE(testGetSatelliteVisualPass, DataReceiverFixture)
{
    BOOST_REQUIRE(configReadSuccess);
    auto satelliteVisualPass = dataReceiver->getSatelliteVisualPass();
    BOOST_TEST(satelliteVisualPass.satId == config.getConfigValues().noradId);
    BOOST_TEST(!satelliteVisualPass.satName.empty());
    BOOST_TEST(satelliteVisualPass.transactionCount >= 0);
    BOOST_TEST(satelliteVisualPass.passCount == satelliteVisualPass.visualPassData.size());
};

BOOST_FIXTURE_TEST_CASE(testGetSatelliteRadioPass, DataReceiverFixture)
{
    BOOST_REQUIRE(configReadSuccess);
    auto satelliteRadioPass = dataReceiver->getSatelliteRadioPass();
    BOOST_TEST(satelliteRadioPass.satId == config.getConfigValues().noradId);
    BOOST_TEST(!satelliteRadioPass.satName.empty());
    BOOST_TEST(satelliteRadioPass.transactionCount >= 0);
    BOOST_TEST(satelliteRadioPass.passCount == satelliteRadioPass.radioPassData.size());
};

BOOST_FIXTURE_TEST_CASE(testGetSatellitesAbove, DataReceiverFixture)
{
    BOOST_REQUIRE(configReadSuccess);
    auto satellitesAbove = dataReceiver->getSatellitesAbove();
    BOOST_TEST(satellitesAbove.transactionCount >= 0);
    BOOST_TEST(!satellitesAbove.category.empty());
    BOOST_TEST(!satellitesAbove.satelliteCount >= 0);
};
