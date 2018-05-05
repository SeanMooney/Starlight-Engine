#include <chrono>
#include <iostream>

#include <example/game.hpp>

namespace starlight::example {
std::string Game::exeLocation = "";
Game::Game(const std::string& path) {
    Game::exeLocation = path + "\\..\\";
    init();
}

void Game::init() {
    glfw = std::make_unique<GLFW>();
    window = std::make_unique<Window>(1920, 1080, "Starlight Example");
}

void Game::run() const{
    auto windowPTR = window->get();
    /* Make the window's context current */
    glfwMakeContextCurrent(windowPTR);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(windowPTR)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(windowPTR);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
}