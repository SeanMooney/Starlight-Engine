#pragma once
#include <core/gfx/gfx.hpp>

namespace starlight::example{
using GLFW = starlight::core::gfx::GLFW;
using Window = starlight::core::gfx::Window;
class Game{
		private:
			std::unique_ptr<GLFW> glfw;
            std::unique_ptr<Window> window;
            // std::unique_ptr<InputManager>inputManager;
		public:
			static std::string exeLocation;
			Game(const std::string&);
			~Game()=default;
			void run() const;
			void init();
};
}