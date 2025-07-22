#ifndef SUNBURST_GRAPHICS_COMPONENT_HPP
#define SUNBURST_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class Texture;
class Sunburst;

class SunburstGraphicsComponent : public BulletGraphicsComponent {
    static constexpr float INITIAL_GRADIENT = 0.6f;
    static constexpr float ROTATE_FPS = 6; // rotate degrees X times per second

public:
    explicit SunburstGraphicsComponent(const Sunburst* bullet);

    void render() const override;
    void update(float dt);

private:
    const Sunburst* bullet;

    const Texture* inactiveTexture;
    const Texture* activeTexture;

    float gradient = 0.0f;
    float rotationTimer = 0.0f;
    float rotation = 0.0f;
    bool flipped = false;
};

#endif // SUNBURST_GRAPHICS_COMPONENT_HPP
