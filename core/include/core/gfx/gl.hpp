#pragma once
#include <GL/glew.h>
#include <core/core.hpp>

namespace starlight::core::gfx {
class GLEW {
    const Core* core;
    public : GLEW(const Core* core):core(core) {
          const auto& logger = this->core->logManager->get(core->loggerName);
          logger->debug("initalising GLEW");
          glewExperimental = GL_TRUE;
          if (glewInit() != GLEW_OK) {
              logger->debug("initalising GLEW failed");
              THROW("glewInit failed")
        }
    }

    ~GLEW()=default;
};

} // namespace starlight::core::gfx