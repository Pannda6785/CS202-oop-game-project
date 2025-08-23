#ifndef STONE_STATIC_GREEN_HPP
#define STONE_STATIC_GREEN_HPP

#include "Challenge.hpp"
#include "../pattern/StaticGreen.hpp"

class StoneStaticGreen : public Challenge {
public:
    void apply(World* world) override {
        addPattern(world, std::make_unique<StaticGreen>(world, world));
    }
};

#endif // STONE_STATIC_GREEN_HPP