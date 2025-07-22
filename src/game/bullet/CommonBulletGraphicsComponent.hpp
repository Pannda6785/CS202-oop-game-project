#ifndef COMMON_BULLET_GRAPHICS_COMPONENT_HPP
#define COMMON_BULLET_GRAPHICS_COMPONENT_HPP

#include "BulletGraphicsComponent.hpp"

#include <string>

class Texture;
class Bullet;

class CommonBulletGraphicsComponent : public BulletGraphicsComponent {
public:
    CommonBulletGraphicsComponent(float initialGradient = 0.4f); // not expected to be used outside of prototyping
    CommonBulletGraphicsComponent(std::string texturePath, float texResize, float initialGradient, bool useVelocity = false,
                                    std::string startupTexturePath = "", float startUpTexResize = 1.0f);

    void registerOwner(const Bullet* bullet);
    void render() const override;
    void update(float dt);

private:
    const Bullet* bullet;

    const Texture* texture = nullptr;
    const Texture* startupTexture = nullptr; // if this is not null, this will be rendered instead until damaging hitbox is set
    float texResize = 1.0f; // how much to resize the texture
    float startUpTexResize = 1.0f; // how much to resize the
    float initialGradient = 0.0f; // for this much second after being born, it will linearly become fully opaque
    float gradient = 0.0f;
    bool useVelocity; // if true, the bullet will be rotated to face its velocity vector

};

#endif // COMMON_BULLET_GRAPHICS_COMPONENT_HPP