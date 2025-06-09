#ifndef DEMO_CHARACTER_H
#define DEMO_CHARACTER_H

#include "Character.h"

class DemoCharacter : public Character {
public:
    DemoCharacter() 
        : moveSpeed(600.0f), focusedSpeed(120.0f) {
        name = "DemoCharacter";
    }

    void update(float dt, const InputHandler& input) override {

    }

    std::string getName() const override {
        return name;
    }

    float getMoveSpeed() const override {
        return moveSpeed;
    }

    float getFocusedSpeed() const override {
        return focusedSpeed;
    }

private:
    float moveSpeed;
    float focusedSpeed;
};

#endif // DEMO_CHARACTER_H
