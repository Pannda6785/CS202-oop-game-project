#ifndef LICH_WIDE_HANDLER_HPP
#define LICH_WIDE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

#include <vector>
#include <memory>

class LichGraphicsComponent;
class StraightBullet;

class LichWideHandler : public TapHandler {
    static constexpr int NUM_STEPS = 4;
    static constexpr float STARTUP[NUM_STEPS] = {0.6f, 0.7f, 0.8f, 0.9f};
    static constexpr float RING_RADIUS[2 * NUM_STEPS] = {230, 460, 690, 920, 1150, 1380, 1510, 1710};
    static constexpr float BULLET_RADIUS[2 * NUM_STEPS] = {27, 29, 31, 33, 36, 38, 40, 42};
    static constexpr int NUM_BULLETS[2 * NUM_STEPS] = {14, 15, 16, 17, 18, 19, 20, 21};
    static constexpr float LIFETIME = 14;

    static constexpr float MOVEMENT_MODIFIER_VALUE = 0.25f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.480f;
    static constexpr float MOVEMENT_LOCK = 0.100f;
    static constexpr float ATTACK_LOCK = 0.280f;
    static constexpr float COMBO_HOLD = 0.700f;

public:
    LichWideHandler(LichGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void tap(bool isFocusing) override;

private:
    LichGraphicsComponent* graphics;

    int step = 0;
    float comboHold = 0.0f;
    std::vector<std::weak_ptr<StraightBullet>> spawnedBullets;

    void spawnBullet();
};

#endif // LICH_WIDE_HANDLER_HPP