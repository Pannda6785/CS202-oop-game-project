#ifndef INPUT_INTERPRETER_H
#define INPUT_INTERPRETER_H

#include "GameUnits.h"

class InputInterpreter {
    int playerId;
public:
    InputInterpreter(int playerId) : playerId(playerId) {};
    virtual ~InputInterpreter() = default;

    virtual void update(float dt) { /* normally empty */ }
    virtual Unit::Vec2D getMovement() const = 0;
    virtual bool isInputPressed(Unit::Input input) const = 0;
    virtual bool isInputReleased(Unit::Input input) const = 0;
    virtual bool isInputDown(Unit::Input input) const = 0;
    virtual bool isInputUp(Unit::Input input) const = 0;
};

#endif // INPUT_INTERPRETER_H