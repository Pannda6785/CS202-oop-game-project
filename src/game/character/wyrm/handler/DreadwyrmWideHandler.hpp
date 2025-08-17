#ifndef DREADWYRM_WIDE_HANDLER_HPP
#define DREADWYRM_WIDE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class DreadwyrmWideHandler : public TapHandler {
    // bullet
    static constexpr float STARTUP_FIRST = 0.250f;
    static constexpr float STARTUP_SECOND = 0.800f;
    static constexpr float RADIUS = 13;
    static constexpr float SPEED = 650;
    static constexpr float SPAWN_DISTANCE = 300;
    static constexpr float ANGLE = 40.0f; // degrees
    static constexpr float SPEED_JERK = 0.5f; // after this long after moving, speed halves

    // move control
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.25f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.300f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.05f;
    static constexpr float ARROW_MODIFIER_DURATION = 1.050f;
    static constexpr float BASIC_LOCK = 0.800f;
    static constexpr float WIDE_LOCK = 1.800f;
    static constexpr float SPELL_LOCK = 0.800f;

public:
    DreadwyrmWideHandler(WyrmGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;
    
    void spawnBullet();
};

#endif // DREADWYRM_WIDE_HANDLER_HPP