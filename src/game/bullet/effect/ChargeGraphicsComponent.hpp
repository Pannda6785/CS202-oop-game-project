#ifndef CHARGE_GRAPHICS_COMPONENT_HPP
#define CHARGE_GRAPHICS_COMPONENT_HPP

#include "../BulletGraphicsComponent.hpp"
#include <array>
#include <vector>
#include <string>

class ChargeGraphicsComponent : public BulletGraphicsComponent {
public:
    // Automatic mode: radius animates from startRadius to endRadius over duration
    ChargeGraphicsComponent(std::array<int, 4> color, float startRadius, float endRadius, float duration);

    // Manual mode: radius set to 0, expects setRadius() to be called
    ChargeGraphicsComponent(std::array<int, 4> color);

    void setRadius(float r);

    // Add an inner texture that shrinks from outer radius to 0 at given speed, optionally looping
    void addInner(std::array<int, 4> color, float speed, bool loop);

    void update(float dt) override;
    void render() const override;
    void reset();

private:
    struct Inner {
        std::array<int, 4> color;
        float speed;
        bool loop;
        float radius;
        float timer;
    };

    std::array<int, 4> color;
    float startRadius = 0.0f;
    float endRadius;
    float duration;
    float radius;
    bool automatic;

    float time = 0.0f;

    std::vector<Inner> inners;
};

#endif // CHARGE_GRAPHICS_COMPONENT_HPP