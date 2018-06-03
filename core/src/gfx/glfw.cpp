#include <core/gfx/glfw.hpp>

namespace starlight::core::gfx {

void GLFW::error_callback(int error, const char* description) {
    std::cerr << "error code: " << error << std::endl << "message: " << description << std::endl;
}

void GLFW::destroy() const noexcept {
        glfwTerminate();
}

GLFW::GLFW(const Core* core):core(core) {
    const auto& logger = this->core->logManager->get(core->loggerName);
    logger->info("GLFW initalising");
    ret = glfwInit();
    if (!ret) {
        logger->error("GLFW failed");
        destroy();
        THROW("glfwInit failed");
    }
    glfwSetErrorCallback(error_callback);
    logger->info("GLFW initalised");
}

GLFW::~GLFW() { destroy(); }

}