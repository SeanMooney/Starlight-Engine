#pragma once

#include <unordered_map>

#include <core/gfx/window.hpp>
#include <core/input/enum.hpp>

namespace starlight::core::input {

class Mouse {
    #include <core/input/enum.hpp>
    friend class InputManager;
    using Window = starlight::core::gfx::Window;

  private:
    bool dirty = false;
    std::array<SLC_DOUBLE,2> pos;
    std::array<PressedState, MouseButtons::MOUSE_BUTTON_LAST + 1> buttons;
    static std::unordered_map<Window*, Mouse*> mouseMap;

  private:
    friend void button_callback(GLFWwindow* window, SLC_INT32 button, SLC_INT32 action, SLC_INT32 modifer);
    friend void cursor_callback(GLFWwindow* window, SLC_DOUBLE x, SLC_DOUBLE y);

  public:
    Mouse();
    ~Mouse() = default;
    void registerWindowCallback(Window* window);
};
} // namespace starlight::core::input
