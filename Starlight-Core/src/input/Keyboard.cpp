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
#include "STARLIGHT_CORE\input\Keyboard.h"
#pragma once
namespace starlight{
	namespace core{
		namespace input{
			std::unordered_map<starlight::core::graphics::Window*,Keyboard*> Keyboard::keyboardMap={};
			
			void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods){
				using starlight::core::graphics::Window;
				Window* win=static_cast<Window*>(glfwGetWindowUserPointer(window));
				bool& pk=Keyboard::keyboardMap[win]->keys[key];
				bool& hk=Keyboard::keyboardMap[win]->heldKeys[key];
				bool& dirty=Keyboard::keyboardMap[win]->dirty;
				switch(action){
					case GLFW_REPEAT:
					case GLFW_PRESS:
						if(pk)
							hk=pk;
						pk=true;
						break;
					case GLFW_RELEASE:
						hk=pk=false;
						break;
				}
				dirty=true;
			}

			void Keyboard::registerWindowCallback(starlight::core::graphics::Window* window){
				keyboardMap[window]=this;
				glfwSetKeyCallback(window->get(),key_callback);
				
			}

		}
	}
}