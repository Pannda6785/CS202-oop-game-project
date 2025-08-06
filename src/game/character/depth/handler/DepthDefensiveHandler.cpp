#include "DepthDefensiveHandler.hpp"
#include "../DepthGraphicsComponent.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

DepthDefensiveHandler::DepthDefensiveHandler(DepthGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Defensive, MIN_CASTING_TIME), graphics(graphics) {}

void DepthDefensiveHandler::update(float dt, const InputBufferer* input) {
    CastHandler::update(dt, input);

    if (isCasting) {
        player->applyModifier(Unit::Modifier::MovementModifier, 0.05f, MOVEMENT_MODIFIER_CAST);
        if (auto bullet = bulletRef.lock()) {
            bullet->setPosition(player->getPosition() + SPAWN_DISTANCE * dir);
            chargeGraphicsRef->setRadius(getRadius());
        }
    }
}

void DepthDefensiveHandler::onCastStart() {
    graphics->startCastingDefensive();

    dir = player->getArrow().x < 0 ? Unit::Vec2D{-1, 0} : Unit::Vec2D{1, 0}; 
    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        player->getPosition() + SPAWN_DISTANCE * dir,
        dir,
        [this](float t) {
            if (this->isCasting) return 0.0f;
            if (t - this->castReleaseTime < STARTUP) return 0.0f;
            return SPEED;
        },
        1e9
    );
    bulletRef = bullet;

    std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 220;
    auto chargeGraphics = std::make_unique<ChargeGraphicsComponent>(color);
    chargeGraphics->addInner({255,255,255,210}, MIN_RADIUS / MAX_CASTING_TIME, true);
    chargeGraphicsRef = chargeGraphics.get();

    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(chargeGraphics), 0.0f, 1e9);

    player->spawnBullet(std::move(bullet));
}

void DepthDefensiveHandler::onCastRelease(bool isInterupted) {
    if (isInterupted) {
        if (auto bullet = bulletRef.lock()) bullet->makeDone();
        return;
    }
    graphics->endCastingDefensive();
    castReleaseTime = castingTime;

    float ratio = std::max(MIN_CASTING_TIME, std::min(castingTime, MAX_CASTING_TIME)) / (MAX_CASTING_TIME - MIN_CASTING_TIME);
    float invDuration = INVINCIBILITY_DURATION_MIN + (INVINCIBILITY_DURATION_MAX - INVINCIBILITY_DURATION_MIN) * ratio;
    float moveModDuration = MOVEMENT_MODIFIER_DURATION_MIN + (MOVEMENT_MODIFIER_DURATION_MAX - MOVEMENT_MODIFIER_DURATION_MIN) * ratio;

    player->applyInvincibility(invDuration, false);
    player->applyModifier(Unit::Modifier::MovementModifier, moveModDuration, MOVEMENT_MODIFIER_VALUE);

    player->applyCooldown(Unit::Move::Defensive, COOLDOWN);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);

    if (auto bullet = bulletRef.lock()) {
        auto* composite = dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics());
        
        // Hide old charge graphics
        chargeGraphicsRef->setVisible(false);
        chargeGraphicsRef = nullptr;

        // Add startup charge graphics (for STARTUP * 3/5 duration)
        std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 220;
        auto startupCharge = std::make_unique<ChargeGraphicsComponent>(color, getRadius() * 0.7f , getRadius(), 0.1f);
        startupCharge->addInner({255, 255, 255, 210}, getRadius() / (STARTUP * 3.0f / 5.0f), true);
        composite->addComponent(std::move(startupCharge), castReleaseTime, castReleaseTime + STARTUP * 3.0f / 5.0f);

        // Add blooming texture (animation, fps 8, bloom after 2/3 STARTUP for 1/3 STARTUP)
        std::vector<const Texture*> anim = {
            TextureManager::instance().getTexture("../assets/sprites/depth/bullet/spr_hyd_1_p1_0.png"),
            TextureManager::instance().getTexture("../assets/sprites/depth/bullet/spr_hyd_1_p1_1.png"),
            TextureManager::instance().getTexture("../assets/sprites/depth/bullet/spr_hyd_1_p1_2.png"),
            TextureManager::instance().getTexture("../assets/sprites/depth/bullet/spr_hyd_1_p1_3.png")
        };
        constexpr float visibleRatio = 5.1f / 6.0f;
        float resize = (getRadius() * 2) / (anim[0]->width * visibleRatio);
        auto bloomTex = std::make_unique<TextureBulletGraphicsComponent>(anim, 8, resize);
        bloomTex->addBloom(0, STARTUP * 1.0f / 3.0f);
        bloomTex->addFlip(dir.x < 0, false);
        bloomTex->setLayer(Unit::Layer::Underlay);
        composite->addComponent(std::move(bloomTex), castReleaseTime + STARTUP * 2.0f / 3.0f, 1e9);

        // After startup, bullet starts moving
        bullet->addDamagingHitbox(castReleaseTime + STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), getRadius()));
        bullet->addCleansingHitbox(castReleaseTime + STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), getRadius() * CLEANSE_RADIUS_RATIO));
    }
}

float DepthDefensiveHandler::getRadius() const {
    float ratio = std::max(MIN_CASTING_TIME, std::min(castingTime, MAX_CASTING_TIME)) / (MAX_CASTING_TIME - MIN_CASTING_TIME);
    return MIN_RADIUS + (MAX_RADIUS - MIN_RADIUS) * ratio;
}