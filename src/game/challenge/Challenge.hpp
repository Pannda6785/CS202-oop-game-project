#ifndef CHALLENGE_HPP
#define CHALLENGE_HPP

#include "../../Unit.hpp"
#include <memory>

class World;
class Pattern;

class Challenge {
public:
    virtual ~Challenge() = default;
    virtual void apply(World* world) = 0;
protected:
    void applyModifier(World* world, Unit::Modifier mod, float duration, float value);
    void applyLock(World* world, Unit::Lock lock, float duration);
    void addPattern(World* world, std::unique_ptr<Pattern> pattern, float time = 0.0f);
};

#endif // CHALLENGE_HPP