#include "InputBufferer.hpp"

InputBufferer::InputBufferer(std::shared_ptr<InputInterpreter> interpreter) : interpreter(interpreter), currentTime(0.0f) {}

void InputBufferer::update(float dt) {
    currentTime += dt;

    // Check and buffer relevant inputs
    for (const auto& input : toBufferInputs) {
        if (interpreter && interpreter->isInputPressed(input)) {
            bufferQueue.push_back({input, currentTime});
        }
    }

    // Remove expired buffered inputs
    while (!bufferQueue.empty() && (currentTime - bufferQueue.front().inputtedTime > BUFFER_TIME)) {
        bufferQueue.pop_front();
    }
}

Unit::Vec2D InputBufferer::getMovement() const {
    if(!interpreter) return Unit::Vec2D{0.0f, 0.0f};
    return interpreter->getMovement();
}

bool InputBufferer::isHoldingKey(Unit::Input input) const {
    return interpreter && interpreter->isInputDown(input);
}

bool InputBufferer::tryRegister(Unit::Input input, float bufferTime) {
    float thresholdTime = currentTime - bufferTime;

    std::deque<BufferedInput>::iterator matchIt = bufferQueue.begin();

    for (auto it = bufferQueue.rbegin(); it != bufferQueue.rend(); ++it) {
        if (it->inputtedTime < thresholdTime) {
            break;
        }
        if (it->input == input) {
            matchIt = it.base(); // points to the next(matched element) in normal iterator form
        }
    }

    if (matchIt != bufferQueue.begin()) {
        bufferQueue.erase(bufferQueue.begin(), matchIt);
        return true;
    }

    return false;
}

void InputBufferer::flush() {
    bufferQueue.clear();
}