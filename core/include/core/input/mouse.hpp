#pragma once

#include <unordered_map>

#include <core/gfx/window.hpp>

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
    friend class InputManager;
    using Window = starlight::core::gfx::Window;

  private:
    static std::unordered_map<Window*, Mouse*> mouseMap;
    SLC_DOUBLE pos[2];
    bool dirty = false;

  private:
    bool buttons[MouseButtons::MOUSE_BUTTON_LAST + 1] = {false};
    bool buttons_helded[MouseButtons::MOUSE_BUTTON_LAST + 1] = {false};
    friend void button_callback(GLFWwindow* window, SLC_INT32 button, SLC_INT32 action, SLC_INT32 modifer);
    friend void cursor_callback(GLFWwindow* window, SLC_DOUBLE x, SLC_DOUBLE y);

  public:
    Mouse() = default;
    ~Mouse() = default;
    void registerWindowCallback(Window* window);
};
} // namespace starlight::core::input
