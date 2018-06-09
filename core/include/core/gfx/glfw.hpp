#pragma once
#include <core/core.hpp>
#include <core/gfx/gl.hpp>

#include <GLFW/glfw3.h>

#include <functional>

namespace starlight::core::gfx {
class STARLIGHTAPI GLFW {
  private:
    const Core* core;
    void destroy() const noexcept;
    static void error_callback(int error, const char* description);

  public:
    int ret;
    GLFW(const Core* core);
    ~GLFW();
    std::string getVersionString() const noexcept;
};
} // namespace starlight::core::gfx