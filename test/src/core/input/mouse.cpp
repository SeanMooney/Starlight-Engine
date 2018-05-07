#include <test/shared.hpp>

#include <core/input/mouse.hpp>


namespace starlight::core::input {
using namespace fakeit;

namespace {
/* template hack to allow acess to private members see:             *
 * https://gist.github.com/mdadams/98710ba3478f306633df20dca47d5cd9 */

PRIVATE_TAG();
TAG_V(Mouse, buttons, std::array<PressedState COMMA MouseButtons::MOUSE_BUTTON_LAST + 1>);
TAG_V(Mouse, dirty, bool);
TAG_V(Mouse, pos, std::array<SLC_DOUBLE COMMA 2>);
TAG_SV(Mouse, mouseMap, std::unordered_map<starlight::core::gfx::Window * COMMA starlight::core::input::Mouse*>);

SCENARIO("mice can trigger actions when buttons are pressed", "[mouse]") {

    GIVEN("A mouse") {
        Mouse m;

        auto& buttons = m.*saved_private_v<Mouse_buttons>;
        auto& dirty = m.*saved_private_v<Mouse_dirty>;
        auto& pos = m.*saved_private_v<Mouse_pos>;
        auto& mouseMap = *saved_private_v<Mouse_mouseMap>;

        WHEN("Mouse is constructed all fields are initilised") {
            for (auto& b : buttons)
                REQUIRE(b == PressedState::unpressed);
            REQUIRE_FALSE(dirty);
            for (auto& x : pos)
                REQUIRE(x == 0.0);
            REQUIRE(mouseMap.empty());
        }

        WHEN("A window callback is registered") {
            m.registerWindowCallback(nullptr);

            THEN("the mouseMap should not be empty and mouse should be the handeler") {
                REQUIRE_FALSE(mouseMap.empty());
                REQUIRE(mouseMap[nullptr] == &m);
            }
        }
    }
}

} // namespace
} // namespace starlight::core::input
