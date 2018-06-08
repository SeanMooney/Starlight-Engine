#include <test/shared.hpp>

#include <core/input/keyboard.hpp>


namespace starlight::core::input {
using namespace fakeit;

namespace {
/* template hack to allow acess to private members see:             *
 * https://gist.github.com/mdadams/98710ba3478f306633df20dca47d5cd9 */

PRIVATE_TAG();
TAG_V(Keyboard, keys, std::array<PressedState COMMA Keycodes::KEY_LAST + 1>);
TAG_V(Keyboard, dirty, bool);
TAG_SV(Keyboard, keyboardMap, std::unordered_map<starlight::core::gfx::Window * COMMA starlight::core::input::Keyboard*>);

SCENARIO("keybaoards can trigger actions when buttons are pressed", "[keyboard]") {

    GIVEN("A keyboard k") {
        Keyboard k;

        auto& keys = k.*saved_private_v<Keyboard_keys>;
        auto& dirty = k.*saved_private_v<Keyboard_dirty>;
        auto& keyboardMap = *saved_private_v<Keyboard_keyboardMap>;

        WHEN("k is constructed all fields are initilised") {
            for (auto& k : keys)
                REQUIRE(k == PressedState::unpressed);
            REQUIRE_FALSE(dirty);
            REQUIRE(keyboardMap.empty());
        }

        WHEN("A window callback is registered") {
            k.registerWindowCallback(nullptr);

            THEN("the keyboardMap should not be empty and k should be the handeler") {
                REQUIRE_FALSE(keyboardMap.empty());
                REQUIRE(keyboardMap[nullptr] == &k);
            }
        }
    }
}

} // namespace
} // namespace starlight::core::input
