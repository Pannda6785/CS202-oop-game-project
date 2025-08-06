#include "ButterflyThrall.hpp"

#include "../../../../graphics/TextureManager.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"

ButterflyThrall::ButterflyThrall(Player* owner, Unit::Vec2D spawnPos)
    : Bullet(owner->getPlayerId(), std::make_unique<CompositeBulletGraphicsComponent>()), 
    ownerPlayer(owner), pos(spawnPos)
{
    std::vector<const Texture*> anim;
    std::string animPath = "../assets/sprites/lich/bullet/";
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_0.png"));
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_1.png"));
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_2.png"));
    anim.push_back(TextureManager::instance().getTexture(animPath + "spr_flo_0_p1_1.png"));
    constexpr float visibleRatio = 3.5f / 6.0f;
    const float resize = 2 * RADIUS / (anim[0]->width * visibleRatio);
    auto texture = std::make_unique<TextureBulletGraphicsComponent>(anim, 6, resize);
    texture->setLayer(Unit::Layer::Underlay);
    texture->addFadein(0, STARTUP * 2 / 3);
    texture->addFadeout(LIFETIME - STARTUP * 1 / 3, LIFETIME);
    texture->addTint({255, 255, 255, 190});
    textureGraphicsRef = texture.get();
    dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get())->addComponent(std::move(texture));
}

void ButterflyThrall::update(float dt) {
    if (graphics) {
        graphics->update(dt);
    }

    timer += dt;
    if (timer > STARTUP && !damagingHitbox) {
        damagingHitbox = std::make_unique<CircleHitbox>(pos, RADIUS * getSize());
    }

    if (forcedDone) {
        remainingForcedDoneTime -= dt;
        textureGraphicsRef->addTint({255, 255, 255, static_cast<int>(190 * remainingForcedDoneTime / (STARTUP * 1 / 3))});
    }

    if (timer > STARTUP) {
        shootingTimer += dt;
        constexpr float CHARGE = 0.25f;
        if (shootingTimer - dt < SHOOT_INTERVAL - CHARGE && shootingTimer >= SHOOT_INTERVAL - CHARGE) {
            auto charge = std::make_unique<ChargeGraphicsComponent>(std::array<int, 4>{255, 255, 255, 100}, RADIUS * 2.2f, RADIUS, CHARGE);
            charge->setLayer(Unit::Layer::Underlay - 1);
            dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get())->addComponent(std::move(charge), 0, timer + CHARGE);
        }
        if (shootingTimer >= SHOOT_INTERVAL) {
            shootingTimer -= SHOOT_INTERVAL;
            spawnBullets();
        }
    }
}

void ButterflyThrall::makeDone() {
    forcedDone = true;
    remainingForcedDoneTime = STARTUP * 1 / 3;
}

bool ButterflyThrall::isDone() const {
    if (forcedDone && remainingForcedDoneTime < 0) return true;
    return timer >= LIFETIME;
}

Unit::Vec2D ButterflyThrall::getPosition() const {
    return pos;
}

void ButterflyThrall::spawnBullets() {
    Unit::Vec2D target = ownerPlayer->getTargetPosition();
    Unit::Vec2D dir = (target - pos).normalized();

    auto bulletTexture = TextureManager::instance().getTexture("../assets/sprites/lich/bullet/spr_flo_2_p1_0.png");
    constexpr float visibleRatio = 2.0 / 3.0f;
    const float resize = 2 * BULLET_RADIUS / (bulletTexture->width * visibleRatio);

    for (int i = -1; i <= 1; ++i) {
        float angleOffset = i * ANGLE;
        float rad = std::atan2(dir.y, dir.x) + angleOffset * 3.14159265f / 180.0f;
        Unit::Vec2D shotDir(std::cos(rad), std::sin(rad));

        auto bullet = std::make_shared<StraightBullet>(
            ownerPlayer->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
            pos, 
            shotDir,
            BULLET_SPEED,
            1e9
        );
        bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), BULLET_RADIUS));
        bullet->addDamagingHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), BULLET_RADIUS));

        ownerPlayer->spawnBullet(std::move(bullet));
    }
}