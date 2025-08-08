#include "CeresCurrent.hpp"

#include "../bullet/StraightBullet.hpp"
#include "../bullet/TextureBulletGraphicsComponent.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../../graphics/TextureManager.hpp"
#include "../IBulletSpawner.hpp"
#include "../../Unit.hpp"

#include <random>
#include <cmath>

CeresCurrent::CeresCurrent(IBulletSpawner* spawner)
    : Pattern(spawner), timer(0.0f), b2Wave(0) {}

void CeresCurrent::init() {
    timer = 0.0f;
    b2Wave = 0;
}

void CeresCurrent::update(float dt) {
    const float MY_PI = 3.14159265358979323846f;

    timer += dt;
    if (timer > DURATION) return;

    // --- B1: Random bullets, upper half right->left, lower half left->right ---
    if (timer >= B1_START_TIME) {
        float t = timer - B1_START_TIME;
        int waveIdx = static_cast<int>(t / FREQUENCY);
        float waveTime = waveIdx * FREQUENCY;
        if (t - dt < waveTime && t >= waveTime) {
            static std::mt19937 rng{std::random_device{}()};
            std::uniform_real_distribution<float> radiusDist(B1_MIN_RADIUS, B1_MAX_RADIUS);
            std::uniform_real_distribution<float> angleDist(-ANGLE_SPREAD, ANGLE_SPREAD);
            std::uniform_real_distribution<float> upperY(0.0f, Unit::BATTLEFIELD_HEIGHT / 2.0f);
            std::uniform_real_distribution<float> lowerY(Unit::BATTLEFIELD_HEIGHT / 2.0f, Unit::BATTLEFIELD_HEIGHT);

            const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/caster_bullets_0_p1_0002.png");
            constexpr float visibleRatio = 2.0 / 3.0f;
            
            for (int ite = 0; ite < 2; ite++) {
                // Upper half: right to left
                {
                    float y = upperY(rng);
                    float radius = radiusDist(rng);
                    float angle = angleDist(rng);
                    float angleRad = (180.0f + angle) * MY_PI / 180.0f; // leftward, with spread
                    Unit::Vec2D dir = { std::cos(angleRad), std::sin(angleRad) };
                    Unit::Vec2D pos = { Unit::BATTLEFIELD_WIDTH + radius, y };
    
                    float resize = (radius * 2.0f) / (texture->width * visibleRatio);
    
                    auto bullet = std::make_shared<StraightBullet>(
                        OWNER_ID,
                        std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                        pos,
                        dir,
                        B1_SPEED,
                        10000.0f
                    );
                    bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(pos, radius));
                    bullet->addDamagingHitbox(0, std::make_unique<CircleHitbox>(pos, radius));
                    spawner->spawnBullet(std::move(bullet));
                }
    
                // Lower half: left to right
                {
                    float y = lowerY(rng);
                    float radius = radiusDist(rng);
                    float angle = angleDist(rng);
                    float angleRad = angle * MY_PI / 180.0f; // rightward, with spread
                    Unit::Vec2D dir = { std::cos(angleRad), std::sin(angleRad) };
                    Unit::Vec2D pos = { -radius, y };
    
                    float resize = (radius * 2.0f) / (texture->width * visibleRatio);
    
                    auto bullet = std::make_shared<StraightBullet>(
                        OWNER_ID,
                        std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                        pos,
                        dir,
                        B1_SPEED,
                        10000.0f
                    );
                    bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(pos, radius));
                    bullet->addDamagingHitbox(0, std::make_unique<CircleHitbox>(pos, radius));
                    spawner->spawnBullet(std::move(bullet));
                }
            }
        }
    }

    // --- B2: Deterministic, big bullet falls downward, alternates left/right ---
    if (timer >= B2_START_TIME) {
        float t = timer - B2_START_TIME;
        int waveIdx = static_cast<int>(t / B2_FREQUENCY);
        float waveTime = waveIdx * B2_FREQUENCY;
        if (t - dt < waveTime && t >= waveTime) {
            // Two fixed positions, away from boundary by RADIUS * 0.8
            float margin = B2_RADIUS * 0.8f;
            float leftX = margin;
            float rightX = Unit::BATTLEFIELD_WIDTH - margin;
            float x = (waveIdx % 2 == 0) ? leftX : rightX;
            float y = -B2_RADIUS;

            Unit::Vec2D pos = { x, y };
            Unit::Vec2D dir = { 0.0f, 1.0f };

            const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/caster_bullets_1_p1_0000.png");
            constexpr float visibleRatio = 4.35f / 6.0f;
            float resize = (B2_RADIUS * 2.0f) / (texture->width * visibleRatio);

            auto bullet = std::make_shared<StraightBullet>(
                OWNER_ID,
                std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                pos,
                dir,
                [](float t) { 
                    if (t < B2_STARTUP / 2) return 0.0f;
                    float progress = (t - B2_STARTUP / 2) / (B2_STARTUP / 2);
                    if (progress > 1.0f) progress = 1.0f;
                    return B2_MIN_SPEED + (B2_MAX_SPEED - B2_MIN_SPEED) * std::pow(progress, 1.5f);
                },
                10000.0f
            );
            bullet->addDamagingHitbox(B2_STARTUP, std::make_unique<CircleHitbox>(pos, B2_RADIUS));
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, B2_STARTUP);
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->setLayer(Unit::Layer::Underlay);
            spawner->spawnBullet(std::move(bullet));
        }
    }
}