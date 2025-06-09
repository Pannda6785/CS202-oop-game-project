#include "KeyboardInputInterpreter.h"

#include <raylib.h>
#include <cmath>

KeyboardInputInterpreter::KeyboardInputInterpreter(int playerId) : InputInterpreter(playerId) {
    // TO DO: try read from a .config file here

    keyMapping[static_cast<int>(Unit::Input::Basic)]     = KEY_Z;
    keyMapping[static_cast<int>(Unit::Input::Wide)]      = KEY_X;
    keyMapping[static_cast<int>(Unit::Input::Offensive)] = KEY_C;
    keyMapping[static_cast<int>(Unit::Input::Defensive)] = KEY_V;
    keyMapping[static_cast<int>(Unit::Input::Focus)]     = KEY_LEFT_SHIFT;
    keyMapping[static_cast<int>(Unit::Input::Toggle)]    = KEY_LEFT_CONTROL;
    keyMapping[static_cast<int>(Unit::Input::Pause)]     = KEY_ESCAPE;

    keyMapping[static_cast<int>(Unit::Input::MoveUp)]    = KEY_UP;
    keyMapping[static_cast<int>(Unit::Input::MoveDown)]  = KEY_DOWN;
    keyMapping[static_cast<int>(Unit::Input::MoveLeft)]  = KEY_LEFT;
    keyMapping[static_cast<int>(Unit::Input::MoveRight)] = KEY_RIGHT;
}

Unit::Vec2D KeyboardInputInterpreter::getMovement() const {
    Unit::Vec2D movement = {0.0f, 0.0f};

    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveUp)]))    movement.y -= 1.0f;
    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveDown)]))  movement.y += 1.0f;
    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveLeft)]))  movement.x -= 1.0f;
    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveRight)])) movement.x += 1.0f;

    if (movement.magnitude() > 0.1f) {
        movement = movement.normalized(); // Normalize the movement vector
    }

    return movement;
}

bool KeyboardInputInterpreter::isInputPressed(Unit::Input input) const {
    return IsKeyPressed(keyMapping[static_cast<int>(input)]);
}

bool KeyboardInputInterpreter::isInputReleased(Unit::Input input) const {
    return IsKeyReleased(keyMapping[static_cast<int>(input)]);
}

bool KeyboardInputInterpreter::isInputDown(Unit::Input input) const {
    return IsKeyDown(keyMapping[static_cast<int>(input)]);
}

bool KeyboardInputInterpreter::isInputUp(Unit::Input input) const {
    return IsKeyUp(keyMapping[static_cast<int>(input)]);
}

void KeyboardInputInterpreter::setKeyMapping(Unit::Input input, int raylibKey) {
    // TO DO: write to a .config file here
    keyMapping[static_cast<int>(input)] = raylibKey;
}
