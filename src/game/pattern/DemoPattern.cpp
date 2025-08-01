#include "DemoPattern.hpp"

#include "../bullet/StraightBullet.hpp"
#include "../bullet/TextureBulletGraphicsComponent.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../../graphics/TextureManager.hpp"

#include "../IBulletSpawner.hpp"
#include "../../Unit.hpp"

#include <cmath> // for std::fmod

DemoPattern::DemoPattern(IBulletSpawner* spawner)
    : Pattern(spawner) {}

void DemoPattern::init() {
    // Initialization logic if needed
    timer = 0.0f; // Reset timer at the start
}

void DemoPattern::update(float dt) {
    timer += dt;

    // Reset wave timer every WAVE_INTERVAL
    if (timer >= WAVE_INTERVAL) {
        timer = std::fmod(timer, WAVE_INTERVAL); // preserve leftover time
    }

    // Determine if we are in an active barrage interval
    float barrageWindow = NUM_BARRAGES * BARRAGE_INTERVAL;
    if (timer > barrageWindow) return;

    // Fire only on specific barrage timestamps
    int barrageIndex = static_cast<int>(timer / BARRAGE_INTERVAL);
    float barrageTime = barrageIndex * BARRAGE_INTERVAL;

    // Fire only once per barrage (edge-triggered)
    if (timer - dt < barrageTime && timer >= barrageTime) {
        float endX = Unit::BATTLEFIELD_WIDTH;
        float startX = 0.0f;
        float step = (endX - startX) / (NUM_BULLETS - 1);
        if (barrageIndex % 2 == 0) {
            startX = -step / 2.0f;
        }

        for (int i = 0; i < NUM_BULLETS; ++i) {
            Unit::Vec2D position = { startX + i * step, -40.0f };
            Unit::Vec2D velocity = { 0.0f, BULLET_SPEED };

            const Texture* texture = TextureManager::instance().getTexture(TEXTURE_PATH);
            const float resize = (BULLET_RADIUS * 2.0f) / (TEXTURE_WIDTH * VISIBLE_RATIO);

            auto bullet = std::make_unique<StraightBullet>(
                OWNER_ID,
                std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                position,
                velocity,
                BULLET_SPEED,
                BULLET_LIFESPAN
            );
            bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(position, BULLET_RADIUS));
            bullet->addDamagingHitbox(BULLET_STARTUP, std::make_unique<CircleHitbox>(position, BULLET_RADIUS));

            spawner->spawnBullet(std::move(bullet));
        }
    }
}
