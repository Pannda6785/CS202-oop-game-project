#ifndef BOMBLESS_MAIDEN_HPP
#define BOMBLESS_MAIDEN_HPP

#include "Challenge.hpp"

class BomblessMaiden : public Challenge {
public:
    void apply(World* world) override {
        applyLock(world, Unit::Lock::DefensiveLock, 1e9);
    }
};

#endif // BOMBLESS_MAIDEN_HPP