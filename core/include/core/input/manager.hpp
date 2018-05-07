#pragma once

#include <functional>
#include <map>
#include <queue>

#include <core/gfx/window.hpp>
#include <core/input/enum.hpp>
#include <core/input/keyboard.hpp>
#include <core/input/mouse.hpp>

namespace starlight::core::input {

class STARLIGHTAPI InputManager {
    using Window = starlight::core::gfx::Window;
    // using Keyboard = starlight::core::input::Keyboard;
    // using Keycodes = starlight::core::input::Keycodes;
    // using MouseButtons = starlight::core::input::MouseButtons;
    // using Mouse = starlight::core::input::Mouse;
  private:
    std::map<std::pair<Keycodes, PressedState>, std::function<void()>> keyEvents;
    std::map<std::pair<MouseButtons, PressedState>, std::function<void()>> mouseEvents;
    std::queue<std::function<void()>> inputEvents;
    Keyboard keyboard;
    Mouse mouse;

  public:
    InputManager() = default;
    ~InputManager() = default;
    void registerWindowCallback(Window* window);
    void pollEvents();
    void processEvents();
    void registerKeyboardEvent(std::pair<Keycodes, PressedState> key, std::function<void()> func);
    void registerMouseEvent(std::pair<MouseButtons, PressedState> button, std::function<void()> func);
    SLC_DOUBLE const* getMouseLocation() const;
};

} // namespace starlight::core::input