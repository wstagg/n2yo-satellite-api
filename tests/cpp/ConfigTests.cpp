#include <boost/test/unit_test.hpp> 
#include "Config.h"

BOOST_AUTO_TEST_CASE(testConfigReadValidFilePath)
{
    Config config{};
    BOOST_TEST(config.read("config.txt") == true);
};

BOOST_AUTO_TEST_CASE(testConfigReadInvalidFilePath)
{
    Config config{};
    BOOST_CHECK_THROW(config.read(""), std::runtime_error);
};

BOOST_AUTO_TEST_CASE(testConfigMissingConfigFileValue)
{
    Config config{};
    BOOST_TEST(config.read("config_tests.txt") == false);
};