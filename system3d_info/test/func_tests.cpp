#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <exception>
#include <stdexcept>

#include "d3dcore/d3d_info.h"
#include "system3d_info/graphic_container.h"
#include "system3d_info/console_visitor.h"
#include "system3d_info/graphic_visitor.h"

using namespace boost::unit_test;

// Functional tests

// IMPORTANT: log level should be set to 'messages' to display in in TeamCity
// example --log_level=message

BOOST_AUTO_TEST_SUITE(D3DCoreFunctionalTests);

using namespace d3dcore;
using namespace system3d_info;

D3DInfo<GraphicContainer> d3d_info;
ConsoleVisitor console_visitor;


bool failure_initialization(const std::runtime_error & ex)
{
	BOOST_CHECK_EQUAL(ex.what(), std::string("Can not CoInitialize() COM"));
	return true;
}
///
/// case_init_fail: test case for exception of wrong initialize of directX version
///

BOOST_AUTO_TEST_CASE(case_init_fail)
{
	BOOST_CHECK_EXCEPTION(d3d_info.init(1234) //wrong id of directX version
		, std::runtime_error, failure_initialization);
}
///
/// case_number_container: test case for checking the number of container
///
BOOST_AUTO_TEST_CASE(case_number_container)
{

	d3d_info.init();
	d3d_info.query_info();
	auto root_container = d3d_info.get_root_container();
	int nb_children = root_container->get_children_containers().size();
	BOOST_CHECK(nb_children > 0);
}





BOOST_AUTO_TEST_SUITE_END()
