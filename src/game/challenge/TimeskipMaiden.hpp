#ifndef TIMSKIP_MAIDEN_HPP
#define TIMSKIP_MAIDEN_HPP

#include "Challenge.hpp"

class TimeskipMaiden : public Challenge {
public:
    void apply(World* world) override {
        applyModifier(world, Unit::Modifier::CooldownModifier, 1e9, 0.2f);
    }
};

#endif // TIMSKIP_MAIDEN_HPP