#include "DreadFire.hpp"

#include "../../../player/Player.hpp"
#include "../../../IBulletSpawner.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"

#include <cmath>

DreadFire::DreadFire(const Player* player, IBulletSpawner* spawner)
    : Bullet(player->getPlayerId(), std::make_unique<CompositeBulletGraphicsComponent>()),
      player(player),
      spawner(spawner),
      pos(player->getPosition())
{
    const Texture* tex = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/spr_drk_0_p1_1.png");
    const float visibleRatio = 2.95f / 6.0f;
    const float resize = 2 * RADIUS / (tex->width * visibleRatio);
    auto texGraphics = std::make_unique<TextureBulletGraphicsComponent>(tex, resize);
    dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get())->addComponent(std::move(texGraphics));

    dir = player->getArrow().normalized();
    // Project target onto arrow
    Unit::Vec2D target = player->getTargetPosition();
    float projDistance = dir.dot(target - pos);
    float distance = std::max(250.0f, projDistance - EXPLODE_DISTANCE);
    timer = distance / SPEED;

    lifeHitbox = std::make_unique<CircleHitbox>(pos, RADIUS);
    damagingHitbox = std::make_unique<CircleHitbox>(pos, RADIUS);
}

void DreadFire::update(float dt) {
    if (graphics) graphics->update(dt);
    if (exploded) return;
    
    timer -= dt;
    if (timer <= 0.0f) {
        explode();
        exploded = true;
        return;
    }

    if (timer <= 0.25f && !warned) {
        warned = true;
        std::array<int, 4> purple = {118, 11, 186, 240};
        auto rippleGraphics = std::make_unique<RippleGraphicsComponent>(purple, 1, 0, RADIUS * 6, 0.3f, 1, 5);
        dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get())->addComponent(std::move(rippleGraphics));
    }

    pos += getVelocity() * dt;
    if (lifeHitbox) lifeHitbox->setPosition(pos);
    if (damagingHitbox) damagingHitbox->setPosition(pos);
}

void DreadFire::explode() {
    AudioManager::getInstance().playSound("Attack2");
    constexpr float MY_PI = 3.14159265358979323846f;

    // Remove main hitboxes
    lifeHitbox = nullptr;
    damagingHitbox = nullptr;

    // Spawn fragments in a fan pattern centered on dir
    float baseAngle = std::atan2(dir.y, dir.x);
    float halfFan = FAN_ANGLE * 0.5f * MY_PI / 180.0f;
    float angleStep = (FAN_ANGLE * MY_PI / 180.0f) / (NUM_FRAGMENTS - 1);

    const Texture* tex = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/spr_cas_0_p1_3.png");
    const float visibleRatio = 1.92f / 6.0f;
    const float resize = 2 * FRAGMENT_RADIUS / (tex->width * visibleRatio);

    for (int i = 0; i < NUM_FRAGMENTS; ++i) {
        float angle = baseAngle - halfFan + angleStep * i;
        Unit::Vec2D fragDir = Unit::Vec2D(std::cos(angle), std::sin(angle));

        auto frag = std::make_shared<StraightBullet>(
            player->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(tex, resize),
            pos, // explode at current position
            fragDir,
            [](float t) {
                return FRAGMENT_SPEED - FRAGMENT_SPEED_DECREASE * t;
            },
            FRAGMENT_LIFETIME
        );
        frag->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(pos, FRAGMENT_RADIUS));
        frag->addDamagingHitbox(0.0f, std::make_unique<CircleHitbox>(pos, FRAGMENT_RADIUS));
        frag->resize(getSize());
        dynamic_cast<TextureBulletGraphicsComponent*>(frag->getGraphics())->addVelocityRotation(true);
        spawner->spawnBullet(std::move(frag));
    }
}

bool DreadFire::isDone() const {
    return exploded;
}

Unit::Vec2D DreadFire::getPosition() const {
    return pos;
}

Unit::Vec2D DreadFire::getVelocity() const {
    return dir * SPEED;
}