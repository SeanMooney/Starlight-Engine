#pragma once

#include <functional>
#include <map>
#include <queue>

#include <core/core.hpp>
#include <core/gfx/window.hpp>
#include <core/input/enum.hpp>
#include <core/input/keyboard.hpp>
#include <core/input/mouse.hpp>

namespace starlight::core::input {

class STARLIGHTAPI InputManager {
    using Window = starlight::core::gfx::Window;

  private:
    std::map<std::pair<Keycodes, PressedState>, std::function<void()>> keyEvents;
    std::map<std::pair<MouseButtons, PressedState>, std::function<void()>> mouseEvents;
    std::queue<std::function<void()>> inputEvents;
    std::unique_ptr<Keyboard> keyboard;
    std::unique_ptr<Mouse> mouse;

  public:
    InputManager();
    InputManager(std::unique_ptr<Keyboard>&& keyboard, std::unique_ptr<Mouse>&& mouse);
    ~InputManager() = default;
    void registerWindowCallback(Window* window);
    void pollEvents();
    void processEvents();
    void registerKeyboardEvent(std::pair<Keycodes, PressedState> key, std::function<void()> func);
    void registerMouseEvent(std::pair<MouseButtons, PressedState> button, std::function<void()> func);
    std::array<SLC_DOUBLE,2> const getMouseLocation() const;
};

} // namespace starlight::core::input