#include "ArcanistDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../ArcanistGraphicsComponent.hpp"

#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"

ArcanistDefensiveHandler::ArcanistDefensiveHandler(ArcanistGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void ArcanistDefensiveHandler::tap(bool isFocusing) {
    graphics->useDefensive();
    AudioManager::getInstance().playSound("ArcanistDefensive1");

    spawnBullet(isFocusing);

    player->applyImplicitMoveLock();
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
    player->applyCooldown(Unit::Move::Defensive, COOLDOWN);
    if (isFocusing) player->applyInvincibility(INVINCIBILITY, false);
}

void ArcanistDefensiveHandler::spawnBullet(bool isFocusing) {
    // calculate trajectory and startup
    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D arrow = player->getArrow().x < 0 ? Unit::Vec2D(-1, 0) : Unit::Vec2D(1, 0);
    Unit::Vec2D target = player->getTargetPosition();

    float toTravel = arrow.dot(target - pos);
    if (isFocusing) toTravel = 0;
    float startupTime = std::max(MIN_STARTUP, computeTravelTime(toTravel));

    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        pos,
        arrow,
        [startupTime, isFocusing](float t) -> float {
            if (isFocusing) return 0.0f;
            if (t > startupTime) return 0.0f;
            if (t < START_GAINING_WHEN) return 0.0f;
            if (t > STOP_GAINING_WHEN) return MAX_SPEED;
            return (t - START_GAINING_WHEN) / (STOP_GAINING_WHEN - START_GAINING_WHEN) * MAX_SPEED;
        },
        startupTime + ACTIVE_TIME + 0.2f
    );

    { // graphics
        auto* composite = dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics());
    
        const Texture* tex = TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/spr_cas_1_p1_2_1.png");
        constexpr float visibleRatio = 0.96f;
        const float resize = (2 * RADIUS) / (tex->width * visibleRatio);
        const Texture* overlay = TextureManager::instance().getTexture("../assets/sprites/universal/spr_endmenu_back_0.png");
        constexpr float overlayVisibleRatio = 0.96f;
        const float overlayResize = (2 * RADIUS * 1.25f) / (overlay->width * overlayVisibleRatio);

        auto texGraphics = std::make_unique<TextureBulletGraphicsComponent>(tex, resize);
        texGraphics->addFadein(0.0f, 0.35f);
        texGraphics->addFadeout(startupTime + ACTIVE_TIME - 0.1f, startupTime + ACTIVE_TIME + 0.2f);
        composite->addComponent(std::move(texGraphics));

        auto flash = std::make_unique<TextureBulletGraphicsComponent>(overlay, overlayResize);
        flash->addFadein(0.0f, 0.05f);
        flash->addFadeout(0.05f, 0.6f);
        flash->addTint({255, 255, 255, 200});
        flash->setLayer(Unit::Layer::Overlay);
        composite->addComponent(std::move(flash), startupTime);

        auto ripple1 = std::make_unique<RippleGraphicsComponent>(std::array<int, 4>{255, 255, 255, 160}, 3, RADIUS, RADIUS * 1.15f, 0.3, 0.3f, 8);
        ripple1->setLayer(Unit::Layer::Overlay);
        composite->addComponent(std::move(ripple1), startupTime, startupTime + 0.3f);
        
        auto ripple2 = std::make_unique<RippleGraphicsComponent>(std::array<int, 4>{255, 255, 255, 160}, 3, RADIUS, RADIUS * 1.15f, 0.3, 0.3f, 8);
        ripple2->setLayer(Unit::Layer::Overlay);
        composite->addComponent(std::move(ripple2), startupTime + ACTIVE_TIME - 0.1f, startupTime + ACTIVE_TIME + 0.2f);
    }

    { // hitboxes
        { // barrier
            bullet->addInvincibilityHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), false, player->getPlayerId(), INVINCIBILITY_REFRESH);
            bullet->addInvincibilityHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), false, player->getPlayerId() ^ 1, INVINCIBILITY_REFRESH);
            bullet->addInvincibilityHitbox(startupTime + ACTIVE_TIME - 0.1f, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), false, player->getPlayerId(), INVINCIBILITY_DOWN);
            bullet->addInvincibilityHitbox(startupTime + ACTIVE_TIME - 0.1f, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), false, player->getPlayerId() ^ 1, INVINCIBILITY_DOWN);
            
            bullet->addCleansingHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), CLEANSE_RADIUS));
            bullet->addModifierHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Modifier::MovementModifier,
                                        player->getPlayerId() ^ 1, BARRIER_MOVEMENT_MODIFIER_DURATION, BARRIER_MOVEMENT_MODIFIER_VALUE);
            
            bullet->removeInvincibilityHitboxes(startupTime + ACTIVE_TIME);
            bullet->removeModifierHitboxes(startupTime + ACTIVE_TIME);
            bullet->removeCleansingHitbox(startupTime + ACTIVE_TIME);
        }
        { // timestop
            bullet->addLockHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::MovementLock, player->getPlayerId() ^ 1, TIME_STOP_DURATION);
            bullet->addLockHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::ArrowLock, player->getPlayerId() ^ 1, TIME_STOP_DURATION);
            bullet->addLockHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::BasicLock, player->getPlayerId() ^ 1, TIME_STOP_DURATION);
            bullet->addLockHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::WideLock, player->getPlayerId() ^ 1, TIME_STOP_DURATION);
            bullet->addLockHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::OffensiveLock, player->getPlayerId() ^ 1, TIME_STOP_DURATION);
            bullet->addLockHitbox(startupTime, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::DefensiveLock, player->getPlayerId() ^ 1, TIME_STOP_DURATION);
    
            bullet->removeLockHitboxes(startupTime + 0.1f);
        }
    }

    AudioManager::getInstance().playSound("ArcanistClockWind");
    bullet->addStartupSound("ArcanistClockStop");
    bullet->addStartupSound("ArcanistClockTick");

    player->spawnBullet(std::move(bullet));
}

float ArcanistDefensiveHandler::computeTravelTime(float toTravel) {
    constexpr float t_s = START_GAINING_WHEN;
    constexpr float t_e = STOP_GAINING_WHEN;
    constexpr float Vmax = MAX_SPEED;

    if (toTravel < Unit::EPS) return 0.0f;

    float accelDist = 0.5f * Vmax * (t_e - t_s);

    if (toTravel <= accelDist) {
        return t_s + std::sqrt(2.0f * (t_e - t_s) * toTravel / Vmax);
    } else {
        return t_e + (toTravel - accelDist) / Vmax;
    }
}