#include <core/input/keyboard.hpp>
namespace starlight::core::input {
using starlight::core::gfx::Window;
std::unordered_map<Window*, Keyboard*> Keyboard::keyboardMap = {};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifer) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    bool& pk = Keyboard::keyboardMap[win]->keys[key];
    bool& hk = Keyboard::keyboardMap[win]->heldKeys[key];
    bool& dirty = Keyboard::keyboardMap[win]->dirty;
    switch (action) {
        case GLFW_REPEAT:
        case GLFW_PRESS:
            if (pk) hk = pk;
            pk = true;
            break;
        case GLFW_RELEASE:
            hk = pk = false;
            break;
    }
    dirty = true;
}

void Keyboard::registerWindowCallback(Window* window) {
    keyboardMap[window] = this;
    glfwSetKeyCallback(window->get(), key_callback);
}

} // namespace starlight::core::input
