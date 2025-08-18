#include "ArcanistBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../ArcanistGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"

#include <cmath>

ArcanistBasicHandler::ArcanistBasicHandler(ArcanistGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void ArcanistBasicHandler::tap(bool isFocusing) {
    graphics->useBasic();
    AudioManager::getInstance().playSound("Attack5");

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_VALUE);
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
}

void ArcanistBasicHandler::spawnBullet() {
    constexpr float MY_PI = 3.14159265358979323846f;

    const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/caster_bullets_0_p1_0002.png");
    constexpr float visibleRatio = 2.0 / 3.0f;
    const float resize = (RADIUS * 2) / (texture->width * visibleRatio);

    Unit::Vec2D baseDir = player->getArrow();

    auto rotateVec = [](const Unit::Vec2D& v, float degrees) {
        float radians = degrees * MY_PI / 180.0f;
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);
        return Unit::Vec2D{
            v.x * cosA - v.y * sinA,
            v.x * sinA + v.y * cosA
        };
    };

    auto fireLayer = [&](const std::vector<float>& angleOffsets, float speed) {
        for (float angleOffset : angleOffsets) {
            Unit::Vec2D dir = rotateVec(baseDir, angleOffset);
            auto bullet = std::make_shared<StraightBullet>(
                player->getPlayerId(),
                std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                player->getPosition(),
                dir,
                speed,
                1e9
            );
            bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
            bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, STARTUP / 3);
            player->spawnBullet(std::move(bullet));
        }
    };

    fireLayer({-4.5f, 4.5f}, SPEED1); // Layer 1
    fireLayer({-9.0f, 0.0f, 9.0f}, SPEED2); // Layer 2
    fireLayer({-4.5f, 4.5f}, SPEED3); // Layer 3
}