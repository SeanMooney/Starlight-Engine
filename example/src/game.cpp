#include <chrono>
#include <iostream>

#include <example/game.hpp>

using Window = starlight::core::gfx::Window;
using Keycodes = starlight::core::input::Keycodes;
using MouseButtons = starlight::core::input::MouseButtons;
using Input = starlight::core::input::InputManager;
using PressedState = starlight::core::input::PressedState;

namespace starlight::example {
std::string Game::exeLocation = "";
Game::Game(const std::string& path) {
    Game::exeLocation = path + "\\..\\";
    init();
}

void Game::init() {
    glfw = std::make_unique<GLFW>();
    window = std::make_unique<Window>(1920, 1080, "Starlight Example");
    input = std::make_unique<Input>();
    input->registerWindowCallback(window.get());
    registerKeyboardCallbacks();
    registerMouseCallbacks();
}

// TODO: replase with loging framework.
#define Debug() std::cout
void Game::registerKeyboardCallbacks() {

    auto terminate = [window = window->get()]() { glfwSetWindowShouldClose(window, GL_TRUE); };
    auto trigger = std::make_pair(Keycodes::KEY_ESCAPE, PressedState::pressed);
    input->registerKeyboardEvent(trigger, terminate);
    auto print = [window = window->get()]() {
        static int count = 0;
        Debug() << "this is a test: " << count++ << std::endl;
    };
    trigger = std::make_pair(Keycodes::KEY_SPACE, PressedState::pressed);
    input->registerKeyboardEvent(trigger, print);
    auto printRepeat = [window = window->get()]() {
        static int count = 0;
        Debug() << "this is a repeat test: " << count++ << std::endl;
    };
    trigger = std::make_pair(Keycodes::KEY_SPACE, PressedState::held);
    input->registerKeyboardEvent(trigger, printRepeat);
}

void Game::registerMouseCallbacks() {
    auto printPos = [im = input.get()]() {
        auto pos = im->getMouseLocation();
        Debug() << "POS X: " << pos[0] << " POS Y: " << pos[1] << std::endl;
    };
    auto trigger = std::make_pair(MouseButtons::MOUSE_BUTTON_RIGHT, PressedState::pressedOrHeld);
    input->registerMouseEvent(trigger, printPos);
    auto printPosUnpressed = [im = input.get()]() {
        auto pos = im->getMouseLocation();
        Debug() << "UNPRESSED POS X: " << pos[0] << " POS Y: " << pos[1] << std::endl;
    };
    trigger = std::make_pair(MouseButtons::MOUSE_BUTTON_RIGHT, PressedState::unpressed);
    input->registerMouseEvent(trigger, printPosUnpressed);
}
#undef Debug

void Game::run() const {
    auto windowPTR = window->get();
    /* Make the window's context current */
    glfwMakeContextCurrent(windowPTR);
    using Clock = std::chrono::system_clock;
    using FrameDuration = std::chrono::milliseconds;
    FrameDuration frame(16);
    auto target = Clock::now() + frame;
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
        std::this_thread::sleep_until(target);
        target = Clock::now() + frame;
    }
}
} // namespace starlight::example