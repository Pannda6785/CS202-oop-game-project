#include "CombatFeedbackFlash.hpp"
#include <raylib.h>
#include "../../../Unit.hpp"

CombatFeedbackFlash::CombatFeedbackFlash(float duration)
    : duration(duration), timer(duration)
{
    setLayer(Unit::Layer::Foreground);       
    setVisible(true);
    addTag("screen_flash");
}

void CombatFeedbackFlash::update(float dt) {
    if (!isVisible()) return;

    timer -= dt;
    if (timer <= 0.0f) {
        setVisible(false);
    }
}

void CombatFeedbackFlash::render() const {
    if (!isVisible()) return;

    float alpha = timer / duration * 0.3;
    if (alpha < 0.0f) alpha = 0.0f;

    Color tint = WHITE;
    tint.a = static_cast<unsigned char>(255 * alpha);

    // Draw bigger than the screen to cover all
    Vector2 size = {
        static_cast<float>(GetScreenWidth()) * 1.2f,
        static_cast<float>(GetScreenHeight()) * 1.2f
    };
    Vector2 pos = { -0.1f * size.x, -0.1f * size.y };

    DrawRectangleV(pos, size, tint);
}

bool CombatFeedbackFlash::isAlive() const {
    return isVisible();
}
