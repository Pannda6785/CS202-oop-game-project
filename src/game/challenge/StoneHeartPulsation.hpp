#ifndef STONE_HEART_PULSATION_HPP
#define STONE_HEART_PULSATION_HPP

#include "Challenge.hpp"
#include "../pattern/HeartPulsation.hpp"

class StoneHeartPulsation : public Challenge {
public:
    void apply(World* world) override {
        addPattern(world, std::make_unique<HeartPulsation>(world));
    }
};

#endif // STONE_HEART_PULSATION_HPP