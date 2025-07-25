#ifndef NOVI_FIRE_GRAPHICS_COMPONENT_HPP
#define NOVI_FIRE_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class NoviFire;
class Texture;

class NoviFireGraphicsComponent : public BulletGraphicsComponent {
    static constexpr float FLASH_FPS = 3;

public:
    explicit NoviFireGraphicsComponent(const NoviFire* bullet);

    void render() const override;
    void update(float dt);

private:
    const NoviFire* bullet;
    const Texture* chargeCircle;
    const Texture* novi[2];

    int frame = 0;
    float timer;
    
};

#endif // NOVI_FIRE_GRAPHICS_COMPONENT_HPP