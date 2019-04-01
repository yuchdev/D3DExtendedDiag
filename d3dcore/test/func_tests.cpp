#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <d3dcore/d3d_core.h>

using namespace d3dcore;
using namespace boost::unit_test;

// Functional tests

// IMPORTANT: log level should be set to 'messages' to display in in TeamCity
// example --log_level=message

BOOST_AUTO_TEST_SUITE(D3DCoreFunctionalTests);


/// TODO: Create first unit test here
BOOST_AUTO_TEST_CASE(FirstTestCase)
{
    D3DInfo d3d_info;
    d3d_info.traverse();

    bool unit_test_created = false;
    BOOST_CHECK(unit_test_created);
}



BOOST_AUTO_TEST_SUITE_END()
