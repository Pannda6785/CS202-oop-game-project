#ifndef PRIESTESS_OFFENSIVE_HANDLER_HPP
#define PRIESTESS_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"
#include "../bullet/RingGraphicsComponent.hpp"

#include <memory>

class PriestessGraphicsComponent;

class PriestessOffensiveHandler : public CastHandler {
    static constexpr float MIN_CASTING_TIME = 0.06f; 
    static constexpr float MAX_CASTING_TIME = 1.60f;
    static constexpr float RING_SPEED = 900; // X units per second
    static constexpr float ADDED_RING_RADIUS = 150.0f;

    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.08f;
    static constexpr float MAX_ACTION_LOCK = 1.000f; // action lock = X - casttime, min Y
    static constexpr float MIN_ACTION_LOCK = 0.300f; // above Y
    static constexpr float SHORT_POST_MOVEMENT_MODIFIER_AMOUNT = 1.3f;
    static constexpr float LONG_POST_MOVEMENT_MODIFIER_AMOUNT = 0.6f;
    static constexpr float POST_MOVEMENT_MODIFIER_DURATION = 0.9f;

    static constexpr float CUTOFF = 0.25f;

    static constexpr float COOLDOWN = 5.0f;
    static constexpr float COOLDOWN_HOLD = 1.2f;

    static constexpr float MAX_NUM_BULLETS_RATIO = 0.0686f; // number bullet pair = this * getRadius
    static constexpr float DECAY_RATE = 0.035f; // decay rate for the number of bullets as radius increases
    static constexpr float STARTUP = 0.4f;
    static constexpr float BULLET_SPEED = 480.0f;
    static constexpr float BULLET_RADIUS = 30.0f;

public:
    PriestessOffensiveHandler(PriestessGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void onCastStart() override;
    void onCastRelease(bool isInterupted) override;

private:
    PriestessGraphicsComponent* graphics;
    std::unique_ptr<RingGraphicsComponent> ring;

    float cooldownHold = 0.0f;

    float getRingRadius() const;
    void spawnBullet();
};

#endif // PRIESTESS_OFFENSIVE_HANDLER_HPP
