#ifndef CONTROLLER_INPUT_INTERPRETER_HPP
#define CONTROLLER_INPUT_INTERPRETER_HPP

#include "InputInterpreter.hpp"
#include <array>

class ControllerInputInterpreter : public InputInterpreter {
public:
    explicit ControllerInputInterpreter(int gamepadId = 0);

    Unit::Vec2D getMovement() const override;
    bool isInputPressed(Unit::Input input) const override;
    bool isInputReleased(Unit::Input input) const override;
    bool isInputDown(Unit::Input input) const override;
    bool isInputUp(Unit::Input input) const override;

    void setButtonMapping(Unit::Input input, int raylibButton);

private:
    int gamepadId;
    std::array<int, Unit::NUM_INPUTS> buttonMapping;

    // stick movement
    int axisHorizontal;
    int axisVertical;
    float deadzone;
    float digitalThreshold;
};

#endif // CONTROLLER_INPUT_INTERPRETER_HPP
