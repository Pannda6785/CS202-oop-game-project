#include "StunGraphicsComponent.hpp"
#include "../../../bullet/Bullet.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../IWorldView.hpp"
#include "../../../player/Player.hpp"

#include <raylib.h>
#include <cmath>
#include <string>

StunGraphicsComponent::StunGraphicsComponent(std::array<int, 4> color, const IWorldView* world)
    : color(color), world(world) {
    setLayer(Unit::Layer::Overlay);
}

void StunGraphicsComponent::update(float dt) {
    if (active) {
        timer += dt;
        return;
    }
    if (!bullet->getLockHitboxes().empty()) {
        const CircleHitbox* hitbox = dynamic_cast<const CircleHitbox*>(std::get<0>(bullet->getLockHitboxes().front()));
        for (auto p : world->getPlayers()) {
            if (p->getPlayerId() == bullet->isWhose()) continue;
            if (hitbox->collidesWithCircle(*p->getHitbox())) {
                active = true;
                timer = 0.0f;
                pos = p->getPosition();
            }
        }
    }
}

void StunGraphicsComponent::render() const {
    if (!active) return;

    // Draw rings
    int alpha[3] = {190, 120, 70};
    int id = 0;
    for (int i = 0; i < 3; ++i) {
        float ringTime = (i + 1) * TIME;
        if (timer > ringTime) continue;
        float radius = FIRST_RADIUS + i * SPACING;
        Color ringColor = {
            (unsigned char)color[0],
            (unsigned char)color[1],
            (unsigned char)color[2],
            (unsigned char)alpha[id++]
        };
        DrawRing(
            { pos.x, pos.y },
            std::max(0.0f, radius - THICKNESS / 2.0f),
            radius + THICKNESS / 2.0f,
            0.0f, 360.0f,
            64,
            ringColor
        );
    }

    // Draw floating "stunned!!" text
    static Font font = LoadFontEx("../assets/fonts/Redressed.ttf", 64, 0, 0);
    float floatOffset = -FLOAT_SPEED * (timer + 0.5f);
    Vector2 textPos = { pos.x + 70, pos.y + floatOffset };
    std::string text = "stunned!!";
    int fontSize = 47;
    Vector2 measure = MeasureTextEx(font, text.c_str(), fontSize, 0);
    DrawTextEx(font, text.c_str(),
        { textPos.x - measure.x / 2, textPos.y },
        fontSize, 0,
        Fade(WHITE, 0.66f)
    );
    
}