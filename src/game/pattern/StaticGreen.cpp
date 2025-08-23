#include "StaticGreen.hpp"
#include "../../graphics/TextureManager.hpp"
#include "../bullet/StraightBullet.hpp"
#include "../bullet/TextureBulletGraphicsComponent.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../IBulletSpawner.hpp"
#include "../../Unit.hpp"
#include "../IWorldView.hpp"
#include "../player/Player.hpp"
#include <random>
#include <vector>

StaticGreen::StaticGreen(IBulletSpawner* spawner, const IWorldView* worldView)
    : Pattern(spawner), worldView(worldView), timer(0.0f) {}

void StaticGreen::init() {
    timer = 0.0f;
    b1timer = 0.0f;
    bullets.clear();
}

void StaticGreen::update(float dt) {
    timer += dt;
    if (timer < B1_START_TIME) return;
    static std::mt19937 rng{std::random_device{}()};
    // B1: spawn at random location in lower half every B1_FREQUENCY
    b1timer += dt;
    if (b1timer > B1_FREQUENCY) {
        b1timer -= B1_FREQUENCY;
        auto players = worldView->getPlayers();
        if (!players.empty()) {
            int targetIdx = rng() % players.size();
            const Player* target = players[targetIdx];
            Unit::Vec2D playerPos = target->getPosition();
            std::uniform_real_distribution<float> xDist(playerPos.x - B1_SPAWN_RANGE / 2.0f, playerPos.x + B1_SPAWN_RANGE / 2.0f);
            std::uniform_real_distribution<float> yDist(Unit::BATTLEFIELD_HEIGHT / 2.0f, Unit::BATTLEFIELD_HEIGHT);
            float x = std::max(0.0f, std::min(Unit::BATTLEFIELD_WIDTH, xDist(rng)));
            float y = yDist(rng);
            Unit::Vec2D pos = {x, y};
            std::vector<const Texture*> texture = {
                TextureManager::instance().getTexture("../assets/sprites/stormbeast/bullet/spr_bst_1_p1_0.png"),
                TextureManager::instance().getTexture("../assets/sprites/stormbeast/bullet/spr_bst_1_p1_1.png"),
                TextureManager::instance().getTexture("../assets/sprites/stormbeast/bullet/spr_bst_1_p1_2.png")
            };
            constexpr float visibleRatio = 0.475f;
            float radius = B1_RADIUS;
            float resize = (radius * 2.0f) / (texture[0]->width * visibleRatio);
            auto bullet = std::make_shared<StraightBullet>(
                OWNER_ID,
                std::make_unique<TextureBulletGraphicsComponent>(texture, 8, resize),
                pos,
                Unit::Vec2D{0, -1},
                B1_SPEED,
                1e9
            );
            bullet->addDamagingHitbox(B1_STARTUP, std::make_unique<CircleHitbox>(pos, radius));
            static_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, B1_STARTUP);
            static_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->setLayer(Unit::Layer::Underlay);
            spawner->spawnBullet(bullet);
            bullets.push_back({bullet, timer});
        }
    }
    // For each B1, handle B2 spawn logic
    for (auto& pair : bullets) {
        auto b1ptr = pair.first.lock();
        if (!b1ptr) continue;
        Unit::Vec2D b1pos = b1ptr->getPosition();
        float b1spawnTime = pair.second;
        float localTime = timer - b1spawnTime;
        float ttt = fmod(localTime, B2_FREQUENCY);
        if (ttt + dt >= B2_FREQUENCY) {
            auto players = worldView->getPlayers();
            if (players.empty()) continue;
            int targetIdx = rng() % players.size();
            const Player* target = players[targetIdx];
            Unit::Vec2D targetPos = target->getPosition();
            Unit::Vec2D dir = (targetPos - b1pos).normalized();
            const Texture* tex = TextureManager::instance().getTexture("../assets/sprites/stormbeast/bullet/beast_bullets_0_p1_0002.png");
            constexpr float visibleRatio = 0.25f;
            const float resize = (B2_RADIUS * 2.0f) / (tex->width * visibleRatio);
            
            // Warning bullet (no hitbox)
            auto warnBullet = std::make_shared<StraightBullet>(OWNER_ID,
                std::make_unique<TextureBulletGraphicsComponent>(tex, resize),
                b1pos,
                dir,
                B2_SPEED,
                1e9
            );
            static_cast<TextureBulletGraphicsComponent*>(warnBullet->getGraphics())->addTint({255, 255, 255, 70});
            static_cast<TextureBulletGraphicsComponent*>(warnBullet->getGraphics())->addVelocityRotation(true);
            spawner->spawnBullet(warnBullet);

            // Real bullet after delay
            auto realBullet = std::make_shared<StraightBullet>(OWNER_ID,
                std::make_unique<TextureBulletGraphicsComponent>(tex, resize),
                b1pos,
                dir,
                [](float t) -> float {
                    if (t < B2_WARNING_DELAY) return 0.0f;
                    return B2_SPEED;
                },
                1e9
            );
            realBullet->addDamagingHitbox(B2_WARNING_DELAY, std::make_unique<CircleHitbox>(b1pos, B2_RADIUS));
            realBullet->addLifeHitbox(B2_WARNING_DELAY, std::make_unique<CircleHitbox>(b1pos, B2_RADIUS));
            static_cast<TextureBulletGraphicsComponent*>(realBullet->getGraphics())->addFadein(B2_WARNING_DELAY, B2_WARNING_DELAY + 0.01f);
            static_cast<TextureBulletGraphicsComponent*>(realBullet->getGraphics())->addVelocityRotation(true);
            static_cast<TextureBulletGraphicsComponent*>(realBullet->getGraphics())->setLayer(Unit::Layer::Underlay - 1);
            spawner->spawnBullet(realBullet);
        }
    }
}
