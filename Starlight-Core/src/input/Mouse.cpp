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
#include "STARLIGHT_CORE\input\Mouse.h"


namespace starlight{
	namespace core{
		namespace input{
			std::unordered_map<starlight::core::graphics::Window*,Mouse*> Mouse::mouseMap={};

			/*! @brief The function signature for mouse button callbacks.
			*  @param[in] window The window that received the event.
			*  @param[in] button The [mouse button](@ref buttons) that was pressed or
			*  released.
			*  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.
			*  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
			*  held down.
			*/
			void button_callback(GLFWwindow * window,int button,int action,int modifer){
				using starlight::core::graphics::Window;
				Window* win=static_cast<Window*>(glfwGetWindowUserPointer(window));
				bool& b=Mouse::mouseMap[win]->buttons[button];
				switch(action){
					case GLFW_PRESS:
						b=true;
						break;
					case GLFW_RELEASE:
						b=false;
						break;
				}
				Mouse::mouseMap[win]->dirty=true;
			}

			void cursor_callback(GLFWwindow* window,double x,double y){
				using starlight::core::graphics::Window;
				Window* win=static_cast<Window*>(glfwGetWindowUserPointer(window));
				Mouse* m=Mouse::mouseMap[win];
				m->pos.data.x=x;
				m->pos.data.y=y;
				m->dirty=true;
			}

			void Mouse::registerWindowCallback(starlight::core::graphics::Window* window){
				mouseMap[window]=this;
				glfwSetMouseButtonCallback(window->get(),button_callback);
				glfwSetCursorPosCallback(window->get(),cursor_callback);
			}
		}
	}
}