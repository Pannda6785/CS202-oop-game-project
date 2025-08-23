#ifndef STATIC_GREEN_HPP
#define STATIC_GREEN_HPP

#include "Pattern.hpp"
#include <vector>
#include <memory>

class Bullet;
class IWorldView;

/*
    B1: rising electric balls
    B2: speedy targeted electric shock
*/

class StaticGreen : public Pattern {
    static constexpr int OWNER_ID = 2; // used for all bullets in of 3rd party pattern
    
    static constexpr float B1_START_TIME = 2;
    static constexpr float B1_FREQUENCY = 12;
    static constexpr float B1_SPAWN_RANGE = 400;
    static constexpr float B1_SPEED = 50;
    static constexpr float B1_RADIUS = 60;
    static constexpr float B1_STARTUP = 0.5f;
    
    static constexpr float B2_FREQUENCY = 2.5;
    static constexpr float B2_SPEED = 4200;
    static constexpr float B2_RADIUS = 15;
    static constexpr float B2_WARNING_DELAY = 0.400f;

public:
    explicit StaticGreen(IBulletSpawner* spawner, const IWorldView* worldView);

    void init() override;
    void update(float dt) override;

private:
    const IWorldView* worldView;

    std::vector<std::pair<std::weak_ptr<Bullet>, float>> bullets;
    float timer;
    float b1timer;
};

#endif // STATIC_GREEN_HPP