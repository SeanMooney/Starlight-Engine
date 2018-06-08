#pragma once
#include <unordered_map>

#include <core/gfx/window.hpp>
#include <core/input/enum.hpp>

namespace starlight::core::input {

class Keyboard {
    using Window = starlight::core::gfx::Window;
    friend class InputManager;

  private:
    static std::unordered_map<Window*, Keyboard*> keyboardMap;
    std::array<PressedState, Keycodes::KEY_LAST + 1> keys;
    bool dirty = false;

  private:
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  public:
    Keyboard();
    ~Keyboard() = default;
    void registerWindowCallback(Window* window);
};
} // namespace starlight::core::input