#include "OrichalcumMail.hpp"

#include "../bullet/StraightBullet.hpp"
#include "../bullet/TextureBulletGraphicsComponent.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../../graphics/TextureManager.hpp"

#include "../IBulletSpawner.hpp"
#include "../../Unit.hpp"

#include <cmath>
#include <random>

OrichalcumMail::OrichalcumMail(IBulletSpawner* spawner)
    : Pattern(spawner), timer(0.0f) {}

void OrichalcumMail::init() {
    timer = 0.0f;
}

void OrichalcumMail::update(float dt) {
    timer += dt;

    if (timer > DURATION) return;

    // B1: Downward deterministic pattern
    if (timer >= B1_START_TIME) {
        float t = timer - B1_START_TIME;
        int waveIdx = static_cast<int>(t / B1_FREQUENCY);
        float waveTime = waveIdx * B1_FREQUENCY;
        // Only fire at the start of each wave (edge-triggered)
        if (t - dt < waveTime && t >= waveTime) {
            float startX = 0.0f;
            float endX = Unit::BATTLEFIELD_WIDTH;
            int numBullets = static_cast<int>((endX - startX) / B1_HORIZONTAL_SPACING) + 1;
            float offset = (waveIdx % 2 == 0) ? 0.0f : B1_HORIZONTAL_SPACING / 2.0f;

            for (int i = 0; i < numBullets; ++i) {
                float x = startX + i * B1_HORIZONTAL_SPACING + offset;
                if (x < 0.0f || x > Unit::BATTLEFIELD_WIDTH) continue;
                Unit::Vec2D position = { x, -40.0f };
                Unit::Vec2D velocity = { 0.0f, B1_SPEED };

                const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/hero/bullet/fencer_bullets_0_p1_0000.png");
                constexpr float visibleRatio = 0.25f;
                const float resize = (B1_RADIUS * 2) / (texture->width * visibleRatio);

                auto bullet = std::make_shared<StraightBullet>(
                    OWNER_ID,
                    std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                    position,
                    velocity,
                    B1_SPEED,
                    10000.0f
                );
                bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(position, B1_RADIUS));
                bullet->addDamagingHitbox(0, std::make_unique<CircleHitbox>(position, B1_RADIUS));
                dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addVelocityRotation(true);
                spawner->spawnBullet(std::move(bullet));
            }
        }
    }

    // B2: Outward vertical walls, each wave is randomized offset
    if (timer >= B2_START_TIME) {
        float t = timer - B2_START_TIME;
        int waveIdx = static_cast<int>(t / B2_FREQUENCY);
        float waveTime = waveIdx * B2_FREQUENCY;
        // Only fire at the start of each wave (edge-triggered)
        if (t - dt < waveTime && t >= waveTime) {
            // Random vertical offset for this wave
            static std::mt19937 rng{std::random_device{}()};
            std::uniform_real_distribution<float> dist(0.0f, B2_VERTICAL_SPACING);
            float offset = dist(rng);

            // Compute number of bullets per wall
            int numBullets = static_cast<int>(Unit::BATTLEFIELD_HEIGHT / B2_VERTICAL_SPACING) + 2;

            for (int dir = -1; dir <= 1; dir += 2) { // -1 (left), +1 (right)
                float x = Unit::BATTLEFIELD_WIDTH / 2.0f;
                for (int i = 0; i < numBullets; ++i) {
                    float y = offset + i * B2_VERTICAL_SPACING;
                    if (y < 0.0f || y > Unit::BATTLEFIELD_HEIGHT) continue;
                    Unit::Vec2D position = { x, y };
                    Unit::Vec2D velocity = { dir * B2_SPEED, 0.0f };

                    const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/hero/bullet/spr_fen_0_wh_7_1.png");
                    constexpr float visibleRatio = 2.5f / 6.0f;
                    const float resize = (B2_RADIUS * 2) / (texture->width * visibleRatio);

                    auto bullet = std::make_shared<StraightBullet>(
                        OWNER_ID,
                        std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                        position,
                        velocity,
                        B2_SPEED,
                        10000.0f
                    );
                    bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(position, B2_RADIUS));
                    bullet->addDamagingHitbox(0.2f, std::make_unique<CircleHitbox>(position, B2_RADIUS));
                    dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addVelocityRotation(true);
                    spawner->spawnBullet(std::move(bullet));
                }
            }
        }
    }
}