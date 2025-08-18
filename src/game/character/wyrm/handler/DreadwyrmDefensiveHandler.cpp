#include "DreadwyrmDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"

DreadwyrmDefensiveHandler::DreadwyrmDefensiveHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void DreadwyrmDefensiveHandler::tap(bool isFocusing) {
    graphics->roar(STARTUP - 0.1f, LIFETIME - STARTUP);
    AudioManager::getInstance().playSound("WyrmCharge");

    player->applyInvincibility(INVINCIBILITY_DURATION, true);

    spawnBullet();

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyLock(Unit::Lock::BasicLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::WideLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, ACTION_LOCK);
}

void DreadwyrmDefensiveHandler::spawnBullet() {
    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        player->getPosition(),
        Unit::Vec2D{0, 0},
        0,
        LIFETIME + 0.1f // debloom
    );

    std::vector<const Texture*> textures(2);
    textures[0] = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/spr_drk_1_p1_0.png");
    textures[1] = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/spr_drk_1_p1_1.png");
    const float noviVisibleRatio = 4.278f / 6.0f;
    const float resize = 2 * RADIUS / (noviVisibleRatio * textures[0]->width);

    bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS));
    bullet->removeDamagingHitbox(LIFETIME);


    std::array<int, 4> purple = {118, 11, 186, 240};
    std::array<int, 4> color = purple; color[3] = 170;
    auto chargeGraphics = std::make_unique<ChargeGraphicsComponent>(color, RADIUS, RADIUS, STARTUP - 0.15);
    chargeGraphics->addInner(color, RADIUS / STARTUP, false);

    std::array<int, 4> tint = {255, 255, 255, 230};
    auto textureGraphics = std::make_unique<TextureBulletGraphicsComponent>(textures, 8, resize);
    textureGraphics->setLayer(Unit::Layer::Underlay);
    textureGraphics->addBloom(0, 0.1f);
    textureGraphics->addDebloom(0.1 + LIFETIME - STARTUP, 0.2f + LIFETIME - STARTUP);
    textureGraphics->addTint(tint);

    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(chargeGraphics), 0.0f, STARTUP - 0.15f);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(textureGraphics), STARTUP - 0.1f, LIFETIME + 0.1f);

    bullet->addStartupSound("WyrmBlast");

    player->spawnBullet(std::move(bullet));
}