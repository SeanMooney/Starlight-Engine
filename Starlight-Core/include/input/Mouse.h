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

#include<unordered_map>

#include "STARLIGHT_CORE\graphics\window.h"
#include "STARLIGHT_CORE\Maths\Vec.h"

namespace starlight{
	namespace core{
		namespace input{

			enum MouseButtons{
				MOUSE_BUTTON_1=0,
				MOUSE_BUTTON_2=1,
				MOUSE_BUTTON_3=2,
				MOUSE_BUTTON_4=3,
				MOUSE_BUTTON_5=4,
				MOUSE_BUTTON_6=5,
				MOUSE_BUTTON_7=6,
				MOUSE_BUTTON_8=7,
				MOUSE_BUTTON_LAST=MOUSE_BUTTON_8,
				MOUSE_BUTTON_LEFT=MOUSE_BUTTON_1,
				MOUSE_BUTTON_RIGHT=MOUSE_BUTTON_2,
				MOUSE_BUTTON_MIDDLE=MOUSE_BUTTON_3
			};
			class  Mouse{
				friend class InputManager;
			private:
				static std::unordered_map<starlight::core::graphics::Window*,Mouse*> mouseMap;
				starlight::core::maths::Vec2 pos;
				bool dirty=false;
			private:
				bool buttons[MouseButtons::MOUSE_BUTTON_LAST+1]={ false };
				static friend void button_callback(GLFWwindow*,int,int,int);
				static friend void cursor_callback(GLFWwindow* window,double x,double y);
			public:
				Mouse()=default;
				~Mouse()=default;
				void registerWindowCallback(starlight::core::graphics::Window* window);
			};
		}
	}
}

