#ifndef WORLD_BACKGROUND_HPP
#define WORLD_BACKGROUND_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include "../../Unit.hpp"     // for BATTLEFIELD_WIDTH / HEIGHT / BOUNDARY_PADDING
#include <vector>
#include <raylib.h>
#include <random>

class WorldBackground : public GraphicsComponent {
public:
    explicit WorldBackground(int dotCount = 100);
    ~WorldBackground() override = default;

    void update(float dt);
    void render() const override;

private:
    struct Dot {
        Vector2 position;
        float speed;
        float radius;
    };

    std::vector<Dot> dots;

    Color backgroundColor = { 40, 0, 0, 255 };     // very dark red
    Color dotColor        = { 255, 40, 40, 200 };  // bright red
    Color boundaryColor   = { 255, 0, 0, 255 };    // solid bright red

    void drawBackground() const;
    void drawBoundaryLines() const;
    void drawDots() const;

    void resetDot(Dot& dot) const;
};

#endif // WORLD_BACKGROUND_HPP
