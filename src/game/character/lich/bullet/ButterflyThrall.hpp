#ifndef BUTTERFLY_THRALL_HPP
#define BUTTERFLY_THRALL_HPP

#include "../../../bullet/Bullet.hpp"

#include <memory>

class Player;
class TextureBulletGraphicsComponent;

class ButterflyThrall : public Bullet {
    static constexpr float LIFETIME = 20.8f;
    static constexpr float SHOOT_INTERVAL = 1.8f;
    static constexpr float RADIUS = 60.0f; // damaging radius of the butterfly itself
    static constexpr float STARTUP = 0.680f;

    // bullet it spawns
    static constexpr float BULLET_SPEED = 9 * 60;
    static constexpr float BULLET_RADIUS = 30;
    static constexpr float ANGLE = 6; // shoot three bullets [-ANGLE, 0, +ANGLE] degrees

public:
    ButterflyThrall(Player* owner, Unit::Vec2D spawnPos);

    void update(float dt) override;
    bool isDone() const override;
    void makeDone();

    Unit::Vec2D getPosition() const override;

private:
    Player* ownerPlayer;
    Unit::Vec2D pos;
    TextureBulletGraphicsComponent* textureGraphicsRef;

    float timer = 0;
    float shootingTimer = 0;
    bool forcedDone = false;
    float remainingForcedDoneTime;

    void spawnBullets();

};

#endif // BUTTERFLY_THRALL_HPP