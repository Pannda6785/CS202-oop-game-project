#include "LichDefensiveHandler.hpp"
#include "../LichGraphicsComponent.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

LichDefensiveHandler::LichDefensiveHandler(LichGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Defensive, MIN_CASTING_TIME), graphics(graphics) {}

void LichDefensiveHandler::update(float dt, const InputBufferer* input) {
    CastHandler::update(dt, input);

    for (auto it = pastBullets.begin(); it != pastBullets.end();) {
        it->first -= dt;
        if (it->first <= 0) {
            if (auto bullet = it->second.lock()) {
                bullet->makeDone();
                it = pastBullets.erase(it);
            } else {
                it = pastBullets.erase(it);
            }
        } else {
            it++;
        }
    }

    if (isCasting) {
        player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION_CASTING, MOVEMENT_MODIFIER_VALUE_CASTING);
        if (auto bullet = bulletRef.lock()) {
            bullet->setPosition(player->getPosition());
            if (chargeGraphicsRef) chargeGraphicsRef->setRadius(getRadius());
        }
    }
}

void LichDefensiveHandler::onCastStart() {
    graphics->startCastingDefensive();

    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        player->getPosition(),
        Unit::Vec2D{0.0f, 0.0f},
        0.0f,
        1e9
    );
    bulletRef = bullet;

    std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 220;
    auto chargeGraphics = std::make_unique<ChargeGraphicsComponent>(color);
    chargeGraphics->addInner({255,255,255,210}, MIN_RADIUS / (15 * MIN_CASTING_TIME), true);
    chargeGraphicsRef = chargeGraphics.get();

    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(chargeGraphics));

    player->spawnBullet(std::move(bullet));
}

void LichDefensiveHandler::onCastRelease(bool isInterrupted) {
    if (isInterrupted) {
        if (auto bullet = bulletRef.lock()) bullet->makeDone();
        return;
    }
    graphics->endCastingDefensive(STARTUP * 3 / 5.0f);
    
    player->applyInvincibility(INVINCIBILITY, false);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION_RELEASE, MOVEMENT_MODIFIER_VALUE_RELEASE);
    player->applyCooldown(Unit::Move::Defensive, COOLDOWN);

    if (auto bullet = bulletRef.lock()) {
        auto* composite = dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics());

        // Hide old charge graphics
        chargeGraphicsRef->setVisible(false);
        chargeGraphicsRef = nullptr;

        float castReleaseTime = castingTime;

        // Add startup charge graphics (for STARTUP * 3/5 duration)
        std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 190;
        auto startupCharge = std::make_unique<ChargeGraphicsComponent>(color, getRadius() , getRadius(), 0.1f);
        startupCharge->addInner({255, 255, 255, 210}, getRadius() / (STARTUP * 3.0f / 5.0f), true);
        composite->addComponent(std::move(startupCharge), castReleaseTime, castReleaseTime + STARTUP * 3.0f / 5.0f);

        // add ripple graphics (for STARTUP)
        auto ripple = std::make_unique<RippleGraphicsComponent>(std::array<int, 4>{255, 255, 255, 200}, 3, 0, getRadius(), STARTUP * 2.0f / 3.0f, STARTUP, 5);
        composite->addComponent(std::move(ripple), castReleaseTime + STARTUP * 3.0f / 5.0f, castReleaseTime + STARTUP * 3.0f);

        // Add blooming texture (animation, fps 8, bloom after 2/3 STARTUP for 1/3 STARTUP)
        const Texture* tex = TextureManager::instance().getTexture("../assets/sprites/lich/bullet/spr_flo_3_p1_0.png");
        constexpr float visibleRatio = 4.85f / 6.0f;
        float resize = (getRadius() * 2) / (tex->width * visibleRatio);
        auto bloomTex = std::make_unique<TextureBulletGraphicsComponent>(tex, resize);
        bloomTex->addBloom(0, STARTUP / 3.0f);
        bloomTex->addDebloom(STARTUP / 3.0f + DURATION, STARTUP / 3.0f + DURATION + STARTUP / 3.0f);
        bloomTex->addRotation(-1.0f / 10.0f);
        bloomTex->setLayer(Unit::Layer::Underlay);
        composite->addComponent(std::move(bloomTex), castReleaseTime + STARTUP * 2.0f / 3.0f, castReleaseTime + STARTUP + DURATION + STARTUP / 3.0f);

        // After release, bullet stays at position (no movement)
        bullet->addDamagingHitbox(castReleaseTime + STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), getRadius()));
        bullet->addCleansingHitbox(castReleaseTime + STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), getRadius() * CLEANSE_RATIO));
        bullet->removeCleansingHitbox(castReleaseTime + STARTUP + 0.1f);
        bullet->removeDamagingHitbox(castReleaseTime + STARTUP + DURATION);
        pastBullets.emplace_back(DURATION + STARTUP / 3.0f, bulletRef);
        bulletRef.reset();
    }
}

float LichDefensiveHandler::getRadius() const {
    return MIN_RADIUS + castingTime * RADIUS_RATE;
}