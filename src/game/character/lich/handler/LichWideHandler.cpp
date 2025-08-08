#include "LichWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../LichGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <cmath>
#include <algorithm>

LichWideHandler::LichWideHandler(LichGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics) {}

void LichWideHandler::update(float dt, const InputBufferer* input) {
    comboHold = std::max(0.0f, comboHold - dt);
    if (comboHold < Unit::EPS) {
        step = 0;
    }
}

void LichWideHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Wide) {
        comboHold = 0.0f;
        step = 0;
    }
}

void LichWideHandler::tap(bool isFocusing) {
    graphics->useWide();

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_VALUE);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);

    comboHold = COMBO_HOLD;
    step = (step + 1) % NUM_STEPS;
}

void LichWideHandler::spawnBullet() {
    const float MY_PI = 3.14159265358979323846f;

    Unit::Vec2D center = player->getPosition();
    Unit::Vec2D toTargetDir = player->getTargetPosition() - center;

    // Destroy old Lat Life flowers in the destruction ring
    float outerRadius = RING_RADIUS[2 * step + 1] + 150.0f;
    float innerRadius = (step == 0) ? 0.0f : RING_RADIUS[2 * step] - 30.0f;
    for (auto it = spawnedBullets.begin(); it != spawnedBullets.end();) {
        if (auto bullet = it->lock()) {
            float dist = (bullet->getPosition() - center).magnitude();
            if (dist >= innerRadius && dist <= outerRadius) {
                bullet->makeDone();
                it = spawnedBullets.erase(it);
            } else {
                ++it;
            }
        } else {
            it = spawnedBullets.erase(it);
        }
    }

    // Spawn two new rings
    std::vector<const Texture*> startupTex = {
        TextureManager::instance().getTexture("../assets/sprites/lich/bullet/spr_flo_2_p1_1.png"),
        TextureManager::instance().getTexture("../assets/sprites/lich/bullet/spr_flo_2_p1_3.png"),
    };
    constexpr int FPS = 6;
    const Texture* flowerTex = TextureManager::instance().getTexture("../assets/sprites/lich/bullet/spr_flo_2_p1_2.png");
    constexpr float visibleRatio = 0.5f;

    for (int ringIdx = 2 * step; ringIdx < 2 * step + 2; ++ringIdx) {
        float startup = STARTUP[step];
        float radius = RING_RADIUS[ringIdx];
        float flowerRadius = BULLET_RADIUS[ringIdx];
        int numFlowers = NUM_BULLETS[ringIdx];

        const float resize = 2 * flowerRadius / (visibleRatio * flowerTex->width);

        // Compute the angle to the target for this ring
        float angleToTarget = std::atan2(toTargetDir.y, toTargetDir.x);

        for (int i = 0; i < numFlowers; ++i) {
            float angle = angleToTarget + 2.0f * MY_PI * (i + 0.5f) / numFlowers;
            Unit::Vec2D pos = center + Unit::Vec2D(std::cos(angle), std::sin(angle)) * radius;

            auto bullet = std::make_shared<StraightBullet>(
                player->getPlayerId(),
                std::make_unique<TextureBulletGraphicsComponent>(flowerTex, resize),
                pos,
                Unit::Vec2D{0, 0},
                0.0f,
                LIFETIME
            );

            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addStartup(startupTex, FPS, resize);
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addRotation(-1 / 3.0f);
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0.0f, startup / 3);
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addTint({255, 255, 255, 190});

            bullet->addDamagingHitbox(startup, std::make_unique<CircleHitbox>(pos, flowerRadius));

            player->spawnBullet(bullet);
            spawnedBullets.emplace_back(bullet);
        }
    }
}