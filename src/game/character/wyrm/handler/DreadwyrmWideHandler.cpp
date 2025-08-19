#include "DreadwyrmWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"

#include <cmath>

DreadwyrmWideHandler::DreadwyrmWideHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics) {}

void DreadwyrmWideHandler::tap(bool isFocusing) {
    graphics->command(STARTUP_FIRST - 0.050f, 0.200f);
    AudioManager::getInstance().playSound("Attack5");
    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, BASIC_LOCK);
    player->applyLock(Unit::Lock::WideLock, WIDE_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);
}

void DreadwyrmWideHandler::spawnBullet() {
    constexpr float MY_PI = 3.14159265358979323846f;

    Unit::Vec2D center = player->getTargetPosition();
    
    const Texture* bulletTexture = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/spr_drk_0_p1_0.png");
    constexpr float visibleRatio = 0.14f;
    const float resize = (RADIUS * 2) / (bulletTexture->width * visibleRatio);

    constexpr int NUM_GROUPS = 8;
    constexpr int BULLETS_PER_GROUP = 2;

    for (int group = 0; group < NUM_GROUPS; ++group) {
        float baseAngle = 2.0f * MY_PI * group / NUM_GROUPS;
        float time = (group & 1) ? STARTUP_SECOND : STARTUP_FIRST;

        for (int j = 0; j < BULLETS_PER_GROUP; ++j) {
            Unit::Vec2D pos = center + Unit::Vec2D(std::cos(baseAngle), std::sin(baseAngle)) * SPAWN_DISTANCE;
            float angle = baseAngle + MY_PI + (j == 0 ? -1 : 1) * (ANGLE * MY_PI / 180.0f);
            Unit::Vec2D dir = Unit::Vec2D(std::cos(angle), std::sin(angle)).normalized();

            auto bullet = std::make_shared<StraightBullet>(
                player->getPlayerId(),
                std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
                pos,
                dir,
                [time](float t) {
                    if (t > time + SPEED_JERK) return SPEED / 2;
                    if (t > time) return SPEED;
                    return 0.0f;
                },  
                1e9
            );

            bullet->addLifeHitbox(STARTUP_FIRST, std::make_unique<CircleHitbox>(pos, RADIUS));
            bullet->addDamagingHitbox(time, std::make_unique<CircleHitbox>(pos, RADIUS));
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(STARTUP_FIRST * (group & 1), time);
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addVelocityRotation(true);

            player->spawnBullet(std::move(bullet));
        }
    }
}