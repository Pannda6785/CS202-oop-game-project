#include "Whirlpool.hpp"

#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/AuraGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"

Whirlpool::Whirlpool(const Player* player)
    : Bullet(player->getPlayerId(), std::make_unique<CompositeBulletGraphicsComponent>()), 
    player(player), pos(player->getPosition()), dir(player->getArrow()), 
    timer(0.0f), isStartedUp(false), isDetonating(false), timeDetonated(0.0f), initialSize(getSize())
{
    auto texture = TextureManager::instance().getTexture("../assets/sprites/depth/bullet/hydra_bullets_0_p1_0002.png");
    const float visibleRatio = 4.7f / 6.0f;
    auto textureGraphics = std::make_unique<TextureBulletGraphicsComponent>(texture, 2 * BASE_RADIUS / (texture->width * visibleRatio));
    textureGraphicsRef = textureGraphics.get();
    textureGraphics->addFadein(0, 0.1f);
    textureGraphics->addTint({255, 255, 255, 230});
    textureGraphics->setLayer(Unit::Layer::Underlay + 2);

    std::array<int, 4> color = player->getSignatureColor(); color[3] = 150;
    auto rippleGraphics = std::make_unique<RippleGraphicsComponent>(color, 3, BASE_RADIUS * 1.5f, 0, STARTUP, 0.4f, 16.0f);
    rippleGraphics->setLayer(Unit::Layer::Underlay + 1);
    auto auraGraphics = std::make_unique<AuraGraphicsComponent>(std::array<int, 4>{0, 0, 0, 200}, BASE_RADIUS * 1.3, BASE_RADIUS * 0.9f, STARTUP / 2);
    auraGraphics->setLayer(Unit::Layer::Underlay + 0);

    auto* composite = dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get());
    composite->addComponent(std::move(textureGraphics), STARTUP - 0.1f, 1e9);
    composite->addComponent(std::move(rippleGraphics), 0, STARTUP);
    composite->addComponent(std::move(auraGraphics), 0, STARTUP / 2);
}

void Whirlpool::update(float dt) {
    timer += dt;
    graphics->update(dt);

    if (!isStartedUp && timer >= STARTUP) {
        isStartedUp = true;
        damagingHitbox = std::make_unique<CircleHitbox>(pos, BASE_RADIUS * initialSize);
    }
    if (!isStartedUp) return;

    if (!isDetonating) { // Moves forward and expands
        pos += dir * SPEED * dt;
        float newRadius = BASE_RADIUS + RADIUS_INCREASE * (timer - STARTUP);
        float scale = newRadius / BASE_RADIUS;
        resize(scale * initialSize / getSize());
    } else {
        float detonationElapsed = timer - timeDetonated;
        if (detonationElapsed < EXPLODE_DELAY) { // Deflect and slows down bullet until EXPLODE_DELAY
            float speedFactor = 1.0f - (detonationElapsed / EXPLODE_DELAY);
            Unit::Vec2D deflectDir = (pos - deflectedSource).normalized();
            pos += deflectDir * SPEED * speedFactor * dt;
            float lastRadius = BASE_RADIUS + RADIUS_INCREASE * (timeDetonated - STARTUP);
            float scale = lastRadius / BASE_RADIUS;
            resize(scale * initialSize / getSize());
        } else if (detonationElapsed < EXPLODE_DELAY + EXPLODE_DURATION) { // Expands radius to double over EXPLODE_DURATION
            float lastRadius = BASE_RADIUS + RADIUS_INCREASE * (timeDetonated - STARTUP);
            float expandRatio = (detonationElapsed - EXPLODE_DELAY) / EXPLODE_DURATION;
            float expandedRadius = lastRadius * (1.0f + expandRatio);
            float scale = expandedRadius / BASE_RADIUS;
            resize(scale * initialSize / getSize());
        } else if (detonationElapsed < EXPLODE_DELAY + EXPLODE_DURATION + LIFETIME) { // Hold at full expanded radius
        } else if (damagingHitbox) { // de-startup
            damagingHitbox = nullptr;
        }
    }
    if (damagingHitbox) {
        damagingHitbox->setPosition(pos);
    }
}

bool Whirlpool::isDone() const {
    // Done if detonation finished and LIFETIME elapsed
    if (isDetonating) {
        float detonationElapsed = timer - timeDetonated;
        if (detonationElapsed > EXPLODE_DELAY + EXPLODE_DURATION + LIFETIME + 0.2f) // 0.2 fade out
            return true;
    }
    // Or if bullet moves 2000 units away from battlefield
    float margin = 2000.0f;
    if (pos.x < -margin || pos.x > Unit::BATTLEFIELD_WIDTH + margin ||
        pos.y < -margin || pos.y > Unit::BATTLEFIELD_HEIGHT + margin)
        return true;

    return false;
}

void Whirlpool::detonate() {
    if (!isStartedUp) {
        std::cerr << "warning: Whirlpool::detonate called before startup!??" << std::endl;
        return;
    }
    isDetonating = true;
    timeDetonated = timer;
    deflectedSource = player->getPosition();

    std::array<int, 4> color = player->getSignatureColor(); color[3] = 150;
    auto rippleGraphics = std::make_unique<RippleGraphicsComponent>(color, 3, BASE_RADIUS * 1.3f, 0, STARTUP, 0.4f, 16.0f);
    auto auraGraphics = std::make_unique<AuraGraphicsComponent>(std::array<int, 4>{0, 0, 0, 200}, BASE_RADIUS * 0.9f, BASE_RADIUS / 2, STARTUP / 2);
    rippleGraphics->setLayer(Unit::Layer::Underlay + 1);
    auraGraphics->setLayer(Unit::Layer::Underlay + 0);
    auto* composite = dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get());
    composite->addComponent(std::move(rippleGraphics), timer, timer + STARTUP + 0.1f);
    composite->addComponent(std::move(auraGraphics), timer, timer + STARTUP);

    if (textureGraphicsRef) {
        float localTimer = timer - STARTUP + 0.1f;
        textureGraphicsRef->addFadeout(localTimer + LIFETIME, localTimer + LIFETIME + 0.2f);
    } else {
        std::cerr << "warning: Whirlpool::detonate called but textureGraphicsRef is null?!" << std::endl;
        return;
    }
}

Unit::Vec2D Whirlpool::getPosition() const {
    return pos;
}