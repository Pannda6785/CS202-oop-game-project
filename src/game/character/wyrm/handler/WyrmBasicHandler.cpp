#include "WyrmBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"

#include <cmath>

WyrmBasicHandler::WyrmBasicHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void WyrmBasicHandler::update(float dt, const InputBufferer* input) {
    comboHold = std::max(0.0f, comboHold - dt);
    if (comboHold < Unit::EPS) {
        step = 0;
    }
}

void WyrmBasicHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Basic) {
        comboHold = 0.0f;
        step = 0;
    }
}

void WyrmBasicHandler::tap(bool isFocusing) {
    graphics->useBasic();

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::moveToLock(move), step < STEP_COUNT - 1 ? SHORT_LOCK : LONG_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);

    ++step;
    if (step < STEP_COUNT) {
        comboHold = COMBO_HOLD;
    } else {
        step = 0;
        comboHold = 0.0f;
    }
}

void WyrmBasicHandler::spawnBullet() {
    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D target = player->getTargetPosition();
    Unit::Vec2D baseDir = (target - pos).normalized();

    float baseAngle = std::atan2(baseDir.y, baseDir.x) * 180.0f / static_cast<float>(M_PI);
    int clampedStep = std::min(step, STEP_COUNT - 1);

    for (int i = 0; i < NUM_BULLETS[clampedStep]; ++i) {
        float angleDeg = OFFSET[clampedStep] + i * BULLET_SPACING;
        float finalAngle = baseAngle + angleDeg;
        float rad = finalAngle * static_cast<float>(M_PI) / 180.0f;

        Unit::Vec2D dir(std::cos(rad), std::sin(rad));
        Unit::Vec2D velocity = dir * SPEED;

        std::string bulletTexture = "../assets/sprites/wyrm/bullet/nidhogg_bullet_0_p1_0000.png";
        constexpr float visibleRatio = 0.14f;
        constexpr float textureWidth = 256;
        constexpr float resize = (RADIUS * 2) / (textureWidth * visibleRatio);

        auto gfx = std::make_unique<CommonBulletGraphicsComponent>(
            bulletTexture,
            resize,
            STARTUP * 0.8f,
            true
        );

        auto bullet = std::make_unique<StraightBullet>(
            player->getPlayerId(),
            pos + dir * RADIUS,
            velocity,
            RADIUS,
            SPEED,
            STARTUP,
            1000,
            std::move(gfx)
        );

        player->spawnBullet(std::move(bullet));
    }
}