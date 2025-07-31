#include "DepthOffensiveHandler.hpp"
#include "../../../player/Player.hpp"
#include "../DepthGraphicsComponent.hpp"
#include "../../../bullet/StraightBulletPro.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

#include <cmath>
#include <algorithm>

DepthOffensiveHandler::DepthOffensiveHandler(DepthGraphicsComponent* graphics)
    : HoldHandler(Unit::Move::Offensive), graphics(graphics) {}

void DepthOffensiveHandler::update(float dt, const InputBufferer* input) {
    if (comboHold > Unit::EPS) {
        comboHold -= dt;
        if (comboHold < Unit::EPS) {
            step = 0;
            comboHold = 0.0f;
            player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
        }
    }
}

void DepthOffensiveHandler::listen(Unit::Move move) {
    if (comboHold > Unit::EPS) {
        if (move != Unit::Move::Offensive) {
            comboHold = 0.0f;
            step = 0;
            player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
        }
    }
}

void DepthOffensiveHandler::tick(bool isFocusing) {
    graphics->useOffensive();

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_VALUE);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);

    comboHold = COMBO_HOLD;
    step = std::min(step + 1, NUM_STEPS - 1);
}

void DepthOffensiveHandler::spawnBullet() {
    constexpr float PI = 3.14159265358979323846f;
    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D aimDir = player->getArrow().normalized();

    float spread = ANGLE_SPREAD[step];
    int numBullets = NUM_BULLETS;
    float baseAngle = std::atan2(aimDir.y, aimDir.x) * 180.0f / static_cast<float>(PI);

    std::string bulletTexture = "../assets/sprites/depth/bullet/hydra_bullets_0_p1_0005.png";
    constexpr float visibleRatio = 3.5f / 6.0f;
    constexpr float textureWidth = 512;
    constexpr float resize = (RADIUS * 2) / (textureWidth * visibleRatio);

    auto speedFunc = [fast = SPEED_FAST, slow = SPEED_SLOW, fastDur = FAST_DURATION[step]](float t) {
        return (t < fastDur) ? fast : slow;
    };

    float lifetime = FAST_DURATION[step] + SLOW_DURATION;

    for (int i = 0; i < numBullets; ++i) {
        float angleDeg = baseAngle - spread + (2.0f * spread) * i / (numBullets - 1);
        float rad = angleDeg * PI / 180.0f;
        Unit::Vec2D dir(std::cos(rad), std::sin(rad));

        auto bullet = std::make_unique<StraightBulletPro>(
            player->getPlayerId(),
            pos + dir * RADIUS,
            dir,
            speedFunc,
            lifetime
        );
        auto gfx = std::make_unique<CommonBulletGraphicsComponent>(
            bullet.get(),
            bulletTexture,
            resize,
            STARTUP,
            true
        );
        bullet->addBulletGraphics(std::move(gfx));
        bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(Unit::Vec2D(), RADIUS));
        bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(Unit::Vec2D(), RADIUS));
        player->spawnBullet(std::move(bullet));
    }
}