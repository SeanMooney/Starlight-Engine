#include <core/gfx/glfw.hpp>

namespace starlight::core::gfx {

void GLFW::error_callback(int error, const char* description) {
    const auto& logger = spdlog::get("system");
    logger->error("GLFW ERROR\nError code: {}\nMessage: {}",error,description);
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