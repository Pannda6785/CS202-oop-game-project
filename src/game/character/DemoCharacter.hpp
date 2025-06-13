#ifndef DEMO_CHARACTER_HPP
#define DEMO_CHARACTER_HPP

#include "Character.hpp"
#include "../../Unit.hpp"

#include <string>
#include <array>

class DemoCharacter : public Character {
public:
    DemoCharacter(IBulletSpawner* world);  

    void init() override;
    void update(float dt) override;

private:
    std::array<float, Unit::NUM_MOVES> cooldown;
};

#endif // DEMO_CHARACTER_HPP
