#ifndef IRON_MAIDEN_HPP
#define IRON_MAIDEN_HPP

#include "Challenge.hpp"

class IronMaiden : public Challenge {
public:
    void apply(World* world) override {
        applyModifier(world, Unit::Modifier::StaggerModifier, 1e9, 0.1f);
    }
};

#endif // IRON_MAIDEN_HPP