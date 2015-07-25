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
#include "STARLIGHT_CORE\Shared.h"
#include "STARLIGHT_CORE\graphics\GLEW.h"
#include "STARLIGHT_CORE\graphics\GLFW.h"
#include "STARLIGHT_CORE\graphics\Window.h"
#include "STARLIGHT_CORE\graphics\Program.h"
#include "STARLIGHT_CORE\input\InputManager.h"
namespace starlight{
	namespace example{
		using namespace starlight::core::graphics;
		using namespace starlight::core::input;
		class Game{
		private:
			GLFW glfw;
			std::unique_ptr<Window>window;
			std::unique_ptr<InputManager>inputManager;
		public:
			static std::string exeLocation;
			Game(const std::string&);
			~Game();
			void run();
			void init();
		};
	}
}