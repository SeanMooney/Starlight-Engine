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
#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "STARLIGHT_CORE\graphics\window.h"
#include "STARLIGHT_CORE\Maths\Vec.h"
#include <vector>
#include <map>
#include <functional>
namespace starlight{
	namespace core{
		namespace input{
			class STARLIGHTAPI InputManager{
			private:
				std::map<std::pair<Keycodes,bool>,std::function<void()>> keyEvents;
				std::map<MouseButtons,std::function<void()>> mouseEvents;
				std::vector<std::function<void()>> inputEvents;
				Keyboard keyboard;
				Mouse mouse;
			public:
				
				InputManager()=default;
				~InputManager()=default;
				void registerWindowCallback(starlight::core::graphics::Window* window);
				void pollEvents();
				void processEvents();
				void registerKeyboardEvent(std::pair<Keycodes,bool> key,std::function<void()> func);
				void registerMouseEvent(MouseButtons button,std::function<void()> func);
				const starlight::core::maths::Vec2& getMouseLocation() const;
			};
		}
	}
}
