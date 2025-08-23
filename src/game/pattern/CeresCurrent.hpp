#ifndef CERES_CURRENT_HPP
#define CERES_CURRENT_HPP

#include "Pattern.hpp"

/*
    PLAYPEN: Restrict the arena to only the middle zone
    B1: asterite, random from two sides
    B2: moons, big, downward, alternate left right
*/

class CeresCurrent : public Pattern {
    static constexpr int OWNER_ID = 3;
    static constexpr float DURATION = 30;

    static constexpr float PLAYPEN_WIDTH = 1400;
    static constexpr float PLAYPEN_STARTUP = 7.0f;

    static constexpr float B1_START_TIME = 4;
    static constexpr float B1_SPEED = 450;
    static constexpr float B1_MIN_RADIUS = 20;
    static constexpr float B1_MAX_RADIUS = 36;
    static constexpr float ANGLE_SPREAD = 8; // degrees
    static constexpr float FREQUENCY = 0.3f;

    static constexpr float B2_START_TIME = 7;
    static constexpr float B2_STARTUP = 1.000f;
    static constexpr float B2_MIN_SPEED = 0;
    static constexpr float B2_MAX_SPEED = 270;
    static constexpr float B2_RADIUS = 480;
    static constexpr float B2_FREQUENCY = 3.85f;

public:
    explicit CeresCurrent(IBulletSpawner* spawner);

    void init() override;
    void update(float dt) override;

private:
    float timer;
    int b2Wave = 0;
    bool playpenSet = false;
};

#endif // CERES_CURRENT_HPP
