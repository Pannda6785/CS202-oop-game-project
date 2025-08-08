#ifndef DREADFIRE_HPP
#define DREADFIRE_HPP

#include "../../../bullet/Bullet.hpp"

#include <memory>
#include <vector>

class IBulletSpawner;
class Player;

class DreadFire : public Bullet {
    static constexpr float SPEED = 1280.0f;
    static constexpr float RADIUS = 32.0f;
    static constexpr float EXPLODE_DISTANCE = 300; // explode before reaching target this distance
    static constexpr float STARTUP = 0.1f;

    static constexpr int NUM_FRAGMENTS = 5;
    static constexpr float FAN_ANGLE = 100; // degrees
    static constexpr float FRAGMENT_RADIUS = 21.0f;
    static constexpr float FRAGMENT_SPEED = 1020.0f;
    static constexpr float FRAGMENT_SPEED_DECREASE = 600.0f; // per second
    static constexpr float FRAGMENT_LIFETIME = FRAGMENT_SPEED / FRAGMENT_SPEED_DECREASE + 0.1f;

public:

    DreadFire(const Player* player, IBulletSpawner* spawner);

    void update(float dt) override;
    bool isDone() const override;
    void makeDone() override {}

    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getVelocity() const override;

private:
    const Player* player;
    IBulletSpawner* spawner;
    Unit::Vec2D pos;
    Unit::Vec2D dir;
    Unit::Vec2D explodePos;
    float timer;
    bool exploded = false;
    bool warned = false;

    void explode();
};

#endif // DREADFIRE_HPP