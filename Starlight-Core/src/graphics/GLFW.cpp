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
#include "STARLIGHT_CORE/graphics/glfw.h"
#include <iostream>
namespace starlight{
	namespace core{
		namespace graphics{
			void GLFW::error_callback(int error,const char* description){
				std::cerr<<"error code: "<<error<<std::endl<<"message: "<<description<<std::endl;
			}


			void GLFW::destroy(){
				glfwTerminate();
				using namespace std;
			}


			GLFW::GLFW(){
				ret=glfwInit();
				if(!ret){
					destroy();
					throw std::exception::exception(" glfwInit failed");
				}
				glfwSetErrorCallback(error_callback);

			}

			GLFW::~GLFW(){
				destroy();
			}
		}
	}
}
