#pragma once
#include <core/core.hpp>
#include <core/gfx/glfw.hpp>
namespace starlight::core::gfx {
    class STARLIGHTAPI Window {
      private:
        GLFWwindow* window;

      private:
        void init(int width, int height, const char* title);
        void destroy() const noexcept;
        friend void window_size_callback(GLFWwindow* window, int width, int height) noexcept;

      public:
        int width, height;
        float ratio;
        Window(int width = 800, int height = 600, const char* title = "Starlight-Core");
        ~Window();
        GLFWwindow* get() const noexcept;
    };
}