#ifndef RING_GRAPHICS_COMPONENT_HPP
#define RING_GRAPHICS_COMPONENT_HPP

#include "../../../bullet/BulletGraphicsComponent.hpp"

class PriestessWideHandler;

class RingGraphicsComponent : public BulletGraphicsComponent {
    // for ring
    static constexpr float THICKNESS = 6.5f;
    static constexpr float SPACING = 25.0f;
    static constexpr float LINGER = 0.24f;
    static constexpr float LINGER_SPEED = 350.0f;
    static constexpr float ROTATE_SPEED = 70.0f; // degrees per second

    // for wide
    static constexpr float CIRCLE_RADIUS = 45.0f;
    static constexpr float CIRCLE_THICKNESS = 8.0f;
    static constexpr int NUM_CIRCLES = 12;
    static constexpr float TIME_FOR_MORE = 0.35f; // how long until additional circle fill up
    static constexpr float GRADIENT = 0.15f; // for when circle comes up

    // for offensive
    static constexpr int NUM_DIAS = 10;
    static constexpr float DIAMOND_LENGTH = 125.0f;
    static constexpr float DIAMOND_WIDTH = 110.0f;
    static constexpr float DIAMOND_LINE_THICKNESS = 8.0f;

public:
    RingGraphicsComponent(bool isWide);
    ~RingGraphicsComponent() override = default;

    void render() const override;
    void update(float dt);
    void onCastStart();
    void onCastRelease();

    void setRadius(float r);
    void setCenter(Unit::Vec2D p);

private:
    bool isWide;
    float time = 0;
    float releaseTime;
    bool isCasting = false;

    float radius = 0;
    Unit::Vec2D center;

    void drawCircles() const;
    void drawDiamonds() const;

};

#endif // RING_GRAPHICS_COMPONENT_HPP