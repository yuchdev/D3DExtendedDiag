#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

using namespace boost::unit_test;

// Functional tests

// IMPORTANT: log level should be set to 'messages' to display in in TeamCity
// example --log_level=message

BOOST_AUTO_TEST_SUITE(System3DInfoFunctionalTests);


/// TODO: Create first unit test here
BOOST_AUTO_TEST_CASE(FirstTestCase)
{
    bool unit_test_created = false;
    BOOST_CHECK(unit_test_created);
}



BOOST_AUTO_TEST_SUITE_END()
