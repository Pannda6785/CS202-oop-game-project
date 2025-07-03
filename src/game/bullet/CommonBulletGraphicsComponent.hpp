#ifndef COMMON_BULLET_GRAPHICS_COMPONENT_HPP
#define COMMON_BULLET_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"

/*
    TO DO: If this is ever extensively used (because as of now it's merely demo-purpose)
    + Render the things based on velocity
    + Do flyweight
*/ 

class Texture;
class CommonBullet;

class CommonBulletGraphicsComponent : public GraphicsComponent {
public:
    CommonBulletGraphicsComponent(const CommonBullet* bullet);
    CommonBulletGraphicsComponent(const CommonBullet* bullet, const std::string& texturePath);
    ~CommonBulletGraphicsComponent();

    void render() const override;

private:
    const CommonBullet* bullet;
    Texture* texture;
    bool useTexture;
};

#endif // COMMON_BULLET_GRAPHICS_COMPONENT_HPP