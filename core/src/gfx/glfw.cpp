#include <core/gfx/glfw.hpp>

namespace starlight::core::gfx {

void GLFW::error_callback(int error, const char* description) {
    std::cerr << "error code: " << error << std::endl << "message: " << description << std::endl;
}

void GLFW::destroy() const noexcept {
    glfwTerminate();
}

GLFW::GLFW() {
    ret = glfwInit();
    if (!ret) {
        destroy();
        THROW("glfwInit failed");
    }
    glfwSetErrorCallback(error_callback);
}

GLFW::~GLFW() { destroy(); }

}