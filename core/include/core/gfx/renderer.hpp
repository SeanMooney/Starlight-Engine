#pragma once

#include <core/core.hpp>
#include <core/gfx/gfx.hpp>

namespace starlight::core::gfx {

class STARLIGHTAPI Renderer {
    using Window = starlight::core::gfx::Window;
    using VertexData = std::array<SLC_FLOAT, 9>;

    const Core* core;
    const Window* window;
    VertexData current;
    VertexData pending;
    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint shader_programme =0;
    const char* vertex_shader = "#version 400\n"
                                                        "in vec3 vp;"
                                                        "void main() {"
                                                        "  gl_Position = vec4(vp, 1.0);"
                                                        "}";

    const char* fragment_shader = "#version 400\n"
                                  "out vec4 frag_colour;"
                                  "void main() {"
                                  "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
                                  "}";

  public:
    Renderer(const Core* core, const Window* window) : core(core), window(window) {
        SUPPRESS_UNUSED(this->core);
        SUPPRESS_UNUSED(this->window);
        current = pending = {};
        
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, NULL);
        glCompileShader(vs);
       
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, NULL);
        glCompileShader(fs);
       
        shader_programme = glCreateProgram();
        glAttachShader(shader_programme, fs);
        glAttachShader(shader_programme, vs);
        glLinkProgram(shader_programme);
        glUseProgram(shader_programme);
    }
    void submit() {
        // const auto& logger = this->core->logManager->get(core->loggerName);
        // logger->debug("submiting renderables");
        pending = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
    }
    void flush() {
        // const auto& logger = this->core->logManager->get(core->loggerName);
        // logger->debug("flushing renderables");
        std::swap(pending, current);
        
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, current.size() * sizeof(float), current.cbegin(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    void present() {
        // const auto& logger = this->core->logManager->get(core->loggerName);
        // logger->debug("presenting renderables");
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window->get());
    }
};

} // namespace starlight::core::gfx