#include <test/shared.hpp>

#include <core/input/manager.hpp>


namespace starlight::core::input {
using namespace fakeit;

namespace {
using Window = starlight::core::gfx::Window;
using Keycodes = starlight::core::input::Keycodes;
using MouseButtons = starlight::core::input::MouseButtons;
using PressedState = starlight::core::input::PressedState;

PRIVATE_TAG();
TAG_V(InputManager, keyEvents, std::map<std::pair<Keycodes COMMA PressedState> COMMA std::function<void()>>);
TAG_V(InputManager, mouseEvents, std::map<std::pair<MouseButtons COMMA PressedState> COMMA std::function<void()>>);
TAG_V(InputManager, inputEvents, std::queue<std::function<void()>>);
TAG_V(InputManager, keyboard, std::unique_ptr<Keyboard>);
TAG_V(InputManager, mouse, std::unique_ptr<Mouse>);

SCENARIO("input mangers support mouse and keyboard", "[input,inputManager]") {

    GIVEN("An inputmanager im") {
        Core core;
        InputManager im={&core};

        auto& keyEvents = im.*saved_private_v<InputManager_keyEvents>;
        auto& mouseEvents = im.*saved_private_v<InputManager_mouseEvents>;
        auto& inputEvents = im.*saved_private_v<InputManager_inputEvents>;
        auto& keyboard = im.*saved_private_v<InputManager_keyboard>;
        auto& mouse = im.*saved_private_v<InputManager_mouse>;

        WHEN("A k is constructed all fields are initilised") {
            REQUIRE(keyEvents.empty());
            REQUIRE(mouseEvents.empty());
            REQUIRE(inputEvents.empty());
            REQUIRE(nullptr != keyboard);
            REQUIRE(nullptr != mouse);
        }

    }
}

} // namespace
} // namespace starlight::core::input
