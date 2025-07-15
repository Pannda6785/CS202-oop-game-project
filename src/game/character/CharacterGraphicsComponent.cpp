#include "CharacterGraphicsComponent.hpp"

#include "../player/IPlayerView.hpp"
#include "../hitbox/CircleHitbox.hpp"

#include <raylib.h>
#include <algorithm>
#include <iostream>
#include <cassert>

CharacterGraphicsComponent::CharacterGraphicsComponent() {
    setVisible(false);
    Shader loadedShader = LoadShader(0, "./src/game/character/white_silhouette.fs");
    whiteSilhouette = new Shader(loadedShader);
}

CharacterGraphicsComponent::~CharacterGraphicsComponent() {
    if (whiteSilhouette) {
        UnloadShader(*whiteSilhouette);  // unload the actual shader
        delete whiteSilhouette;          // free memory
        whiteSilhouette = nullptr;
    }
}

void CharacterGraphicsComponent::registerPlayer(IPlayerView* playerView) {
    player = playerView;
}

void CharacterGraphicsComponent::init() {
    setVisible(true);
}

void CharacterGraphicsComponent::render() const {
    renderUnderlay();
    renderCharacter();
    renderOverlay();
}

void CharacterGraphicsComponent::update(float dt) {
    time += dt;
    timeBuffer += dt;
    if (timeBuffer > 1 / animationFPS) {
        curAnimId++;
        timeBuffer -= 1 / animationFPS;
    }

    remainingStaggerTime = std::max(0.0f, remainingStaggerTime - dt);
    if (remainingStaggerTime > Unit::EPS) {
        if (remainingStaggerTime > wakeAnim.size() / animationFPS) {
            toRenderCharacterTexture = staggerAnim[curAnimId % staggerAnim.size()];
            wakeAnimId0 = curAnimId;
            return;
        } 
        if (curAnimId - wakeAnimId0 < wakeAnim.size()) {
            toRenderCharacterTexture = wakeAnim[curAnimId - wakeAnimId0];
            return;
        }
    }

    if (characterSpecificUpdate(dt)) {
        return;
    }

    Unit::Vec2D movement = player->getMovement();

    if (movement.magnitude() < Unit::EPS) {
        toRenderCharacterTexture = idleAnim[curAnimId % idleAnim.size()];
        return;
    }

    float direction = ((player->getTargetPosition()).x < (player->getPosition()).x) ? -1.0f : 1.0f;
    if (direction * movement.x > Unit::EPS || (direction * movement.x > -Unit::EPS && movement.y > -Unit::EPS)) {
        toRenderCharacterTexture = walkAnim[curAnimId % walkAnim.size()];
        return;
    }
    
    toRenderCharacterTexture = backAnim[curAnimId % backAnim.size()];
}

void CharacterGraphicsComponent::resize(float scale) {
    size *= scale;
}

void CharacterGraphicsComponent::takeHit(float staggerTime) {
    remainingStaggerTime = staggerTime;
}

void CharacterGraphicsComponent::renderUnderlay() const {
    // TO DO: Properly do this right

    Unit::Vec2D pos = player->getPosition();
    Vector2 center = { pos.x, pos.y };

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
}

void CharacterGraphicsComponent::renderOverlay() const {
    // TO DO: Properly do this right

    // Draw hitbox
    const CircleHitbox* hitbox = dynamic_cast<const CircleHitbox*>(player->getHitbox());
    if (hitbox) {
        Unit::Vec2D pos = hitbox->getPosition();
        Vector2 center = { pos.x, pos.y };
        float radius = hitbox->getRadius();
        DrawCircleV(center, radius, RED);
    }
}

void CharacterGraphicsComponent::renderCharacter() const {
    if(toRenderCharacterTexture == nullptr) return;
    Texture tex = *toRenderCharacterTexture;

    Unit::Vec2D pos = player->getPosition();
    Vector2 center = { pos.x, pos.y };

    float scale = 0.25f * size;
    float direction = ((player->getTargetPosition()).x < (player->getPosition()).x) ? -1.0f : 1.0f;

    Rectangle srcRect = {
        0.0f, 0.0f,
        direction * tex.width, (float)tex.height
    };

    Rectangle destRect = {
        center.x, center.y,
        tex.width * scale, tex.height * scale
    };

    Vector2 origin = {
        tex.width * scale / 2.0f,
        tex.height * scale / 2.0f
    };

    float inv = player->getInvincibility();

    if (inv > Unit::EPS) {
        float flashAlpha = 0.5f * (sinf(time * flashFrequency * 2.0f * PI) + 1.0f);
        BeginShaderMode(*whiteSilhouette);
        int flashLoc = GetShaderLocation(*whiteSilhouette, "flashAmount");
        SetShaderValue(*whiteSilhouette, flashLoc, &flashAlpha, SHADER_UNIFORM_FLOAT);
        DrawTexturePro(tex, srcRect, destRect, origin, 0.0f, WHITE); 
        EndShaderMode();
    } else {
        // Normal rendering
        DrawTexturePro(tex, srcRect, destRect, origin, 0.0f, WHITE);
    }
}