#include "CharacterGraphicsComponent.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include <raylib.h>
#include <algorithm>

CharacterGraphicsComponent::CharacterGraphicsComponent(const IPlayerView* playerView)
    : player(playerView),
      frameTime(0.0f),
      hitboxTexture(nullptr),
      arrowTexture(nullptr)
{
    loadTextures();
}

CharacterGraphicsComponent::~CharacterGraphicsComponent() {
    unloadTextures();
}

void CharacterGraphicsComponent::update(float dt) {
    frameTime += dt;
}

void CharacterGraphicsComponent::render(Renderer& /*renderer*/) const {
    if (!player) return;

    Unit::Vec2D pos = player->getPosition();
    Vector2 center = { pos.x, pos.y };

    // Draw character
    int currentFrame = static_cast<int>(frameTime / characterAnimationSpeed) % std::max(1, static_cast<int>(idle.size()));
    if (!idle.empty()) {
        Texture2D tex = *idle[currentFrame];
        float scale = 0.25f; // adjust to fit your game
        Vector2 drawPos = {
            center.x - tex.width * scale / 2.0f + 20 * scale,
            center.y - tex.height * scale / 2.0f - 30 * scale
        };
        DrawTextureEx(tex, drawPos, 0.0f, scale, WHITE);
    } else {
        DrawCircleV(center, 20.0f, BLUE);
    }
    // Draw arrow
    Unit::Vec2D arrow = player->getArrow();
    Vector2 arrowEnd = { pos.x + arrow.x * 40, pos.y + arrow.y * 40 };
    DrawLineEx(center, arrowEnd, 3.0f, RED);
    Vector2 perp = { -arrow.y, arrow.x };  // perpendicular vector
    Vector2 tip = arrowEnd;
    Vector2 baseLeft = { tip.x - arrow.x * 10 + perp.x * 5, tip.y - arrow.y * 10 + perp.y * 5 };
    Vector2 baseRight = { tip.x - arrow.x * 10 - perp.x * 5, tip.y - arrow.y * 10 - perp.y * 5 };
    Vector2 points[3] = { tip, baseLeft, baseRight };
    DrawTriangle(points[0], points[1], points[2], RED);

    // Draw hitbox
    const CircleHitbox* hitbox = player->getHitbox();
    if (hitbox) {
        Unit::Vec2D pos = hitbox->getPosition();
        Vector2 center = { pos.x, pos.y };
        float radius = hitbox->getRadius();
        DrawCircleV(center, radius, RED);
    }

    // Draw health as hearts below player
    const float heartSpacing = 22;
    for (int i = 0; i < 3; ++i) {
        Vector2 heartPos = { pos.x - 12 - heartSpacing + i * heartSpacing, pos.y + 70 };
        if (i < player->getHealth()) {
            DrawText("<3", static_cast<int>(heartPos.x), static_cast<int>(heartPos.y), 20, RED);
        } else {
            DrawText("<3", static_cast<int>(heartPos.x), static_cast<int>(heartPos.y), 20, DARKGRAY);
        }
    }

    // Draw stock as small blue circles below hearts
    const float stockRadius = 6;
    for (int i = 0; i < player->getStock(); ++i) {
        Vector2 stockPos = { pos.x - stockRadius - 5 + i * heartSpacing, pos.y + 100 };
        DrawCircleV(stockPos, stockRadius, BLUE);
        DrawCircleLines(static_cast<int>(stockPos.x), static_cast<int>(stockPos.y), stockRadius, DARKBLUE);
    }

    // Draw invincibility indicator
    float invTime = player->getInvincibility();
    if (invTime > 0.0f) {
        float maxTime = 3.0f; // total invincibility duration
        float percent = std::clamp(invTime / maxTime, 0.0f, 1.0f);

        float radius = 58.0f;
        float thickness = 4.0f;

        float startAngle = -90.0f; // top of the circle
        float endAngle = startAngle + 360.0f * percent;

        DrawRing(
            center,
            radius - thickness / 2.0f, // inner radius
            radius + thickness / 2.0f, // outer radius
            startAngle,
            endAngle,
            64,                        // smoothness
            GREEN
        );
    }
}

void CharacterGraphicsComponent::takeHit() {
    frameTime = 0.0f;
}

void CharacterGraphicsComponent::loadTextures() {
    std::string character_path = "../assets/sprites/priestess/";

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "movement/idle" + std::to_string(i) + ".png";
        idle.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "movement/walk" + std::to_string(i) + ".png";
        walkForward.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "movement/back" + std::to_string(i) + ".png";
        walkBackward.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "hit/stagger" + std::to_string(i) + ".png";
        stagger.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 5; ++i) {
        std::string path = character_path + "hit/wake" + std::to_string(i) + ".png";
        wakeup.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    // hitboxTexture = new Texture2D(LoadTexture("..."));
    // arrowTexture = new Texture2D(LoadTexture("..."));
}

void CharacterGraphicsComponent::unloadTextures() {
    auto freeTextures = [](std::vector<Texture*>& textures) {
        for (Texture* tex : textures) {
            if (tex) {
                UnloadTexture(*tex);
                delete tex;
            }
        }
        textures.clear();
    };

    freeTextures(idle);
    freeTextures(walkForward);
    freeTextures(walkBackward);
    freeTextures(stagger);
    freeTextures(wakeup);

    if (hitboxTexture) {
        UnloadTexture(*hitboxTexture);
        delete hitboxTexture;
        hitboxTexture = nullptr;
    }

    if (arrowTexture) {
        UnloadTexture(*arrowTexture);
        delete arrowTexture;
        arrowTexture = nullptr;
    }
}
