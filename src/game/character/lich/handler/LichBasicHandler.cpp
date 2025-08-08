#include "LichBasicHandler.hpp"
#include "../../../player/Player.hpp"
#include "../LichGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"

LichBasicHandler::LichBasicHandler(LichGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void LichBasicHandler::tap(bool isFocusing) {
    graphics->useBasic();

    spawnBullets();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::MovementLock, MOVE_LOCK);
}

void LichBasicHandler::spawnBullets() {
    Unit::Vec2D dir = player->getArrow();

    auto bulletTexture = TextureManager::instance().getTexture("../assets/sprites/lich/bullet/spr_flo_1_p1_0.png");
    constexpr float visibleRatio = 2.0 / 3.0f;
    const float resize = 2 * RADIUS / (bulletTexture->width * visibleRatio);

    for (int i = -1; i <= 1; ++i) {
        float angleOffset = i * ANGLE;
        float rad = std::atan2(dir.y, dir.x) + angleOffset * 3.14159265f / 180.0f;
        Unit::Vec2D shotDir(std::cos(rad), std::sin(rad));

        auto bullet = std::make_shared<StraightBullet>(
            player->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
            player->getPosition(),
            shotDir,
            SPEED,
            1e9
        );
        bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
        bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, 0.1f);

        player->spawnBullet(std::move(bullet));
    }
}