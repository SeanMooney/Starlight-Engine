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
#include "STARLIGHT_CORE/input/InputManager.h"

namespace starlight{
	namespace core{
		namespace input{

			void InputManager::registerWindowCallback(starlight::core::graphics::Window * window){
				keyboard.registerWindowCallback(window);
				mouse.registerWindowCallback(window);
			}
			void InputManager::pollEvents(){
				if(keyboard.dirty){
					for(auto it:keyEvents){
						if(keyboard.keys[it.first.first]&&keyboard.heldKeys[it.first.first]==it.first.second){
							inputEvents.push_back(it.second);
						}
					}
					keyboard.dirty=false;
				}
				if(mouse.dirty){
					for(auto it:mouseEvents){
						if(mouse.buttons[it.first]) inputEvents.push_back(it.second);
					}
					mouse.dirty=false;
				}
			}
			void InputManager::processEvents(){
				while(!inputEvents.empty()){
					auto func=inputEvents.back();
					inputEvents.pop_back();
					func();
				}
			}
			void InputManager::registerKeyboardEvent(std::pair<Keycodes,bool> key,std::function<void()> func){
				keyEvents[key]=func;
			}
			void InputManager::registerMouseEvent(MouseButtons button,std::function<void()> func){
				mouseEvents[button]=func;
			}
			const  starlight::core::maths::Vec2& InputManager::getMouseLocation() const{
				return mouse.pos;
			}
		}
	}
}