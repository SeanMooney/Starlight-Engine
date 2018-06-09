#include <core/gfx/window.hpp>

namespace starlight::core::gfx {

Window::Window(const Core* core, const int width, const int height, const char* title, const int major, const int minor)
    : core(core), width(width), height(height), ratio(width / (float)height) {
    const auto& logger = this->core->logManager->get(core->loggerName);
    logger->info("creating window({}): height={} width={}",title,width,height);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

void Window::init(const int width, const int height, const char* title) {
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