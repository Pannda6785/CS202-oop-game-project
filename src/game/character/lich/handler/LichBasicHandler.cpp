#include "LichBasicHandler.hpp"
#include "../../../player/Player.hpp"
#include "../LichGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"

LichBasicHandler::LichBasicHandler(LichGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void LichBasicHandler::tap(bool isFocusing) {
    // graphics->useBasic();

    spawnBullets();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, 0.5f);
}

void LichBasicHandler::spawnBullets() {
    Unit::Vec2D dir = player->getArrow();

    std::string bulletTexture = "../assets/sprites/lich/bullet/spr_flo_1_p1_0.png";

    for (int i = -1; i <= 1; ++i) {
        float angleOffset = i * ANGLE;
        float rad = std::atan2(dir.y, dir.x) + angleOffset * 3.14159265f / 180.0f;
        Unit::Vec2D shotDir(std::cos(rad), std::sin(rad));

        constexpr float visibleRatio = 2.0 / 3.0f;
        constexpr float textureWidth = 128;
        constexpr float resize = 2 * RADIUS / (textureWidth * visibleRatio);

        auto bullet = std::make_unique<StraightBullet>(
            player->getPlayerId(),
            player->getPosition(),
            shotDir,
            RADIUS,
            SPEED,
            STARTUP,
            1e9
        );
        auto gfx = std::make_unique<CommonBulletGraphicsComponent>(
            bullet.get(),
            bulletTexture,
            resize,
            0.1f
        );
        bullet->addBulletGraphics(std::move(gfx));
        player->spawnBullet(std::move(bullet));
    }
}