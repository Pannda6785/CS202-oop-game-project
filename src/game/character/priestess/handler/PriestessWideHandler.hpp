#ifndef PRIESTESS_WIDE_HANDLER_HPP
#define PRIESTESS_WIDE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"
#include "../extra/RingGraphicsComponent.hpp"

#include <memory>

class PriestessGraphicsComponent;

class PriestessWideHandler : public CastHandler {
    static constexpr float MIN_CASTING_TIME = 0.06f; 
    static constexpr float MAX_CASTING_TIME = 1.60f;
    static constexpr float RING_SPEED = 900; // X units per second
    static constexpr float ADDED_RING_RADIUS = 150.0f;

    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.08f;
    static constexpr float MAX_ACTION_LOCK = 1.060f; // action lock = X - casttime, min Y
    static constexpr float MIN_ACTION_LOCK = 0.300f; // above Y

    static constexpr float CUTOFF = 0.25f;

    static constexpr float MAX_NUM_BULLETS_RATIO = 0.0588f; // number bullet = this * getRadius
    static constexpr float DECAY_RATE = 0.015f; // decay rate for the number of bullets as radius increases
    static constexpr float SHORT_STARTUP = 0.5f;
    static constexpr float LONG_STARTUP = 0.4f;
    static constexpr float BULLET_SPEED = 150.0f;
    static constexpr float BULLET_RADIUS = 55.0f;

public:
    PriestessWideHandler(PriestessGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;

protected:
    void onCastStart() override;
    void onCastRelease(bool isInterupted) override;

private:
    PriestessGraphicsComponent* graphics;
    std::unique_ptr<RingGraphicsComponent> ring;

    float getRingRadius() const;
    void spawnBullet();
};

#endif // PRIESTESS_WIDE_HANDLER_HPP
