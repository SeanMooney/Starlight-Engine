#include <core/input/manager.hpp>

namespace starlight::core::input {
using Window = starlight::core::gfx::Window;
using Keycodes = starlight::core::input::Keycodes;
using MouseButtons = starlight::core::input::MouseButtons;
using PressedState = starlight::core::input::PressedState;

void InputManager::registerWindowCallback(Window* window) {
    keyboard.registerWindowCallback(window);
    mouse.registerWindowCallback(window);
}

void InputManager::pollEvents() {
    if (keyboard.dirty) {
        for (auto it : keyEvents) {
            if (keyboard.keys[it.first.first]) {
                auto& heldState = keyboard.heldKeys[it.first.first];
                auto& triggerState = it.first.second;
                switch (triggerState) {
                    case PressedState::pressed:
                        if (!heldState) inputEvents.push(it.second);
                        break;
                    case PressedState::held:
                        if (heldState) inputEvents.push(it.second);
                        break;
                    case PressedState::pressedOrHeld:
                        inputEvents.push(it.second);
                        break;
                    default:
                        break;
                }
            }
        }
        keyboard.dirty = false;
    }
    if (mouse.dirty) {
        for (auto it : mouseEvents) {
            auto& triggerState = it.first.second;
            if (mouse.buttons[it.first.first]) {
                auto& heldState = mouse.buttons_helded[it.first.first];
                switch (triggerState) {
                    case PressedState::pressed:
                        if (!heldState) inputEvents.push(it.second);
                        break;
                    case PressedState::held:
                        if (heldState) inputEvents.push(it.second);
                        break;
                    case PressedState::pressedOrHeld:
                        inputEvents.push(it.second);
                        break;
                    default:
                        break;
                }
            } else {
                if (triggerState == PressedState::unpressed) inputEvents.push(it.second);
            }
            mouse.dirty = false;
        }
    }
}

void InputManager::processEvents() {
    while (!inputEvents.empty()) {
        auto func = inputEvents.front();
        inputEvents.pop();
        func();
    }
}

void InputManager::registerKeyboardEvent(std::pair<Keycodes, PressedState> key, std::function<void()> func) {
    keyEvents[key] = func;
}

void InputManager::registerMouseEvent(std::pair<MouseButtons, PressedState> button, std::function<void()> func) {
    mouseEvents[button] = func;
}

SLC_DOUBLE const* InputManager::getMouseLocation() const { return mouse.pos; }

} // namespace starlight::core::input