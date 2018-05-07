#include <core/input/mouse.hpp>
namespace starlight::core::input {

using starlight::core::gfx::Window;
using starlight::core::input::Mouse;

std::unordered_map<Window*, Mouse*> Mouse::mouseMap = {};
Mouse::Mouse(){
for(auto& b : buttons) b=PressedState::unpressed;
}
/*! @brief The function signature for mouse button callbacks.
 *  @param[in] window The window that received the event.
 *  @param[in] button The [mouse button](@ref buttons) that was pressed or
 *  released.
 *  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 */
void button_callback(GLFWwindow* window, SLC_INT32 button, SLC_INT32 action, SLC_INT32 modifer) {
    using PressedState = starlight::core::input::PressedState;
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    auto& pb = Mouse::mouseMap[win]->buttons[button];
    bool& dirty = Mouse::mouseMap[win]->dirty;
    switch (action) {
        case GLFW_REPEAT:
            pb = PressedState::held;
            break;
        case GLFW_PRESS:
            pb = PressedState::pressed;
            break;
        case GLFW_RELEASE:
            pb = PressedState::unpressed;
            break;
    }
    dirty = true;
}

void cursor_callback(GLFWwindow* window, double x, double y) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    Mouse* m = Mouse::mouseMap[win];
    m->pos[0] = static_cast<SLC_DOUBLE>(x);
    m->pos[1] = static_cast<SLC_DOUBLE>(y);
    m->dirty = true;
}

void Mouse::registerWindowCallback(Window* window) {
    mouseMap[window] = this;
    glfwSetMouseButtonCallback(window->get(), button_callback);
    glfwSetCursorPosCallback(window->get(), cursor_callback);
}
} // namespace starlight::core::input
