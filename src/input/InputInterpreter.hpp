#ifndef INPUT_INTERPRETER_HPP
#define INPUT_INTERPRETER_HPP

#include "../Unit.hpp"

class InputInterpreter {
public:
    virtual ~InputInterpreter() = default;

    virtual void update(float dt) { /* normally empty because GUI lib handles it */ }
    virtual Unit::Vec2D getMovement() const = 0;
    virtual bool isInputPressed(Unit::Input input) const = 0;
    virtual bool isInputReleased(Unit::Input input) const = 0;
    virtual bool isInputDown(Unit::Input input) const = 0;
    virtual bool isInputUp(Unit::Input input) const = 0;
};

#endif // INPUT_INTERPRETER_HPP