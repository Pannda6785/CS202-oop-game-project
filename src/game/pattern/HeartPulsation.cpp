#include "HeartPulsation.hpp"
#include "../IBulletSpawner.hpp"
#include "../../graphics/TextureManager.hpp"
#include "../bullet/StraightBullet.hpp"
#include "../bullet/TextureBulletGraphicsComponent.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../../Unit.hpp"
#include <cmath>

HeartPulsation::HeartPulsation(IBulletSpawner* spawner)
    : Pattern(spawner), timer(0.0f) {}

void HeartPulsation::init() {
    timer = 0.0f;
}

void HeartPulsation::update(float dt) {
    timer += dt;
    if (timer > FREQUENCY) {
        timer -= FREQUENCY;
        Unit::Vec2D center = {Unit::BATTLEFIELD_WIDTH / 2.0f, Unit::BATTLEFIELD_HEIGHT / 2.0f};
        const Texture* texture = TextureManager::instance().getTexture("../assets/sprites/redhood/bullet/thf_bullet_0_p1_0004.png");
        constexpr float visibleRatio = 0.475f;
        float resize = (BULLET_RADIUS * 2.0f) / (texture->width * visibleRatio);
        float baseAngle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159265358979323846f;
        for (int i = 0; i < NUM_BULLETS; ++i) {
            float angle = baseAngle + 2.0f * 3.14159265358979323846f * i / NUM_BULLETS;
            Unit::Vec2D dir = {std::cos(angle), std::sin(angle)};
            auto bullet = std::make_shared<StraightBullet>(OWNER_ID,
                std::make_unique<TextureBulletGraphicsComponent>(texture, resize),
                center,
                dir,
                [](float t) {
                    if (t < STARTUP) return BULLET_DORMANT_SPEED;
                    if (t > STARTUP + TIME_TO_REACH_FINAL) return BULLET_SPEED_FINAL;
                    return (t - STARTUP) / TIME_TO_REACH_FINAL * (BULLET_SPEED_FINAL - BULLET_SPEED_INIT) + BULLET_SPEED_INIT;
                },
                1e9f
            );
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, STARTUP);
            bullet->addLifeHitbox(STARTUP / 2, std::make_unique<CircleHitbox>(center, BULLET_RADIUS));
            bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(center, BULLET_RADIUS));
            spawner->spawnBullet(bullet);
        }
    }
}
