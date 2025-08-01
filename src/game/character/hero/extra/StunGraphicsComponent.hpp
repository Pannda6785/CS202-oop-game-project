#ifndef STUN_GRAPHICS_COMPONENT_HPP
#define STUN_GRAPHICS_COMPONENT_HPP

#include "../../../../game/bullet/BulletGraphicsComponent.hpp"
#include "../../../../Unit.hpp"
#include <array>

class IWorldView;

class StunGraphicsComponent : public BulletGraphicsComponent {
    // draw three rings around the 'pos', every TIME seconds the inner most ring is gone. also draw a floating up text "stunned!!" 
    static constexpr float THICKNESS = 16;
    static constexpr float SPACING = 24;
    static constexpr float FIRST_RADIUS = 95;
    static constexpr float TIME = 0.160f;
    static constexpr float FLOAT_SPEED = 160;

public:
    StunGraphicsComponent(std::array<int, 4> color, const IWorldView* world);

    void update(float dt);
    void render() const override;

private:
    const IWorldView* world = nullptr;
    Unit::Vec2D pos;
    std::array<int, 4> color;
    bool active = false;
    float timer;
};

#endif // STUN_GRAPHICS_COMPONENT_HPP