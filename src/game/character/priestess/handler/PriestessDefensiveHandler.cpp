#include "PriestessDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"
#include "../../../bullet/effect/DecorateGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

PriestessDefensiveHandler::PriestessDefensiveHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void PriestessDefensiveHandler::tap(bool isFocusing) {
    graphics->yell(0.8f);
    AudioManager::getInstance().playSound("PriestessDefensive");

    spawnBullet();

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
}

void PriestessDefensiveHandler::spawnBullet() {
    
    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        player->getPosition(),
        Unit::Vec2D(0, 0), 
        0,
        LIFETIME + 0.2f // 0.1s fade out
    );
    
    { // graphcics
        std::vector<const Texture*> anim = {
            TextureManager::instance().getTexture("../assets/sprites/priestess/bullet/spr_prs_def_0.png"),
            TextureManager::instance().getTexture("../assets/sprites/priestess/bullet/spr_prs_def_1.png"),
            TextureManager::instance().getTexture("../assets/sprites/priestess/bullet/spr_prs_def_2.png"),
            TextureManager::instance().getTexture("../assets/sprites/priestess/bullet/spr_prs_def_3.png")
        };
        constexpr float visibleRatio = 0.93f;
        float resize = (BASE_RADIUS * 2.0f) / (anim[0]->width * visibleRatio);

        auto texture = std::make_unique<TextureBulletGraphicsComponent>(anim, 5, resize);
        texture->addFadeout(LIFETIME, LIFETIME + 0.2f);
        texture->setLayer(Unit::Layer::Underlay);

        auto ripple = std::make_unique<RippleGraphicsComponent>(std::array<int, 4>{255, 255, 255, 210}, 3, BASE_RADIUS, BASE_RADIUS + 60, 0.6, 0.3f, 10);
        ripple->setLayer(Unit::Layer::Underlay);

        auto ripple2 = std::make_unique<RippleGraphicsComponent>(std::array<int, 4>{255, 255, 255, 160}, 3, BASE_RADIUS, BASE_RADIUS + 45, 0.3, 0.3f, 8);
        ripple2->setLayer(Unit::Layer::Underlay);

        auto decorate = std::make_unique<DecorateGraphicsComponent>();
        decorate->setLayer(Unit::Layer::Underlay - 2);
        auto color = graphics->getSignatureColor(); color[3] = 75;
        decorate->addCircle(color, BASE_RADIUS * 0.98f);

        dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(texture));
        dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(ripple));
        dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(ripple2), LIFETIME - 0.1, LIFETIME + 0.2f);
        dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(decorate), 0, LIFETIME);
    }

    { // hitboxes
        bullet->addInvincibilityHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), BASE_RADIUS), true, player->getPlayerId(), INVINCIBILITY_DURATION);
        bullet->addInvincibilityHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), BASE_RADIUS), false, player->getPlayerId() ^ 1, INVINCIBILITY_DURATION);
        bullet->addCleansingHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), CLEANSE_RADIUS));
        bullet->addModifierHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), BASE_RADIUS), Unit::Modifier::MovementModifier,
                                  player->getPlayerId() ^ 1, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
        
        bullet->removeModifierHitboxes(0.1f);
        bullet->removeInvincibilityHitboxes(LIFETIME);
        bullet->removeCleansingHitbox(LIFETIME);
    }

    player->spawnBullet(std::move(bullet));
}