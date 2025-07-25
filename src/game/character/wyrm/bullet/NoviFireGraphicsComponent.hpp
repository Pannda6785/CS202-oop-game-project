#ifndef NOVI_FIRE_GRAPHICS_COMPONENT_HPP
#define NOVI_FIRE_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class Bullet;
class Texture;

class NoviFireGraphicsComponent : public BulletGraphicsComponent {
    static constexpr float FLASH_FPS = 8;

public:
    explicit NoviFireGraphicsComponent(const Bullet* bullet, float baseRadius, float startup, float bloomTime, float debloom);

    void render() const override;
    void update(float dt);

private:
    const Texture* chargeCircle;
    const Texture* novi[2]; 

    float startup, bloomTime, baseRadius, debloom;
    int frame = 0;
    float timer;
    
    float chargeVisibleRatio = 1.0f; 
    float noviVisibleRatio = 4.278f / 6.0f;

};

#endif // NOVI_FIRE_GRAPHICS_COMPONENT_HPP