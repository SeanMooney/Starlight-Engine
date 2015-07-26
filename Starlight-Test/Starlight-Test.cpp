#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "STARLIGHT_CORE\Maths\Vec.h"

namespace starlight{
	namespace test{
		BOOST_AUTO_TEST_CASE(Test1){
			using namespace starlight::core::maths;
			Vec3 a={1,1,1};
			Vec3 b={ 2,2,2 };
			Vec3 c={ 3,3,3 };
			BOOST_REQUIRE_EQUAL((a+b),c);
		}
	}
}