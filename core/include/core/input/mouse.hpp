#pragma once

#include <unordered_map>

#include <core/gfx/window.hpp>
#include <core/input/enum.hpp>

namespace starlight::core::input {
enum MouseButtons {
    MOUSE_BUTTON_1 = 0,
    MOUSE_BUTTON_2 = 1,
    MOUSE_BUTTON_3 = 2,
    MOUSE_BUTTON_4 = 3,
    MOUSE_BUTTON_5 = 4,
    MOUSE_BUTTON_6 = 5,
    MOUSE_BUTTON_7 = 6,
    MOUSE_BUTTON_8 = 7,
    MOUSE_BUTTON_NONE = 8,
    MOUSE_BUTTON_LAST = MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
    MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
    MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
};
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
