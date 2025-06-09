#include "InputHandler.h"

InputHandler::InputHandler(std::shared_ptr<InputInterpreter> interpreter) : interpreter(interpreter), currentTime(0.0f) {}

void InputHandler::update(float dt) {
    currentTime += dt;

    // Check and buffer relevant inputs
    for (const auto& input : toBufferInputs) {
        if (interpreter->isInputPressed(input)) {
            bufferQueue.push_back({input, currentTime});
        }
    }

    // Remove expired buffered inputs
    while (!bufferQueue.empty() && (currentTime - bufferQueue.front().inputtedTime > BUFFER_TIME)) {
        bufferQueue.pop_front();
    }
}

Unit::Vec2D InputHandler::getMovement() const {
    return interpreter->getMovement();
}

bool InputHandler::isHoldingKey(Unit::Input input) const {
    return interpreter->isInputDown(input);
}

bool InputHandler::tryRegister(Unit::Input input, float bufferTime) {
    float thresholdTime = currentTime - bufferTime;

    // We'll store the iterator to the earliest matched input found from the back
    std::deque<BufferedInput>::iterator matchIt = bufferQueue.end();

    // Iterate backwards through the bufferQueue
    for (auto it = bufferQueue.rbegin(); it != bufferQueue.rend(); ++it) {
        if (it->inputtedTime < thresholdTime) {
            break; // Since we're going backward, any earlier inputs are older and can be ignored
        }
        if (it->input == input) {
            matchIt = it.base(); // points to the next(matched element) in normal iterator form
        }
    }

    if (matchIt != bufferQueue.end()) {
        // Remove all inputs up to and including the matched input
        bufferQueue.erase(bufferQueue.begin(), matchIt);
        return true;
    }

    return false;
}

void InputHandler::flush() {
    bufferQueue.clear();
}