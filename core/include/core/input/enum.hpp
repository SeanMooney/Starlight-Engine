#pragma once
namespace starlight::core::input {
enum PressedState{
    pressed,
    held,
    pressedOrHeld,
    unpressed,
    end
};
}