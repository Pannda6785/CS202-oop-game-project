#include "RingGraphicsComponent.hpp"
#include <raylib.h>

#include <cmath>

RingGraphicsComponent::RingGraphicsComponent(bool isWide) : isWide(isWide) {
    visible = false;
}

void RingGraphicsComponent::render() const {
    Color orange = {255, 60, 25, 255};
    Color white = WHITE;
    orange.a = white.a = 140;
    float radii[3] = { radius - SPACING, radius, radius + SPACING };
    Color colors[3];

    if (isWide) {
        white.a = 180;
        colors[0] = colors[2] = orange;
        colors[1] = white;
    } else {
        orange.a = 180;
        colors[0] = colors[2] = white;
        colors[1] = orange;
    }

    if (isCasting) {
        // Draw the 3 rings
        for (int i = 0; i < 3; ++i) {
            float inner = radii[i] - THICKNESS / 2;
            float outer = radii[i] + THICKNESS / 2;
            DrawRing({center.x, center.y}, inner, outer, 0.0f, 360.0f, 512, colors[i]);
        }
        if (isWide) {
            drawCircles();
        } else {
            drawDiamonds();
        }
    } else if (time - releaseTime < LINGER) {
        // Draw the rings fading out
        float fade = (time - releaseTime) / LINGER;
        for (int i = 0; i < 3; ++i) {
            float inner = radii[i] - (time - releaseTime) * LINGER_SPEED - THICKNESS / 2;
            float outer = radii[i] - (time - releaseTime) * LINGER_SPEED + THICKNESS / 2;
            Color color = orange;
            color.a = static_cast<unsigned char>(colors[i].a * (1.0f - fade));
            DrawRing({center.x, center.y}, inner, outer, 0.0f, 360.0f, 512, color);
        }
    }
}

void RingGraphicsComponent::update(float dt) {
    time += dt; 
}

void RingGraphicsComponent::onCastStart() {
    time = 0;
    isCasting = true;
}

void RingGraphicsComponent::onCastRelease() {
    releaseTime = time;
    isCasting = false;
}

void RingGraphicsComponent::setRadius(float r) {
    radius = r;
}

void RingGraphicsComponent::setCenter(Unit::Vec2D p) {
    center = p;
}

void RingGraphicsComponent::drawCircles() const {
    // Draw rotating circle markers around the middle ring;
    auto draw = [&](float angleOffset, float gradient) -> void {
        for (int i = 0; i < NUM_CIRCLES; ++i) {
            float angle = (2 * PI * i / NUM_CIRCLES) + angleOffset;
            float x = center.x + radius * cosf(angle);
            float y = center.y + radius * sinf(angle);
            float inner = CIRCLE_RADIUS - CIRCLE_THICKNESS / 2;
            float outer = CIRCLE_RADIUS + CIRCLE_THICKNESS / 2;
            Color color = {255, 60, 25, 255};
            color.a = static_cast<unsigned char>(180 * gradient);
            DrawRing({x, y}, inner, outer, 0.0f, 360.0f, 128, color);
        }
    };
    float angleOffset = time * ROTATE_SPEED * DEG2RAD;
    draw(angleOffset, std::min(1.0f, time / GRADIENT));
    if (time > TIME_FOR_MORE) {
        draw(angleOffset + PI / NUM_CIRCLES, std::min(1.0f, (time - TIME_FOR_MORE) / GRADIENT));
    }
}

void RingGraphicsComponent::drawDiamonds() const {
    float angleOffset = time * ROTATE_SPEED * DEG2RAD;
    for (int i = 0; i < NUM_DIAS; ++i) {
        float angle = (2 * PI * i / NUM_DIAS) + angleOffset;
        Vector2 base = {
            center.x + radius * cosf(angle),
            center.y + radius * sinf(angle)
        };
        Vector2 dir  = { cosf(angle), sinf(angle) };
        Vector2 perp = { -dir.y, dir.x };
        float len = DIAMOND_LENGTH * 0.6;
        float width = DIAMOND_WIDTH * 0.5f;
        float backLen = DIAMOND_LENGTH * 0.4f;
        Vector2 tip    = { base.x + dir.x * len,       base.y + dir.y * len };
        Vector2 tail   = { base.x - dir.x * backLen,   base.y - dir.y * backLen };
        Vector2 left   = { base.x + perp.x * width,    base.y + perp.y * width };
        Vector2 right  = { base.x - perp.x * width,    base.y - perp.y * width };
        Color mainColor = WHITE;
        mainColor.a = static_cast<unsigned char>(200 * std::min(1.0f, time / GRADIENT));
        DrawLineEx(tip, right, DIAMOND_LINE_THICKNESS, mainColor);
        DrawLineEx(right, tail, DIAMOND_LINE_THICKNESS, mainColor);
        DrawLineEx(tail, left, DIAMOND_LINE_THICKNESS, mainColor);
        DrawLineEx(left, tip, DIAMOND_LINE_THICKNESS, mainColor);
    }
}