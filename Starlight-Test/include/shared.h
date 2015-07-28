#pragma once
#include "boost\test\unit_test.hpp"
#define BOOST_TEST_MODULE Starlight-Test
#include "CHAMOIS\Chamois.hpp"
namespace starlight{
	namespace test{
		using namespace evolutional::Chamois;

#define STARLIGHT_TEST_CASE(testCaseName) \
	void testCaseName();\
	BOOST_AUTO_TEST_CASE(testCaseName##_){ \
		testCaseName();\
		std::cout<<#testCaseName<<" passed"<<std::endl;\
	}\
	void testCaseName()

	}
}

