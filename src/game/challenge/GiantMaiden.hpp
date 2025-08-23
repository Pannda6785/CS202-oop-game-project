#ifndef GIANT_MAIDEN_HPP
#define GIANT_MAIDEN_HPP

#include "Challenge.hpp"

class GiantMaiden : public Challenge {
public:
    void apply(World* world) override {
        applyModifier(world, Unit::Modifier::SizeModifier, 1e9, 2.0f);
        applyModifier(world, Unit::Modifier::BulletSizeModifier, 1e9, 1.333f);
    }
};

#endif // GIANT_MAIDEN_HPP