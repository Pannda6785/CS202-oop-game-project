#ifndef HERO_DEFENSIVE_HANDLER_HPP
#define HERO_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class HeroGraphicsComponent;

class HeroDefensiveHandler : public TapHandler {
    static constexpr float INVINCIBILITY_DURATION = 0.500f; // minor
    static constexpr float STUN_DURATION = 1.380;

    // move control
    static constexpr float COOLDOWN = 8.5f;
    static constexpr float MOVEMENT_LOCK = 0.600f;
    static constexpr float ATTACK_LOCK = 0.600f;
    static constexpr float SPELL_LOCK = 0.720f;

    // bullet
    static constexpr float STARTUP = 0.425f;
    static constexpr float RADIUS = 335;
    static constexpr float CLEANSE_RADIUS = RADIUS * 0.96f;
    static constexpr float LIFETIME = 1.800f;

public:
    HeroDefensiveHandler(HeroGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    HeroGraphicsComponent* graphics;
    
    void spawnBullet();
};

#endif // HERO_DEFENSIVE_HANDLER_HPP