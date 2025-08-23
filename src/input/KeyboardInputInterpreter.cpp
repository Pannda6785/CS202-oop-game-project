#include "KeyboardInputInterpreter.hpp"

#include <raylib.h>
#include <cmath>

KeyboardInputInterpreter::KeyboardInputInterpreter(int playerIndex) {
    // TO DO: try read from a .config file here
    if(playerIndex > 1) return;
    if (playerIndex == 0) {
        defaultKeyMapping[static_cast<int>(Unit::Input::Basic)]     = keyMapping[static_cast<int>(Unit::Input::Basic)]     = KEY_Z;
        defaultKeyMapping[static_cast<int>(Unit::Input::Wide)]      = keyMapping[static_cast<int>(Unit::Input::Wide)]      = KEY_X;
        defaultKeyMapping[static_cast<int>(Unit::Input::Offensive)] = keyMapping[static_cast<int>(Unit::Input::Offensive)] = KEY_C;
        defaultKeyMapping[static_cast<int>(Unit::Input::Defensive)] = keyMapping[static_cast<int>(Unit::Input::Defensive)] = KEY_V;
        defaultKeyMapping[static_cast<int>(Unit::Input::Focus)]     = keyMapping[static_cast<int>(Unit::Input::Focus)]     = KEY_LEFT_SHIFT;
        defaultKeyMapping[static_cast<int>(Unit::Input::Toggle)]    = keyMapping[static_cast<int>(Unit::Input::Toggle)]    = KEY_LEFT_CONTROL;
        defaultKeyMapping[static_cast<int>(Unit::Input::Pause)]     = keyMapping[static_cast<int>(Unit::Input::Pause)]     = KEY_ESCAPE;
        defaultKeyMapping[static_cast<int>(Unit::Input::Confirm)]   = keyMapping[static_cast<int>(Unit::Input::Confirm)]   = KEY_ENTER;
        defaultKeyMapping[static_cast<int>(Unit::Input::Back)]      = keyMapping[static_cast<int>(Unit::Input::Back)]      = KEY_BACKSPACE;

        defaultKeyMapping[static_cast<int>(Unit::Input::MoveUp)]    = keyMapping[static_cast<int>(Unit::Input::MoveUp)]    = KEY_UP;
        defaultKeyMapping[static_cast<int>(Unit::Input::MoveDown)]  = keyMapping[static_cast<int>(Unit::Input::MoveDown)]  = KEY_DOWN;
        defaultKeyMapping[static_cast<int>(Unit::Input::MoveLeft)]  = keyMapping[static_cast<int>(Unit::Input::MoveLeft)]  = KEY_LEFT;
        defaultKeyMapping[static_cast<int>(Unit::Input::MoveRight)] = keyMapping[static_cast<int>(Unit::Input::MoveRight)] = KEY_RIGHT;
    } else{
        defaultKeyMapping[static_cast<int>(Unit::Input::Basic)]     = keyMapping[static_cast<int>(Unit::Input::Basic)]     = KEY_J;
        defaultKeyMapping[static_cast<int>(Unit::Input::Wide)]      = keyMapping[static_cast<int>(Unit::Input::Wide)]      = KEY_K;
        defaultKeyMapping[static_cast<int>(Unit::Input::Offensive)] = keyMapping[static_cast<int>(Unit::Input::Offensive)] = KEY_L;
        defaultKeyMapping[static_cast<int>(Unit::Input::Defensive)] = keyMapping[static_cast<int>(Unit::Input::Defensive)] = KEY_SEMICOLON;
        defaultKeyMapping[static_cast<int>(Unit::Input::Focus)]     = keyMapping[static_cast<int>(Unit::Input::Focus)]     = KEY_RIGHT_SHIFT;
        defaultKeyMapping[static_cast<int>(Unit::Input::Toggle)]    = keyMapping[static_cast<int>(Unit::Input::Toggle)]    = KEY_RIGHT_CONTROL;
        defaultKeyMapping[static_cast<int>(Unit::Input::Pause)]     = keyMapping[static_cast<int>(Unit::Input::Pause)]     = KEY_ESCAPE;
        defaultKeyMapping[static_cast<int>(Unit::Input::Confirm)]   = keyMapping[static_cast<int>(Unit::Input::Confirm)]   = KEY_RIGHT_SHIFT;
        defaultKeyMapping[static_cast<int>(Unit::Input::Back)]      = keyMapping[static_cast<int>(Unit::Input::Back)]      = KEY_L;

        defaultKeyMapping[static_cast<int>(Unit::Input::MoveUp)]    = keyMapping[static_cast<int>(Unit::Input::MoveUp)]    = KEY_W;
        defaultKeyMapping[static_cast<int>(Unit::Input::MoveDown)]  = keyMapping[static_cast<int>(Unit::Input::MoveDown)]  = KEY_S;
        defaultKeyMapping[static_cast<int>(Unit::Input::MoveLeft)]  = keyMapping[static_cast<int>(Unit::Input::MoveLeft)]  = KEY_A;
        defaultKeyMapping[static_cast<int>(Unit::Input::MoveRight)] = keyMapping[static_cast<int>(Unit::Input::MoveRight)] = KEY_D;
    }
}

Unit::Vec2D KeyboardInputInterpreter::getMovement() const {
    Unit::Vec2D movement = {0.0f, 0.0f};

    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveUp)]))    movement.y -= 1.0f;
    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveDown)]))  movement.y += 1.0f;
    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveLeft)]))  movement.x -= 1.0f;
    if (IsKeyDown(keyMapping[static_cast<int>(Unit::Input::MoveRight)])) movement.x += 1.0f;

    if (movement.magnitude() > 0.1f) {
        movement = movement.normalized();
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

int KeyboardInputInterpreter::getKeyMapping(Unit::Input input) const {
    return keyMapping[static_cast<int>(input)];
}

void KeyboardInputInterpreter::resetDefaultMapping() {
    keyMapping = defaultKeyMapping;
}