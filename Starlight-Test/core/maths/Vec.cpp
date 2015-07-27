#include "STARLIGHT_TEST\Shared.h"
#include "STARLIGHT_CORE\Maths\Vec.h"

namespace starlight{
	namespace test{
		namespace core{
			namespace maths{
				BOOST_AUTO_TEST_CASE(add_vec3){
					using namespace starlight::core::maths;
					using namespace evolutional::Chamois;
					Vec3 a={ 1,1,1 };
					Vec3 b={ 2,2,2 };
					Vec3 c={ 3,3,3 };
					Assert::That(a+b).Should().Be(c,L"1+2=3");
				}
			}
		}
	}
}