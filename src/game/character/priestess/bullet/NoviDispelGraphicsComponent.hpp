#ifndef NOVI_DISPEL_GRAPHICS_COMPONENT_HPP
#define NOVI_DISPEL_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class NoviDispel;
class Texture;

class NoviDispelGraphicsComponent : public BulletGraphicsComponent {
    static constexpr float ROTATE_FPS = 6; // rotate degrees X times per second
    static constexpr float FLASH_FPS = 5; // flash X times per second

public:
    explicit NoviDispelGraphicsComponent(const NoviDispel* bullet);
    ~NoviDispelGraphicsComponent() override;

    void render() const override;
    void update(float dt);

private:
    const NoviDispel* bullet;
    Texture* texture = nullptr;

    float rotationTimer = 0.0f;
    float rotation = 0.0f;

};

#endif // NOVI_DISPEL_GRAPHICS_COMPONENT_HPP