#ifndef DECORATE_GRAPHICS_COMPONENT_HPP
#define DECORATE_GRAPHICS_COMPONENT_HPP

#include "../BulletGraphicsComponent.hpp"
#include <vector>
#include <array>

class DecorateGraphicsComponent : public BulletGraphicsComponent {
public:
    DecorateGraphicsComponent();

    void addCircle(std::array<int, 4> color, float radius);
    void addRing(std::array<int, 4> color, float radius, float thickness);

    void render() const override;

private:
    struct Circle {
        std::array<int, 4> color;
        float radius;
    };
    struct Ring {
        std::array<int, 4> color;
        float radius;
        float thickness;
    };

    std::vector<Circle> circles;
    std::vector<Ring> rings;
};

#endif //