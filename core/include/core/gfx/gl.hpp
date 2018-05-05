#pragma once
#include <GL/glew.h>
#include <core/core.hpp>

namespace starlight::core::gfx {
class GLEW {
  public:
    GLEW() {
        if (glewInit() != GLEW_OK) {
            THROW("glewInit failed")
        }
    }

    ~GLEW()=default;
};

} // namespace starlight::core::gfx