#ifndef NOVI_DISPEL_GRAPHICS_COMPONENT_HPP
#define NOVI_DISPEL_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class Bullet;
class Texture;

class NoviDispelGraphicsComponent : public BulletGraphicsComponent {
    static constexpr float ROTATE_FPS = 6; // rotate degrees X times per second
    static constexpr float FLASH_FPS = 5; // flash X times per second

    static constexpr int RIPPLE_COUNT = 3;
    static constexpr float RIPPLE_DURATION = 0.4f; // seconds
    static constexpr float RIPPLE_WIDTH = 7.0f;
    static constexpr float RIPPLE_SPREAD = 50.0f;  // how far ripples expand beyond the texture edge

public:
    NoviDispelGraphicsComponent(const Bullet* bullet);

    void render() const override;
    void update(float dt) override;

private:
    const Texture* texture = nullptr;

    float rotationTimer = 0.0f;
    float rotation = 0.0f;
    
    float rippleTimer = 0.0f;
    bool rippleActive = true;

};

#endif // NOVI_DISPEL_GRAPHICS_COMPONENT_HPP