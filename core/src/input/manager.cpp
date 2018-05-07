#include <core/input/manager.hpp>

namespace starlight::core::input {
using Window = starlight::core::gfx::Window;
using Keycodes = starlight::core::input::Keycodes;
using MouseButtons = starlight::core::input::MouseButtons;

void InputManager::registerWindowCallback(Window* window) {
    keyboard.registerWindowCallback(window);
    mouse.registerWindowCallback(window);
}
void InputManager::pollEvents() {
    if (keyboard.dirty) {
        for (auto it : keyEvents) {
            if (keyboard.keys[it.first.first] && keyboard.heldKeys[it.first.first] == it.first.second) {
                inputEvents.push(it.second);
            }
        }
        keyboard.dirty = false;
    }
    if (mouse.dirty) {
        for (auto it : mouseEvents) {
            if (mouse.buttons[it.first.first] && mouse.buttons_helded[it.first.first] == it.first.second)
                inputEvents.push(it.second);
        }
        mouse.dirty = false;
    }
}
void InputManager::processEvents() {
    while (!inputEvents.empty()) {
        auto func = inputEvents.front();
        inputEvents.pop();
        func();
    }
}
void InputManager::registerKeyboardEvent(std::pair<Keycodes, bool> key, std::function<void()> func) {
    keyEvents[key] = func;
}
void InputManager::registerMouseEvent(std::pair<MouseButtons, bool> button, std::function<void()> func) {
    mouseEvents[button] = func;
}
SLC_DOUBLE const* InputManager::getMouseLocation() const { return mouse.pos; }
} // namespace starlight::core::input