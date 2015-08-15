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

#include <sstream>

#include "STARLIGHT_TEST\Shared.h"
#include "STARLIGHT_CORE\Maths\Vec.h"
#include "STARLIGHT_CORE\Maths\Matrix.h"


namespace starlight{
	namespace test{
		namespace core{
			namespace maths{
				using namespace starlight::core::maths;
				
				STARLIGHT_TEST_CASE(TEST_CREATE_MAT4){
					Matrix4 matrix;
					for(auto x : matrix.data_array)
						Assert::That(x).Should().Be(0,L"matrix should default to all 0s");
				}
				
				STARLIGHT_TEST_CASE(TEST_MAT4_DIAGONAL){
					Matrix4 matrix(1.0f);
					for(int i=0,offset=0; i<Matrix4::dimension*Matrix4::dimension; i++){
						if(i==offset+offset*Matrix4::dimension){
							++offset;
							Assert::That(matrix.data_array[i]).Should().Be(1,L"Diagonal elments should be 1");
						} else
							Assert::That(matrix.data_array[i]).Should().Be(0,L"Off Diagonal elments should be 0");
					}
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_EQUALITY){
					Matrix4 a(1.0f);
					Matrix4 b(1.0f);
					Assert::That(a==b).Should().Be(true,L"a should equal b");
				}
				
				STARLIGHT_TEST_CASE(TEST_MAT4_INITLIST){
					Matrix4 actual={ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
					Matrix4 expected(1);
					Assert::That(actual).Should().Be(expected,L"actual == expected");
				}
				
				STARLIGHT_TEST_CASE(TEST_MAT4_IDENTITY){
					Matrix4 actual=Matrix4::identity();
					Matrix4 expected(1.0f);
					Assert::That(actual).Should().Be(expected,L"identity is equal to diagonal of 1");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_ADD){
					Matrix4 expected(3.0f);
					Matrix4 a(1.0f);
					Matrix4 b(2.0f);
					Assert::That(a+b).Should().Be(expected,L"1+2==3");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_SUBTRACT){
					Matrix4 expected(1.0f);
					Matrix4 a(3.0f);
					Matrix4 b(2.0f);
					Assert::That(a-b).Should().Be(expected,L"3-2==1");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_MULTIPLY){
					Matrix4 identity=Matrix4::identity();
					Matrix4 a(3.0f);
					Matrix4 b(2.0f);
					Matrix4 c(6.0f);
					Assert::That(a*identity).Should().Be(a,L"3-2==1");
					Assert::That(a*b).Should().Be(c,L"2*3==6");
				}
				STARLIGHT_TEST_CASE(TEST_MAT4_SCALAR_ADD){
					Matrix4 expected;
					for(auto& x:expected.data_array)
						x=1;
					Matrix4 zero;
					Assert::That(zero+1).Should().Be(expected,L"0+1==1");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_SCALAR_SUBTRACT){
					Matrix4 expected;
					for(auto& x:expected.data_array)
						x=1;
					Matrix4 two;
					for(auto& x:two.data_array)
						x=2;
					Assert::That(two-1).Should().Be(expected,L"2-1==1");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_SCALAR_MULTIPLY){
					Matrix4 a(1.0f);
					Matrix4 expected(3.0f);
					Assert::That(a*3).Should().Be(expected,L"1*3==3");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_SCALAR_DEVIDE){
					Matrix4 expected(1.0f);
					Matrix4 a(3.0f);
					Assert::That(a/3).Should().Be(expected,L"3/3==1");
				}
				
				STARLIGHT_TEST_CASE(TEST_MAT4_SERIALIES){
					Matrix4 test(1.0f);
					std::string expected="matrix:{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}";
					std::stringstream out;
					out<<test;
					Assert::That(out.str()).Should().Be(expected,L"diaganonl 1 ");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_VEC3){
					Matrix4 test(1.0f);
					Matrix4 test2(2.0f);
					Vec3 v(1.0f,1.0f,1.0f);
					Vec3 v2(2.0f,2.0f,2.0f);
					Assert::That(test*v).Should().Be(v,L"mat4*vec3");
					Assert::That(test2*v).Should().Be(v2,L"mat4*vec3");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_VEC4){
					Matrix4 test(1.0f);
					Matrix4 test2(2.0f);
					Vec4 v(1.0f,1.0f,1.0f,1.0f);
					Vec4 v2(2.0f,2.0f,2.0f,2.0f);
					Assert::That(test*v).Should().Be(v,L"mat4*vec3");
					Assert::That(test2*v).Should().Be(v2,L"mat4*vec3");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_LESS){
					Matrix4 test(1.0f);
					Matrix4 test2(2.0f);
					Assert::That(test<test2).Should().Be(true,L"1<2");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_SCALE){
					Vec3 scale(1,2,3);
					Vec3 base(2,2,2);
					Vec3 scaled(2,4,6);
					Matrix4 test=Matrix4::scale(scale);
					Assert::That(test.data[0].x).Should().Be(1,L"x scale == 1");
					Assert::That(test.data[1].y).Should().Be(2,L"y scale == 2");
					Assert::That(test.data[2].z).Should().Be(3,L"z scale == 3");
					Assert::That(test.data[3].w).Should().Be(1,L"w scale == 1");
					Assert::That(test*base).Should().Be(scaled,L"w scale == 1");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_ROTATE){
					Vec3 base(2,2,2);
					Vec3 expected(-2,-2,2);
					Matrix4 test=Matrix4::rotation(180,Vec3(0,0,1));
					Vec3 actual=test*base;
					Assert::That(actual).Should().Be(expected,L"actual == expected");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_ORTO){
					Vec3 point(1920/2,1080/2,1000);
					Vec3 normalised(1,1,-1);
					Matrix4 actual=Matrix4::orthographic(-point.data.x,point.data.x,-point.data.y,point.data.y,10,point.data.z);
					Matrix4 expected={ 0.00104167f,0.0f,0.0f,0.0f,0.0f,0.00185185f,0.0f,0.0f,0.0f,0.0f,-0.0020202f,0.0f,0.0f,0.0f,1.0202f,1.0f };
					Assert::That(actual).Should().Be(expected,L"actual == expected");
					Vec3 transformed=actual*point;
					Assert::That(transformed).Should().Be(normalised,L"transformed == normalised");
				}
				
				STARLIGHT_TEST_CASE(TEST_MAT4_PERSPECTIVE){
					Matrix4 actual=Matrix4::perspective(90,1920/1080.0,10,1000);
					Matrix4 expected={ 0.5625f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,-1.0202f,-1.0f,0.0f,0.0f,-20.202f,1.0f };
					Assert::That(actual).Should().Be(expected,L"actual == expected");
				}

				STARLIGHT_TEST_CASE(TEST_MAT4_TRANSLATION){
					Vec3 point(3,2,1);
					Vec3 translated(4,4,4);
					Matrix4 actual=Matrix4::translation(Vec3(1,2,3));
					Matrix4 expected={ 1,0,0,0,0,1,0,0,0,0,1,0,1,2,3,1 };
					Assert::That(actual).Should().Be(expected,L"actual == expected");
					Assert::That(actual*point).Should().Be(translated,L"translation*point == translated");
				}
				

			}
		}
	}
}