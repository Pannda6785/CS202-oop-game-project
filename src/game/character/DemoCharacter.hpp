#ifndef DEMO_CHARACTER_HPP
#define DEMO_CHARACTER_HPP

#include "Character.hpp"
#include "../../Unit.hpp"

#include <string>
#include <array>

class DemoCharacter : public Character {
public:
    DemoCharacter();

    void init() override;
    void update(float dt, InputBufferer* input) override;

};

#endif // DEMO_CHARACTER_HPP
