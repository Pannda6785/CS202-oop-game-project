#include "DeathToll.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"

#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

DeathToll::DeathToll(const Player* player)
    : Bullet(player->getPlayerId(), std::make_unique<CompositeBulletGraphicsComponent>()),
      player(player)
{
    std::vector<const Texture*> inactive = {
        TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/spr_cas_d_p1_0.png"),  
        TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/spr_cas_d_p1_1.png")
    };
    const Texture* active = TextureManager::instance().getTexture("../assets/sprites/arcanist/bullet/spr_cas_3_p1_1.png");
    const float visibleRatio = 4.7f / 6.0f;
    const float resize = 2 * RADIUS / (active->width * visibleRatio);

    auto texGraphics = std::make_unique<TextureBulletGraphicsComponent>(active, resize);
    texGraphics->addStartup(inactive, 3, resize);
    texGraphics->addFadein(0.0f, 0.3f);
    texGraphics->addFadeout(STARTUP + DURATION, STARTUP + DURATION + FADEOUT);
    texGraphics->setLayer(Unit::Layer::Underlay);

    dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get())->addComponent(std::move(texGraphics));

    pos = (player->getPosition() + player->getTargetPosition()) / 2;
}

void DeathToll::update(float dt) {
    time += dt;

    if (time + 0.5f > STARTUP && !warned) {
        warned = true;
        std::array<int, 4> red = {255, 112, 62, 220};
        auto ripple = std::make_unique<RippleGraphicsComponent>(red, 2, RADIUS * getSize() * 0.7f, RADIUS * getSize() * 1.2f, 0.7f, 0.5f, 11);
        dynamic_cast<CompositeBulletGraphicsComponent*>(graphics.get())->addComponent(std::move(ripple));
    }

    if (time > STARTUP && !active) {
        damagingHitbox = std::make_unique<CircleHitbox>(pos, RADIUS * getSize());
        active = true;
    }

    if (active) {
        pos += getVelocity() * dt;
        if (damagingHitbox) damagingHitbox->setPosition(pos);
    }

    graphics->update(dt);
}

bool DeathToll::isDone() const {
    return time > STARTUP + DURATION + FADEOUT;
}

Unit::Vec2D DeathToll::getPosition() const {
    return pos;
}

Unit::Vec2D DeathToll::getVelocity() const {
    if (active) {
        Unit::Vec2D toTarget = player->getTargetPosition() - pos;
        return toTarget.normalized() * SPEED;
    }
    return Unit::Vec2D(0, 0);
}