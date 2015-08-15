/*Copyright 2015 Sean Mooney

Licensed under the Apache License,Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/
#include "STARLIGHT_TEST\Shared.h"
#include "STARLIGHT_CORE\Maths\Vec.h"


namespace starlight{
	namespace test{
		namespace core{
			namespace maths{
				using namespace starlight::core::maths;
				template <typename T>
				T init_vec(STARLIGHT_PRECISSION val){
					T ret;
					for(int i=0; i<T::dimension;i++)
						ret.data_array[i]=val;
					return std::move(ret);
				};

#define STARLIGHT_TEST_CASE_VEC(testCaseName) \
	template <typename T> \
	void testCaseName();\
	BOOST_AUTO_TEST_CASE(testCaseName##Vec1){ \
		testCaseName<Vec1>();\
		std::cout<<#testCaseName<<" Vec1 passed"<<std::endl;\
	}\
	BOOST_AUTO_TEST_CASE(testCaseName##Vec2){ \
		testCaseName<Vec2>();\
		std::cout<<#testCaseName<<" Vec2 passed"<<std::endl;\
	}\
	BOOST_AUTO_TEST_CASE(testCaseName##Vec3){ \
		testCaseName<Vec3>();\
		std::cout<<#testCaseName<<" Vec3 passed"<<std::endl;\
	}\
	BOOST_AUTO_TEST_CASE(testCaseName##Vec4){ \
		testCaseName<Vec4>();\
		std::cout<<#testCaseName<<" Vec4 passed"<<std::endl;\
	}\
	template <typename T> \
	void testCaseName()
				
				STARLIGHT_TEST_CASE(vec1_initlist){
					typedef  Vec1 testclass;
					testclass a=init_vec<testclass>(1.0f);
					testclass b={ 1 };
					Assert::That(a).Should().Be(b,L"a==b");
				}

				STARLIGHT_TEST_CASE(vec2_initlist){
					typedef  Vec2 testclass;
					testclass a=init_vec<testclass>(1.0f);
					testclass b={ 1,1 };
					Assert::That(a).Should().Be(b,L"a==b");
				}

				STARLIGHT_TEST_CASE(vec3_initlist){
					typedef  Vec3 testclass;
					testclass a=init_vec<testclass>(1.0f);
					testclass b={ 1,1,1 };
					Assert::That(a).Should().Be(b,L"a==b");
				}

				STARLIGHT_TEST_CASE(vec4_initlist){
					typedef  Vec4 testclass;
					testclass a=init_vec<testclass>(1.0f);
					testclass b={ 1,1,1,1 };
					Assert::That(a).Should().Be(b,L"a==b");
				}

				STARLIGHT_TEST_CASE_VEC(equal_vec){
					T&& a=init_vec<T>(1.0f);
					T&& b=init_vec<T>(1.0f);
					Assert::That(a).Should().Be(b,L"1==1");
				}

				STARLIGHT_TEST_CASE_VEC(not_equal_vec){
					T& a=init_vec<T>(1.0f);
					T& b=init_vec<T>(2.0f);
					Assert::That(a).Should().NotBe(b,L"1!=2");
				}
				STARLIGHT_TEST_CASE_VEC(less_vec){
					T& a=init_vec<T>(1.0f);
					T& b=init_vec<T>(2.0f);
					Assert::That(a<b).Should().Be(true,L"1!=2");
				}

				STARLIGHT_TEST_CASE_VEC(add_vec){
					T& a=init_vec<T>(1.0f);
					T& b=init_vec<T>(2.0f);
					T& c=init_vec<T>(3.0f);
					Assert::That(a+b).Should().Be(c,L"1+2=3");
				}

				STARLIGHT_TEST_CASE_VEC(subtract_vec){
					T& a=init_vec<T>(1.0f);
					T& b=init_vec<T>(2.0f);
					T& c=init_vec<T>(3.0f);
					Assert::That(c-b).Should().Be(a,L"3-2=1");
				}

				STARLIGHT_TEST_CASE_VEC(multiply_vec){
					T& a=init_vec<T>(2.0f);
					T& b=init_vec<T>(3.0f);
					T& c=init_vec<T>(6.0f);
					Assert::That(a*b).Should().Be(c,L"1*2=2");
				}

				STARLIGHT_TEST_CASE_VEC(devide_vec){
					T& a=init_vec<T>(6.0f);
					T& b=init_vec<T>(3.0f);
					T& c=init_vec<T>(2.0f);
					Assert::That(a/b).Should().Be(c,L"6/2=3");
				}
			}
		}
	}
}