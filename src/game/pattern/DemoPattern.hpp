#ifndef DEMO_PATTERN_HPP
#define DEMO_PATTERN_HPP

#include "Pattern.hpp"

/*
    This shoots bullets downward (like rain) but in deterministic and orderly manner
*/

class DemoPattern : public Pattern {
public:
    explicit DemoPattern(IBulletSpawner* spawner);

    void init() override;
    void update(float dt) override;

private:
    static constexpr int OWNER_ID = 2; // used for all bullets in of 3rd party pattern 
    static constexpr float WAVE_INTERVAL = 7.0f; // spawn a wave every X seconds. Each wave contains multiple barrage
    static constexpr int NUM_BARRAGES = 4; // how long the wave lasts
    static constexpr int NUM_BULLETS = 18; // spawn this across Unit::BATTLEFIELD_WIDTH
    static constexpr float BARRAGE_INTERVAL = 0.45f; 
    static constexpr float BULLET_RADIUS = 12.0f;
    static constexpr float BULLET_SPEED = 480.0f;
    static constexpr float BULLET_STARTUP = 0.2f;
    static constexpr float BULLET_LIFESPAN = 10000.0f;

    static constexpr const char* TEXTURE_PATH = "../assets/sprites/pattern/bullet/beast_bullets_0_p1_0002.png";
    static constexpr float VISIBLE_RATIO = 0.25f;
    static constexpr float TEXTURE_WIDTH = 150;

    float timer;
};

#endif // DEMO_PATTERN_HPP