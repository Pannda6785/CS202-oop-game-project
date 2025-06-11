#ifndef KEYBOARD_INPUT_INTERPRETER_HPP
#define KEYBOARD_INPUT_INTERPRETER_HPP

#include "InputInterpreter.hpp"
#include <array>

class KeyboardInputInterpreter : public InputInterpreter {
public:
    KeyboardInputInterpreter();

    Unit::Vec2D getMovement() const override;
    bool isInputPressed(Unit::Input input) const override;
    bool isInputReleased(Unit::Input input) const override;
    bool isInputDown(Unit::Input input) const override;
    bool isInputUp(Unit::Input input) const override;

    void setKeyMapping(Unit::Input input, int raylibKey);
private:
    std::array<int, Unit::NUM_INPUTS> keyMapping;
};

#endif // KEYBOARD_INPUT_INTERPRETER_HPP
