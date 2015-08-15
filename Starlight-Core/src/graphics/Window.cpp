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
#include "STARLIGHT_CORE/graphics/window.h"
#include "STARLIGHT_CORE\utils\Log.h"
namespace starlight{
	namespace core{
		namespace graphics{
			Window::Window(int width,int height,const char* title) 
				:width(width),height(height),ratio(width/(float)height){
				init(width,height,title);
				static GLEW glew;
			}
			Window::~Window(){
				destroy();
			}

			void window_size_callback(GLFWwindow* window,int width,int height){
				Window* win=static_cast<Window*>(glfwGetWindowUserPointer(window));
				win->width=width;
				win->height=height;
				win->ratio=width/(float)height;
				glViewport(0,0,width,height);
				starlight::core::utils::Debug()<<"window size changed."<<std::endl
				<< "width: " <<win->width<< ", height:" <<win->height << std::endl;
			}

			void Window::init(int width,int height,const char* title){
				window=glfwCreateWindow(width,height,title,NULL,NULL);
				if(!window)
					THROW("window creation failed");
				glfwMakeContextCurrent(window);
				glViewport(0,0,width,height);
				glfwSetWindowUserPointer(window,this);
				glfwSetWindowSizeCallback(window,window_size_callback);
				glfwSwapInterval(0);

			}

			void Window::destroy(){
				glfwDestroyWindow(window);
			}

			GLFWwindow * Window::get(){
				return window;
			}

		}
	}
}