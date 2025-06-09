#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "InputInterpreter.h"

#include <deque>
#include <vector>
#include <memory>

class InputHandler {
public:
    InputHandler(std::shared_ptr<InputInterpreter> interpreter);

    void update(float dt);
    Unit::Vec2D getMovement() const;
    bool isHoldingKey(Unit::Input input) const;
    bool tryRegister(Unit::Input input, float bufferTime);
    void flush();

private:
    std::shared_ptr<InputInterpreter> interpreter;
    
    const float BUFFER_TIME = 0.4f; // Time in seconds to keep buffer inputs, assumes no move buffers longer that this
    struct BufferedInput {
        Unit::Input input;
        float inputtedTime;
    };
    const std::vector<Unit::Input> toBufferInputs = {
        Unit::Input::Basic,
        Unit::Input::Wide,
        Unit::Input::Offensive,
        Unit::Input::Defensive
    };
    float currentTime;
    std::deque<BufferedInput> bufferQueue;
};

#endif // INPUT_HANDLER_H
