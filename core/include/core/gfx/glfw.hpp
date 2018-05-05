#pragma once
#include <GLFW/glfw3.h>
#include <core/core.hpp>

namespace starlight::core::gfx {
class STARLIGHTAPI GLFW {
  private:
    void destroy() const noexcept;
    static void error_callback(int error, const char* description);

  public:
    int ret;
    GLFW();
    ~GLFW();
};
}