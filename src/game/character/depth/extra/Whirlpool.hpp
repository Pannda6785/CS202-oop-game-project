#ifndef WHIRLPOOL_HPP
#define WHIRLPOOL_HPP

#include "../../../bullet/Bullet.hpp"

#include <memory>

class Player;
class TextureBulletGraphicsComponent;

class Whirlpool : public Bullet {
    static constexpr float STARTUP = 0.680f; // aura for startup, once bullet is spawned it has hitbox and velocity immediately
    static constexpr float BASE_RADIUS = 150;
    static constexpr float RADIUS_INCREASE = 30; // per second
    static constexpr float SPEED = 225;
    
    static constexpr float EXPLODE_DELAY = 0.600f; // when detonate, it waits this long before it starts expanding
    static constexpr float EXPLODE_DURATION = 0.200f; // time to reach full explosion size, explosion linearly doubles the radius
    static constexpr float LIFETIME = 1.200f; // how long it lives after detonation

public: 
    Whirlpool(const Player* player);

    void update(float dt) override;
    bool isDone() const override;
    void makeDone() override {}

    void detonate();

    Unit::Vec2D getPosition() const override;

private:
    const Player* player;
    TextureBulletGraphicsComponent* textureGraphicsRef;

    Unit::Vec2D pos;
    Unit::Vec2D dir;

    float timer = 0;
    float initialSize = 1.0f; // when started up
    bool isStartedUp = false;
    bool isDetonating = false;
    float timeDetonated;
    Unit::Vec2D deflectedSource;

    bool soundPlayed = false;

};

#endif // WHIRLPOOL_HPP