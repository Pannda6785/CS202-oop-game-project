#ifndef STUN_WAVE_GRAPHICS_COMPONENT_HPP
#define STUN_WAVE_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class Bullet;
class Texture;

class StunWaveGraphicsComponent : public BulletGraphicsComponent {
    static constexpr float FLASH_FPS = 8;

public:
    explicit StunWaveGraphicsComponent(const Bullet* bullet, float baseRadius, float startup, float bloomTime, float debloom);

    void render() const override;
    void update(float dt);

private:
    const Texture* chargeCircle;
    const Texture* stun[2];

    float startup, bloomTime, baseRadius, debloom;
    int frame = 0;
    float timer;

    float chargeVisibleRatio = 1.0f;
    float stunVisibleRatio = 4.278f / 6.0f;
};

#endif // STUN_WAVE_GRAPHICS_COMPONENT_HPP