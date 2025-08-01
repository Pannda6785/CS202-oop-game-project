#include "HeroBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../HeroGraphicsComponent.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <cmath>
#include <algorithm>

HeroBasicHandler::HeroBasicHandler(HeroGraphicsComponent* graphics)
    : HoldHandler(Unit::Move::Basic), graphics(graphics) {}

void HeroBasicHandler::update(float dt, const InputBufferer* input) {
    comboHold = std::max(0.0f, comboHold - dt);
    if (comboHold < Unit::EPS) {
        step = 0;
    }
}

void HeroBasicHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Basic) {
        if (move == Unit::Move::Offensive) {
            comboHold = OFFENSIVE_COMBO_HOLD;
        } else {
            comboHold = 0.0f;
            step = 0;
        }
    }
}

void HeroBasicHandler::tick(bool isFocusing) {
    graphics->useBasic(step);

    spawnBullet(isFocusing);

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);

    comboHold = COMBO_HOLD;
    step = (step + 1) % 3;
}

void HeroBasicHandler::spawnBullet(bool isFocusing) {
    constexpr float MY_PI = 3.14159265358979323846f;

    if (lastFocusing != isFocusing) {
        step = 0;
        lastFocusing = isFocusing;
    }

    const Texture* bulletTexture = TextureManager::instance().getTexture("../assets/sprites/hero/bullet/fencer_bullets_0_p1_0000.png");
    constexpr float visibleRatio = 0.25f;
    constexpr float textureWidth = 256;
    constexpr float resize = (RADIUS * 2) / (textureWidth * visibleRatio);

    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D baseDir = player->getArrow();
    float baseAngle = std::atan2(baseDir.y, baseDir.x) * 180.0f / static_cast<float>(MY_PI);

    auto spawn = [&](Unit::Vec2D spawnPos, Unit::Vec2D velocity, float radius, float speed) {
        auto bullet = std::make_unique<StraightBullet>(
            player->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
            spawnPos,
            velocity,
            speed,
            1e9
        );
        bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(spawnPos, radius));
        bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(spawnPos, radius));
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0.0f, STARTUP / 2);
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addVelocityRotation(true);

        player->spawnBullet(std::move(bullet));
    };

    // Unfocused
    if (!isFocusing) {
        if (step == 0) {
            float angles[3] = {12.0f, 0.0f, -12.0f};
            for (float angle : angles) {
                float angleDeg = baseAngle + angle;
                float rad = angleDeg * MY_PI / 180.0f;
                Unit::Vec2D dir(std::cos(rad), std::sin(rad));
                spawn(pos + dir * RADIUS, dir * SPEED, RADIUS, SPEED);
            }
        } else if (step == 1) {
            float angles[4] = {18.0f, 6.0f, -6.0f, -18.0f};
            for (float angle : angles) {
                float angleDeg = baseAngle + angle;
                float rad = angleDeg * MY_PI / 180.0f;
                Unit::Vec2D dir(std::cos(rad), std::sin(rad));
                spawn(pos + dir * RADIUS, dir * SPEED, RADIUS, SPEED);
            }
        } else {
            struct { float angle; float xOffset; float yOffset; } bullets[6] = {
                {0, -90, 60}, {0, 0, 120}, {0, 90, 60},
                {0, -90, -60}, {0, 0, -120}, {0, 90, -60}
            };
            for (auto& b : bullets) {
                float angleDeg = baseAngle + b.angle;
                float rad = angleDeg * MY_PI / 180.0f;
                Unit::Vec2D dir(std::cos(rad), std::sin(rad));
                Unit::Vec2D offset = baseDir.normalized() * b.xOffset + Unit::Vec2D(-baseDir.y, baseDir.x).normalized() * b.yOffset;
                spawn(pos + offset, dir * SPEED, RADIUS, SPEED);
            }
        }
    }
    // Focused
    else {
        if (step == 0) {
            struct { float angle; float speed; } bullets[5] = {
                {14.0f, SPEED}, {0.0f, SPEED}, {-14.0f, SPEED}, {7.0f, SPEED_1}, {-7.0f, SPEED_1}
            };
            for (auto& b : bullets) {
                float angleDeg = baseAngle + b.angle;
                float rad = angleDeg * MY_PI / 180.0f;
                Unit::Vec2D dir(std::cos(rad), std::sin(rad));
                spawn(pos + dir * RADIUS, dir * b.speed, RADIUS, b.speed);
            }
        } else if (step == 1) {
            struct { float angle; float xOffset; float yOffset; } bullets[6] = {
                {11.5f, -30, 90}, {7.5f, 70, 15}, {-2.5f, -30, 80},
                {2.5f, -30, -80}, {-7.5f, 70, -15}, {-11.5f, -30, -90}
            };
            for (auto& b : bullets) {
                float angleDeg = baseAngle + b.angle;
                float rad = angleDeg * MY_PI / 180.0f;
                Unit::Vec2D dir(std::cos(rad), std::sin(rad));
                Unit::Vec2D offset = baseDir.normalized() * b.xOffset + Unit::Vec2D(-baseDir.y, baseDir.x).normalized() * b.yOffset;
                spawn(pos + offset, dir * SPEED_2, RADIUS, SPEED_2);
            }
        } else {
            struct { float angle; float xOffset; float yOffset; } bullets[8] = {
                {0.0f, 110, 0},    // left
                {0.0f, 190, 0},   // right
                {-5.0f, 150, 30},   // upper
                {5.0f, 150, -30},   // lower
                {2.5f, -90, 120},  // rectangle 1
                {-2.5f, -90, -120}, // rectangle 2
                {+2.5f, 110, 120}, // rectangle 3
                {-2.5f, 110, -120} // rectangle 4
            };
            for (auto& b : bullets) {
                float angleDeg = baseAngle + b.angle;
                float rad = angleDeg * MY_PI / 180.0f;
                Unit::Vec2D dir(std::cos(rad), std::sin(rad));
                Unit::Vec2D offset = baseDir.normalized() * b.xOffset + Unit::Vec2D(-baseDir.y, baseDir.x).normalized() * b.yOffset;
                spawn(pos + offset, dir * SPEED_3, RADIUS, SPEED_3);
            }
        }
    }
}