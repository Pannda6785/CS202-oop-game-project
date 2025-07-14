#ifndef COMMON_BULLET_GRAPHICS_COMPONENT_HPP
#define COMMON_BULLET_GRAPHICS_COMPONENT_HPP

#include "BulletGraphicsComponent.hpp"

#include <string>

class Texture;
class Bullet;

class CommonBulletGraphicsComponent : public BulletGraphicsComponent {
public:
    CommonBulletGraphicsComponent(const Bullet* bullet, float initialGradient = 0.4f); // not expected to be used outside of prototyping
    CommonBulletGraphicsComponent(const Bullet* bullet, std::string texturePath, float initialGradient, std::string startupTexturePath = "");
    ~CommonBulletGraphicsComponent();

    void render() const override;
    void update(float dt);

private:
    const Bullet* bullet;

    Texture* texture = nullptr;
    Texture* startupTexture = nullptr; // if this is not null, this will be rendered instead until damaging hitbox is set
    float initialGradient = 0.0f; // for this much second after being born, it will linearly become fully opaque

    float gradient = 0.0f;

};

#endif // COMMON_BULLET_GRAPHICS_COMPONENT_HPP