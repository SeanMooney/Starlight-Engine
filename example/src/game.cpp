#include <chrono>
#include <iostream>

#include <example/game.hpp>

using Window = starlight::core::gfx::Window;
using Keycodes = starlight::core::input::Keycodes;
using MouseButtons = starlight::core::input::MouseButtons;
using Input = starlight::core::input::InputManager;

namespace starlight::example {
std::string Game::exeLocation = "";
Game::Game(const std::string& path) {
    Game::exeLocation = path + "\\..\\";
    init();
}


void Game::init() {
    #define Debug() std::cout
    glfw = std::make_unique<GLFW>();
    window = std::make_unique<Window>(1920, 1080, "Starlight Example");
    input = std::make_unique<Input>();
    input->registerWindowCallback(window.get());
    registerKeyboardCallbacks();
    registerMouseCallbacks();

}

void Game::registerKeyboardCallbacks(){

    auto terminate = [window = window->get()]() { glfwSetWindowShouldClose(window, GL_TRUE); };
    auto trigger = std::make_pair(Keycodes::KEY_ESCAPE, false);
    input->registerKeyboardEvent(trigger, terminate);
    auto print = [window = window->get()]() {
        static int count = 0;
        Debug() << "this is a test: " << count++ << std::endl;
    };
    trigger = std::make_pair(Keycodes::KEY_SPACE, false);
    input->registerKeyboardEvent(trigger, print);
    auto printRepeat = [window = window->get()]() {
        static int count = 0;
        Debug() << "this is a repeat test: " << count++ << std::endl;
    };
    trigger = std::make_pair(Keycodes::KEY_SPACE, true);
    input->registerKeyboardEvent(trigger, printRepeat);

}

void Game::registerMouseCallbacks(){
    auto printPos = [im = input.get()]() {
        auto pos = im->getMouseLocation();
        Debug() << pos << std::endl;
        Debug() << "POS X: " << pos[0] << " POS Y: " << pos[1] << std::endl;
    };
    auto trigger = std::make_pair(MouseButtons::MOUSE_BUTTON_RIGHT, false);
    input->registerMouseEvent(trigger, printPos);
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
        input->pollEvents();
        input->processEvents();
    }
}
}