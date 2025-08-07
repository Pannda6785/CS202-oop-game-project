#ifndef CERES_CURRENT_HPP
#define CERES_CURRENT_HPP

#include "Pattern.hpp"

class CeresCurrent : public Pattern {
    static constexpr int OWNER_ID = 2;
    static constexpr float DURATION = 55;

    static constexpr float B1_START_TIME = 2;
    static constexpr float B1_SPEED = 450;
    static constexpr float B1_MIN_RADIUS = 20;
    static constexpr float B1_MAX_RADIUS = 36;
    static constexpr float ANGLE_SPREAD = 8; // degrees
    static constexpr float FREQUENCY = 0.3f;

    static constexpr float B2_START_TIME = 5;
    static constexpr float B2_STARTUP = 1.000f;
    static constexpr float B2_MIN_SPEED = 0;
    static constexpr float B2_MAX_SPEED = 280;
    static constexpr float B2_RADIUS = 480;
    static constexpr float B2_FREQUENCY = 2.5;

public:
    explicit CeresCurrent(IBulletSpawner* spawner);

    void init() override;
    void update(float dt) override;

private:
    float timer;
    int b2Wave = 0;
};

#endif // CERES_CURRENT_HPP
