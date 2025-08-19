#include "ControllerInputInterpreter.hpp"
#include <raylib.h>
#include <cmath>

ControllerInputInterpreter::ControllerInputInterpreter(int gamepadId)
    : gamepadId(gamepadId),
      axisHorizontal(GAMEPAD_AXIS_LEFT_X),
      axisVertical(GAMEPAD_AXIS_LEFT_Y),
      deadzone(0.25f),
      digitalThreshold(0.8f) {

    // Gameplay buttons
    buttonMapping[static_cast<int>(Unit::Input::Basic)]     = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;   // A
    buttonMapping[static_cast<int>(Unit::Input::Wide)]      = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;  // B
    buttonMapping[static_cast<int>(Unit::Input::Offensive)] = GAMEPAD_BUTTON_RIGHT_FACE_LEFT;   // X
    buttonMapping[static_cast<int>(Unit::Input::Defensive)] = GAMEPAD_BUTTON_RIGHT_FACE_UP;     // Y
    buttonMapping[static_cast<int>(Unit::Input::Focus)]     = GAMEPAD_BUTTON_LEFT_TRIGGER_1;    // LB
    buttonMapping[static_cast<int>(Unit::Input::Toggle)]    = GAMEPAD_BUTTON_RIGHT_TRIGGER_1;   // RB

    // Menu buttons
    buttonMapping[static_cast<int>(Unit::Input::Confirm)]   = buttonMapping[static_cast<int>(Unit::Input::Basic)];
    buttonMapping[static_cast<int>(Unit::Input::Back)]      = buttonMapping[static_cast<int>(Unit::Input::Wide)];
    buttonMapping[static_cast<int>(Unit::Input::Pause)]     = GAMEPAD_BUTTON_MIDDLE_LEFT;       // BACK

    // D-pad fallback for digital movement
    buttonMapping[static_cast<int>(Unit::Input::MoveUp)]    = GAMEPAD_BUTTON_LEFT_FACE_UP;
    buttonMapping[static_cast<int>(Unit::Input::MoveDown)]  = GAMEPAD_BUTTON_LEFT_FACE_DOWN;
    buttonMapping[static_cast<int>(Unit::Input::MoveLeft)]  = GAMEPAD_BUTTON_LEFT_FACE_LEFT;
    buttonMapping[static_cast<int>(Unit::Input::MoveRight)] = GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
}

Unit::Vec2D ControllerInputInterpreter::getMovement() const {
    Unit::Vec2D movement = {0.0f, 0.0f};
    if (!IsGamepadAvailable(gamepadId)) return movement;

    float x = GetGamepadAxisMovement(gamepadId, axisHorizontal);
    float y = GetGamepadAxisMovement(gamepadId, axisVertical);

    if (std::fabs(x) > deadzone) movement.x = x;
    if (std::fabs(y) > deadzone) movement.y = y;

    if (movement.magnitude() > 0.1f) {
        movement = movement.normalized();
    } else {
        movement = {0.0f, 0.0f};
    }

    return movement;
}

bool ControllerInputInterpreter::isInputPressed(Unit::Input input) const {
    if (input == Unit::Input::MoveUp || input == Unit::Input::MoveDown ||
        input == Unit::Input::MoveLeft || input == Unit::Input::MoveRight) {
        // No pressed/released detection from analog stick → fall back to D-pad
        return IsGamepadButtonPressed(gamepadId, buttonMapping[static_cast<int>(input)]);
    }
    return IsGamepadButtonPressed(gamepadId, buttonMapping[static_cast<int>(input)]);
}

bool ControllerInputInterpreter::isInputReleased(Unit::Input input) const {
    if (input == Unit::Input::MoveUp || input == Unit::Input::MoveDown ||
        input == Unit::Input::MoveLeft || input == Unit::Input::MoveRight) {
        return IsGamepadButtonReleased(gamepadId, buttonMapping[static_cast<int>(input)]);
    }
    return IsGamepadButtonReleased(gamepadId, buttonMapping[static_cast<int>(input)]);
}

bool ControllerInputInterpreter::isInputDown(Unit::Input input) const {
    if (!IsGamepadAvailable(gamepadId)) return false;

    if (input == Unit::Input::MoveUp)    return GetGamepadAxisMovement(gamepadId, axisVertical) < -digitalThreshold ||
                                               IsGamepadButtonDown(gamepadId, buttonMapping[static_cast<int>(input)]);
    if (input == Unit::Input::MoveDown)  return GetGamepadAxisMovement(gamepadId, axisVertical) >  digitalThreshold ||
                                               IsGamepadButtonDown(gamepadId, buttonMapping[static_cast<int>(input)]);
    if (input == Unit::Input::MoveLeft)  return GetGamepadAxisMovement(gamepadId, axisHorizontal) < -digitalThreshold ||
                                               IsGamepadButtonDown(gamepadId, buttonMapping[static_cast<int>(input)]);
    if (input == Unit::Input::MoveRight) return GetGamepadAxisMovement(gamepadId, axisHorizontal) >  digitalThreshold ||
                                               IsGamepadButtonDown(gamepadId, buttonMapping[static_cast<int>(input)]);

    return IsGamepadButtonDown(gamepadId, buttonMapping[static_cast<int>(input)]);
}

bool ControllerInputInterpreter::isInputUp(Unit::Input input) const {
    return !isInputDown(input);
}

void ControllerInputInterpreter::setButtonMapping(Unit::Input input, int raylibButton) {
    buttonMapping[static_cast<int>(input)] = raylibButton;
}
