#ifndef CHARGE_GRAPHICS_COMPONENT_HPP
#define CHARGE_GRAPHICS_COMPONENT_HPP

#include "../BulletGraphicsComponent.hpp"
#include <array>
#include <vector>
#include <string>

class ChargeGraphicsComponent : public BulletGraphicsComponent {
    std::string TEXTURE_PATH = "../assets/sprites/universal/spr_bullet_warning_0_1.png";
    static constexpr float VISIBLE_RATIO = 1.0f;
    static constexpr float TEXTURE_WIDTH = 1000.0f;

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

private:
    struct Inner {
        std::array<int, 4> color;
        float speed;
        bool loop;
        float radius;
        float timer;
    };

    std::array<int, 4> color;
    float startRadius;
    float endRadius;
    float duration;
    float time = 0.0f;
    float radius;
    bool automatic;

    std::vector<Inner> inners;
};

#endif // CHARGE_GRAPHICS_COMPONENT_HPP