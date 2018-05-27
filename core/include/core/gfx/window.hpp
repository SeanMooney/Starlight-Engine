#pragma once
#include <core/core.hpp>
#include <core/gfx/glfw.hpp>
namespace starlight::core::gfx {
class STARLIGHTAPI Window {
  private:
    GLFWwindow* window;
    const Core* core;

  private:
    void init(const int width, const int height, const char* title);
    void destroy() const noexcept;
    friend void window_size_callback(GLFWwindow* window, int width, int height) noexcept;

  public:
    int width, height;
    float ratio;
    Window(const Core* core, const int width = 800, const int height = 600, const char* title = "Starlight-Core");
    ~Window();
    GLFWwindow* get() const noexcept;
};
} // namespace starlight::core::gfx