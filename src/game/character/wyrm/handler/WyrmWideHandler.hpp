#ifndef WYRM_WIDE_HANDLER_HPP
#define WYRM_WIDE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class WyrmWideHandler : public TapHandler {
    // bullet
    static constexpr float STARTUP = 0.240f;
    static constexpr float RADIUS = 32;
    static constexpr float SPEED_IN = 1050;
    static constexpr float SPEED_OUT = 1230;
    static constexpr float SPAWN_RADIUS = 25; // where to spawn
    static constexpr int NUM_BULLETS = 10;

    // move control
    static constexpr float MOVEMENT_LOCK_DURATION = 0.160f;
    static constexpr float ARROW_LOCK = 0.160f;
    static constexpr float ATTACK_LOCK = 0.525f;
    static constexpr float SPELL_LOCK = 0.280f;

public:
    WyrmWideHandler(WyrmGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;
    
    void spawnBullet();

};

#endif // WYRM_BASIC_HANDLER_HPP
