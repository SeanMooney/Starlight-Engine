#include <core/input/keyboard.hpp>
namespace starlight::core::input {
using starlight::core::gfx::Window;
std::unordered_map<Window*, Keyboard*> Keyboard::keyboardMap = {};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifer) {
    SUPPRESS_UNUSED(scancode); // ignore scancode for now
    SUPPRESS_UNUSED(modifer); // ignore modifers for now

    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    auto& pk = Keyboard::keyboardMap[win]->keys[key];
    bool& dirty = Keyboard::keyboardMap[win]->dirty;
    switch (action) {
        case GLFW_REPEAT:
            pk = PressedState::held;
            break;
        case GLFW_PRESS:
            pk = PressedState::pressed;
            break;
        case GLFW_RELEASE:
            pk = PressedState::unpressed;
            break;
    }
    dirty = true;
}

Keyboard::Keyboard() {
    for (auto& k : keys)
        k = PressedState::unpressed;
}

void Keyboard::registerWindowCallback(Window* window) {
    keyboardMap[window] = this;
    if (window != nullptr) glfwSetKeyCallback(window->get(), key_callback);
}

} // namespace starlight::core::input
