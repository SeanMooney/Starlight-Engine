#include <chrono>
#include <ctime>
#include <iostream>

#include <example/game.hpp>

using Window = starlight::core::gfx::Window;
using Renderer = starlight::core::gfx::Renderer;
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
    core = std::make_unique<Core>();
    const auto& logger = this->core->logManager->get(core->loggerName);
    glfw = std::make_unique<GLFW>(core.get());
    logger->debug("GLFW Version: {}",glfw->getVersionString());
    window = std::make_unique<Window>(core.get(), 1920, 1080, "Starlight Example");
    glew = std::make_unique<GLEW>(core.get());
    logger->debug("OPENGL Version: {}",glGetString(GL_VERSION));
    logger->debug("OPENGL Renderer: {}", glGetString(GL_RENDERER));
    input = std::make_unique<Input>(core.get());
    input->registerWindowCallback(window.get());
    registerKeyboardCallbacks();
    registerMouseCallbacks();
    // move to renderer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"
}

// TODO: replase with loging framework.

// using Debug = starlight::core::utils::Debug;
void Game::registerKeyboardCallbacks() {
    const auto& logger = core->logManager->get();
    logger->debug("registering keyboard callbaks");
    auto terminate = [window = window->get()]() { glfwSetWindowShouldClose(window, GL_TRUE); };
    auto trigger = std::make_pair(Keycodes::KEY_ESCAPE, PressedState::pressed);
    input->registerKeyboardEvent(trigger, terminate);
    auto print = [logger = logger]() {
        static int count = 0;
        logger->debug("this is a test: {}", count++);
    };
    trigger = std::make_pair(Keycodes::KEY_SPACE, PressedState::pressed);
    input->registerKeyboardEvent(trigger, print);
    auto printRepeat = [logger = logger]() {
        static int count = 0;
        logger->debug("this is a repeat test: {}", count++);
    };
    trigger = std::make_pair(Keycodes::KEY_SPACE, PressedState::held);
    input->registerKeyboardEvent(trigger, printRepeat);
    auto limit = [& frameLimit=frameLimit]() {
        frameLimit= !frameLimit;
    };
    trigger = std::make_pair(Keycodes::KEY_F10, PressedState::pressed);
    input->registerKeyboardEvent(trigger, limit);
}

void Game::registerMouseCallbacks() {
    const auto& logger = core->logManager->get();
    logger->debug("registering mouse callbaks");
    auto printPos = [im = input.get(), logger = logger]() {
        auto pos = im->getMouseLocation();
        logger->debug("PRESSED(X:{},Y:{})", pos[0], pos[1]);
    };
    auto trigger = std::make_pair(MouseButtons::MOUSE_BUTTON_RIGHT, PressedState::pressedOrHeld);
    input->registerMouseEvent(trigger, printPos);
    auto printPosUnpressed = [im = input.get(), logger = logger]() {
        auto pos = im->getMouseLocation();
        logger->debug("UNPRESSED(X:{},Y:{})", pos[0], pos[1]);
    };
    trigger = std::make_pair(MouseButtons::MOUSE_BUTTON_RIGHT, PressedState::unpressed);
    input->registerMouseEvent(trigger, printPosUnpressed);
}

void Game::run() const {
    const auto& logger = core->logManager->get();
    auto windowPTR = window->get();
    /* Make the window's context current */
    glfwMakeContextCurrent(windowPTR);
    using Clock = std::chrono::system_clock;
    using FrameDuration = std::chrono::milliseconds;
    FrameDuration frame{1000 / 60};
    auto target = Clock::now() + frame;
    auto infoTarget = Clock::now() + (frame * 60);
    logger->debug("starting run loop");

#if STARLIGHT_DEBUG
    int oldFrameNumber = 0;
    int currentFrameNumber = 0;
#endif
    /* Loop until the user closes the window */
    Renderer renderer{core.get(),window.get()};
    while (!glfwWindowShouldClose(windowPTR)) {
        /* Render here */

        renderer.submit();
        renderer.flush();
        renderer.present();

        /* Poll for and process events */
        glfwPollEvents();
        input->pollEvents();
        input->processEvents();
        if (frameLimit) std::this_thread::sleep_until(target);

#if STARLIGHT_DEBUG
        if (target > infoTarget) {
            infoTarget = Clock::now() + (frame * 60);
            auto tmp = currentFrameNumber - oldFrameNumber;
            if(currentFrameNumber>100000) currentFrameNumber=0;
            oldFrameNumber = currentFrameNumber;
            logger->debug("FPS:{} FrameNumber {}", tmp, currentFrameNumber);
        }
        ++currentFrameNumber;
#endif
        target = Clock::now() + frame;
    }
}
} // namespace starlight::example