#ifndef KEYBOARD_INPUT_INTERPRETER_H
#define KEYBOARD_INPUT_INTERPRETER_H

#include "InputInterpreter.h"
#include <array>

class KeyboardInputInterpreter : public InputInterpreter {
public:
    KeyboardInputInterpreter(int playerId);

    Unit::Vec2D getMovement() const override;
    bool isInputPressed(Unit::Input input) const override;
    bool isInputReleased(Unit::Input input) const override;
    bool isInputDown(Unit::Input input) const override;
    bool isInputUp(Unit::Input input) const override;

    void setKeyMapping(Unit::Input input, int raylibKey);
private:
    std::array<int, Unit::NUM_INPUTS> keyMapping;
};

#endif // KEYBOARD_INPUT_INTERPRETER_H
