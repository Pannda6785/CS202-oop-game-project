#ifndef DEATHTOLL_HPP
#define DEATHTOLL_HPP

#include "../../../bullet/Bullet.hpp"

class Player;

class DeathToll : public Bullet {
    static constexpr float RADIUS = 247.0f;
    static constexpr float STARTUP = 3.5f;
    static constexpr float DURATION = 4.5f;
    static constexpr float SPEED = 100.0f;

    static constexpr float FADEOUT = 0.3f;

public:
    DeathToll(const Player* player);

    void update(float dt) override;
    bool isDone() const override;
    void makeDone() override {}

    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getVelocity() const override;

private:
    const Player* player;
    Unit::Vec2D pos;
    float time = 0;
    bool active = false;
    bool warned = false;
};

#endif // DEATHTOLL_HPP