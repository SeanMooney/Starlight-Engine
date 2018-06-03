#include <core/input/manager.hpp>

namespace starlight::core::input {
using Window = starlight::core::gfx::Window;
using Keycodes = starlight::core::input::Keycodes;
using MouseButtons = starlight::core::input::MouseButtons;
using PressedState = starlight::core::input::PressedState;

InputManager::InputManager(const Core* core) : InputManager(core, std::make_unique<Keyboard>(), std::make_unique<Mouse>()) {}
InputManager::InputManager(const Core* core, std::unique_ptr<Keyboard>&& kb, std::unique_ptr<Mouse>&& m) : core(core) {
    keyboard = std::move<>(kb);
    mouse = std::move<>(m);
    keyEvents = {};
    mouseEvents = {};
    inputEvents = {};
    const auto& logger = this->core->logManager->get(core->loggerName);
    logger->info("creating input manager");
}

void InputManager::registerWindowCallback(Window* window) {
    keyboard->registerWindowCallback(window);
    mouse->registerWindowCallback(window);
}

void InputManager::pollEvents() {
    if (keyboard) {
        if (keyboard->dirty) {
            for (auto it : keyEvents) {
                auto& triggerState = it.first.second;
                auto& currentState = keyboard->keys[it.first.first];
                if (triggerState == currentState
                    || (triggerState == PressedState::pressedOrHeld
                        && (currentState == PressedState::pressed || currentState == PressedState::held))) {
                    inputEvents.push(it.second);
                }
            }
        }
        keyboard->dirty = false;
    }
    if (mouse) {
        if (mouse->dirty) {
            for (auto it : mouseEvents) {
                auto& triggerState = it.first.second;
                auto& currentState = mouse->buttons[it.first.first];
                if (triggerState == currentState
                    || (triggerState == PressedState::pressedOrHeld
                        && (currentState == PressedState::pressed || currentState == PressedState::held))) {
                    inputEvents.push(it.second);
                }
            }
            mouse->dirty = false;
        }
    }
}

void InputManager::processEvents() {
    while (!inputEvents.empty()) {
        auto& func = inputEvents.front();
        func();
        inputEvents.pop();
    }
}

void InputManager::registerKeyboardEvent(std::pair<Keycodes, PressedState> key, std::function<void()> func) {
    keyEvents[key] = func;
}

void InputManager::registerMouseEvent(std::pair<MouseButtons, PressedState> button, std::function<void()> func) {
    mouseEvents[button] = func;
}

std::array<SLC_DOUBLE, 2> const InputManager::getMouseLocation() const { return mouse->pos; }

} // namespace starlight::core::input