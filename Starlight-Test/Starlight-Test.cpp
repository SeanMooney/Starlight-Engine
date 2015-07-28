#define BOOST_TEST_MAIN
#define __BOOST_TEST_MODULE__ Starlight-Test
#include "STARLIGHT_TEST\Shared.h"
#include "STARLIGHT_CORE\Maths\Vec.h"

namespace starlight{
	namespace test{
		STARLIGHT_TEST_CASE(TEST_BOOST_TEST_FRAMEWORK){
			BOOST_REQUIRE(true);
		}
	}
}
