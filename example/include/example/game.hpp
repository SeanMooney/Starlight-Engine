#pragma once

#include <chrono>
#include <thread>

#include <core/core.hpp>
#include <core/gfx/gfx.hpp>
#include <core/input/manager.hpp>

namespace starlight::example {
using GLFW = starlight::core::gfx::GLFW;
using Window = starlight::core::gfx::Window;
using Input = starlight::core::input::InputManager;
class Game {
  private:
    std::unique_ptr<GLFW> glfw;
    std::unique_ptr<Window> window;
    std::unique_ptr<Input> input;
    // std::unique_ptr<InputManager>inputManager;
  protected:
    void registerKeyboardCallbacks();
    void registerMouseCallbacks();

  public:
    static std::string exeLocation;
    Game(const std::string&);
    ~Game() = default;
    void run() const;
    void init();
};
} // namespace starlight::example