#include "WorldBackground.hpp"

WorldBackground::WorldBackground(int dotCount) {
    addTag("world_object");
    setLayer(Unit::Layer::Background);

    dots.reserve(dotCount);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(Unit::BATTLEFIELD_WIDTH));
    std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(Unit::BATTLEFIELD_HEIGHT));
    std::uniform_real_distribution<float> speedDist(18.0f, 45.0f);   // slow upward drift
    std::uniform_real_distribution<float> radiusDist(1.5f, 3.5f);

    for (int i = 0; i < dotCount; i++) {
        Dot d;
        d.position = { xDist(gen), yDist(gen) };
        d.speed = speedDist(gen);
        d.radius = radiusDist(gen);
        dots.push_back(d);
    }
}

void WorldBackground::update(float dt) {
    for (auto& d : dots) {
        d.position.y -= d.speed * dt;  // upward drift
        if (d.position.y + d.radius < 0) {
            resetDot(d);
        }
    }
}

void WorldBackground::render() const {
    drawBackground();
    drawBoundaryLines();
    drawDots();
}

void WorldBackground::drawBackground() const {
    DrawRectangle(
        0,
        0,
        Unit::BATTLEFIELD_WIDTH,
        Unit::BATTLEFIELD_HEIGHT,
        backgroundColor
    );
}

void WorldBackground::drawBoundaryLines() const {
    float pad = Unit::BOUNDARY_PADDING;

    // Inner rectangle (playable boundary)
    float left   = pad;
    float right  = Unit::BATTLEFIELD_WIDTH  - pad;
    float top    = pad;
    float bottom = Unit::BATTLEFIELD_HEIGHT - pad;

    float thickness = 3.0f; // adjust as needed
    Color color = boundaryColor;
    color.a = 80;

    DrawLineEx({ left, top },     { right, top },    thickness, color);
    DrawLineEx({ right, top },    { right, bottom }, thickness, color);
    DrawLineEx({ right, bottom }, { left, bottom },  thickness, color);
    DrawLineEx({ left, bottom },  { left, top },     thickness, color);
}

void WorldBackground::drawDots() const {
    for (const auto& d : dots) {
        DrawCircleV(d.position, d.radius, dotColor);
    }
}

void WorldBackground::resetDot(Dot& d) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(Unit::BATTLEFIELD_WIDTH));
    std::uniform_real_distribution<float> speedDist(5.0f, 20.0f);
    std::uniform_real_distribution<float> radiusDist(1.5f, 3.5f);

    d.position.x = xDist(gen);
    d.position.y = static_cast<float>(Unit::BATTLEFIELD_HEIGHT) + d.radius; // just below battlefield
    d.speed = speedDist(gen);
    d.radius = radiusDist(gen);
}