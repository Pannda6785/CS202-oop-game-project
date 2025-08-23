#ifndef HEART_PULSATION_HPP
#define HEART_PULSATION_HPP

#include "Pattern.hpp"
#include <vector>
#include <memory>

class IBulletSpawner;

class HeartPulsation : public Pattern {
    static constexpr int OWNER_ID = 2;
    static constexpr float FREQUENCY = 6.0f;
    static constexpr int NUM_BULLETS = 16;
    static constexpr float STARTUP = 0.980f;
    static constexpr float BULLET_RADIUS = 30.0f;

    static constexpr float BULLET_DORMANT_SPEED = BULLET_RADIUS;
    static constexpr float BULLET_SPEED_INIT = 400.0f;
    static constexpr float BULLET_SPEED_FINAL = 80.0f;
    static constexpr float TIME_TO_REACH_FINAL = 2.5f;

public:
    explicit HeartPulsation(IBulletSpawner* spawner);
    void init() override;
    void update(float dt) override;
private:
    float timer;
};

#endif // HEART_PULSATION_HPP
