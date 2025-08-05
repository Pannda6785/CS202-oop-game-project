#include "WyrmBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

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
    player->applyLock(Unit::Lock::BasicLock, step < STEP_COUNT - 1 ? SHORT_LOCK : LONG_LOCK);
    player->applyLock(Unit::Lock::WideLock, step < STEP_COUNT - 1 ? SHORT_LOCK : LONG_LOCK);
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
    constexpr float MY_PI = 3.14159265358979323846f;

    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D baseDir = player->getArrow();

    float baseAngle = std::atan2(baseDir.y, baseDir.x) * 180.0f / static_cast<float>(MY_PI);
    int clampedStep = std::min(step, STEP_COUNT - 1);

    for (int i = 0; i < NUM_BULLETS[clampedStep]; ++i) {
        float angleDeg = OFFSET[clampedStep] + i * BULLET_SPACING;
        float finalAngle = baseAngle + angleDeg;
        float rad = finalAngle * static_cast<float>(MY_PI) / 180.0f;

        Unit::Vec2D dir(std::cos(rad), std::sin(rad));

        auto bulletTexture = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/nidhogg_bullet_0_p1_0000.png");
        constexpr float visibleRatio = 0.14f;
        const float resize = (RADIUS * 2) / (bulletTexture->width * visibleRatio);

        auto bullet = std::make_shared<StraightBullet>(
            player->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
            player->getPosition(),
            dir,
            SPEED,
            1e9
        );
        bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
        bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, STARTUP);
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addVelocityRotation(true);

        player->spawnBullet(std::move(bullet));
    }
}