#include <core/gfx/window.hpp>

namespace starlight::core::gfx {

Window::Window(int width, int height, const char* title) : width(width), height(height), ratio(width / (float)height) {
    init(width, height, title);
}
Window::~Window() { destroy(); }

void window_size_callback(GLFWwindow* window, int width, int height) noexcept {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->width = width;
    win->height = height;
    win->ratio = width / (float)height;
    glViewport(0, 0, width, height);
    // starlight::core::utils::Debug() << "window size changed." << std::endl
    //                                 << "width: " << win->width << ", height:" << win->height << std::endl;
}

void Window::init(int width, int height, const char* title) {
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) THROW("window creation failed");
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSwapInterval(0);
}

void Window::destroy() const noexcept { glfwDestroyWindow(window); }

GLFWwindow* Window::get() const noexcept { return window; }

} // namespace starlight::core::gfx