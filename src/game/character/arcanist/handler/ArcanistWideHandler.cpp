#include "ArcanistWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../ArcanistGraphicsComponent.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"

#include <cmath>
#include <algorithm>

ArcanistWideHandler::ArcanistWideHandler(ArcanistGraphicsComponent* graphics)
    : HoldHandler(Unit::Move::Wide), graphics(graphics) {}

void ArcanistWideHandler::update(float dt, const InputBufferer* input) {
    comboHold = std::max(0.0f, comboHold - dt);
    if (comboHold < Unit::EPS) {
        step = 0;
    }
}

void ArcanistWideHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Wide) {
        comboHold = 0.0f;
        step = 0;   
    }
}

void ArcanistWideHandler::tick(bool isFocusing) {
    graphics->useWide();
    AudioManager::getInstance().playSound("Attack1");

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);

    comboHold = COMBO_HOLD;
    step = (step + 1) % 2;
}

void ArcanistWideHandler::spawnBullet() {
    constexpr float MY_PI = 3.14159265358979323846f;

    const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/caster_bullets_0_p1_0001.png");
    constexpr float visibleRatio = 0.41f;
    const float resize = (RADIUS * 2) / (texture->width * visibleRatio);

    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D targetDir = (player->getTargetPosition() - pos).normalized();
    float baseAngle = std::atan2(targetDir.y, targetDir.x) * 180.0f / MY_PI;

    auto spawn = [&](float angleOffset, float delay) {
        for (int i = 0; i < 5; i++) {
            float angleDeg = baseAngle + angleOffset + 72 * i;
            float rad = angleDeg * MY_PI / 180.0f;
            Unit::Vec2D dir(std::cos(rad), std::sin(rad));
            auto bullet = std::make_shared<StraightBullet>(
                player->getPlayerId(),
                std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                pos,
                dir,
                [delay](float t) -> float { 
                    if (t > delay) return SPEED;
                    return 0;
                },
                1e9
            );
            bullet->addLifeHitbox(0.0f + delay, std::make_unique<CircleHitbox>(pos, RADIUS));
            bullet->addDamagingHitbox(STARTUP + delay, std::make_unique<CircleHitbox>(pos, RADIUS));
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0 + delay, STARTUP + delay);
            player->spawnBullet(std::move(bullet));
        }
    };

    if (step == 0) {
        spawn(-45, 0);
        spawn(-27, DELAY);
    } else {
        spawn(-9, 0);
        spawn(9, DELAY);
    }
}