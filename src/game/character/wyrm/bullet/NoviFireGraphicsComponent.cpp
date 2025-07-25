#include "NoviFireGraphicsComponent.hpp"
#include "NoviFire.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include <raylib.h>

NoviFireGraphicsComponent::NoviFireGraphicsComponent(const NoviFire* bullet)
    : bullet(bullet)
{
    BulletGraphicsComponent::registerOwner(bullet);
    // std::string path = "../assets/sprites/wyrm/bullet/fire.png"; // TODO: update path
    // texture = TextureManager::instance().getTexture(path);
}

void NoviFireGraphicsComponent::update(float dt) {
    timer += dt;
    if (timer >= 1.0f / FLASH_FPS) {
        timer -= 1.0f / FLASH_FPS;
        frame ^= 1;
    }
}

void NoviFireGraphicsComponent::render() const {
    // if (bullet->isStartingUp()) {
    //     DrawTexture(*chargeCircle, bullet->getPosition().x - chargeCircle->width / 2,
    //                 bullet->getPosition().y - chargeCircle->height / 2, WHITE);
    // } else {
    //     DrawTexture(*novi[frame], bullet->getPosition().x - novi[frame]->width / 2,
    //                 bullet->getPosition().y - novi[frame]->height / 2, WHITE);
    // }
    BulletGraphicsComponent::drawHitboxes();
}