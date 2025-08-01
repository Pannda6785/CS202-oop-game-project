#include "ButterflyThrall.hpp"

#include "../../../../graphics/TextureManager.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"

ButterflyThrall::ButterflyThrall(Player* owner, Unit::Vec2D spawnPos)
    : Bullet(owner->getPlayerId()), ownerPlayer(owner), pos(spawnPos)
{
    std::vector<const Texture*> anim;
    std::string animPath = "../assets/sprites/lich/bullet/";
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_0.png"));
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_1.png"));
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_2.png"));
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_1.png"));
    constexpr float visibleRatio = 3.5f / 6.0f;
    constexpr float textureWidth = 512;
    constexpr float resize = 2 * RADIUS / (textureWidth * visibleRatio);
    graphics = std::make_unique<AnimatedBulletGraphicsComponent>(this, anim, 6, resize);
    graphics->addStartup(STARTUP * 2 / 3);
    graphics->addOpacity(0.75f);
}

void ButterflyThrall::update(float dt) {
    if (graphics) {
        graphics->update(dt);
    }

    timer += dt;
    shootingTimer += dt;

    if (timer > STARTUP && !damagingHitbox) {
        damagingHitbox = std::make_unique<CircleHitbox>(pos, RADIUS * getSize());
    }
    
    if (timer > STARTUP && shootingTimer >= SHOOT_INTERVAL) {
        shootingTimer -= SHOOT_INTERVAL;
        spawnBullets();
    }
}

void ButterflyThrall::makeDone() {
    forcedDone = true;
}

bool ButterflyThrall::isDone() const {
    if (forcedDone) return true;
    return timer >= LIFETIME;
}

Unit::Vec2D ButterflyThrall::getPosition() const {
    return pos;
}

void ButterflyThrall::spawnBullets() {
    Unit::Vec2D target = ownerPlayer->getTargetPosition();
    Unit::Vec2D dir = (target - pos).normalized();

    std::string bulletTexture = "../assets/sprites/lich/bullet/spr_flo_2_p1_0.png";

    for (int i = -1; i <= 1; ++i) {
        float angleOffset = i * ANGLE;
        float rad = std::atan2(dir.y, dir.x) + angleOffset * 3.14159265f / 180.0f;
        Unit::Vec2D shotDir(std::cos(rad), std::sin(rad));

        constexpr float visibleRatio = 2.0 / 3.0f;
        constexpr float textureWidth = 300;
        constexpr float resize = 2 * BULLET_RADIUS / (textureWidth * visibleRatio);

        auto bullet = std::make_unique<StraightBullet>(
            ownerPlayer->getPlayerId(),
            pos,
            shotDir,
            BULLET_RADIUS,
            BULLET_SPEED,
            BULLET_STARTUP,
            1e9
        );
        auto gfx = std::make_unique<CommonBulletGraphicsComponent>(
            bullet.get(),
            bulletTexture,
            resize,
            0.1f
        );
        bullet->addBulletGraphics(std::move(gfx));
        ownerPlayer->spawnBullet(std::move(bullet));
    }
}