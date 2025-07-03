#ifndef DEMO_CHARACTER_HPP
#define DEMO_CHARACTER_HPP

#include "../Character.hpp"

class DemoCharacter : public Character {
public:
    DemoCharacter();

    void update(float dt, InputBufferer* input) override;

};

#endif // DEMO_CHARACTER_HPP
