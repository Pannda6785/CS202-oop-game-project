#include "CharacterGraphicsComponent.hpp"

#include "../player/Player.hpp"
#include "../hitbox/CircleHitbox.hpp"

#include <raylib.h>
#include <algorithm>

CharacterGraphicsComponent::CharacterGraphicsComponent() {
    setVisible(false);
    setLayer(Unit::Layer::Character);
    Shader loadedShader = LoadShader(0, "../src/game/character/white_silhouette.fs");
    whiteSilhouette = new Shader(loadedShader);
}

CharacterGraphicsComponent::~CharacterGraphicsComponent() {
    if (whiteSilhouette) {
        UnloadShader(*whiteSilhouette);  // unload the actual shader
        delete whiteSilhouette;          // free memory
        whiteSilhouette = nullptr;
    }
}

void CharacterGraphicsComponent::registerPlayer(Player* playerView) {
    player = playerView;
}

std::array<int, 4> CharacterGraphicsComponent::getSignatureColor() const {
    return signatureColor;
}

void CharacterGraphicsComponent::init() {
    setVisible(true);
    playAnim("idle");
    if (!player) {
        throw std::runtime_error("CharacterGraphicsComponent::init - CharacterGraphicsComponent must be initialized with a player before calling init()");
    }
}

void CharacterGraphicsComponent::render() const {
    renderUnderlay();
    renderCharacter();
    renderOverlay();
}

void CharacterGraphicsComponent::update(float dt) {
    time += dt;

    if (remainingStaggerTime > Unit::EPS) {
        playAnim("stagger");
        remainingStaggerTime -= dt;
    } else if (remainingWakeUpTime > Unit::EPS) {
        playAnim("wake");
        remainingWakeUpTime -= dt;
    } else if (characterSpecificUpdate(dt)) {
        // already handled in the function
    } else {
        Unit::Vec2D move = player->getMovement();
        if (move.magnitude() < Unit::EPS) {
            playAnim("idle");
        } else {
            float dir = player->getTargetPosition().x < player->getPosition().x ? -1.0f : 1.0f;
            if (dir * move.x > Unit::EPS || (dir * move.x > -Unit::EPS && move.y > -Unit::EPS)) {
                playAnim("walk");
            } else {
                playAnim("back");
            }
        }
    }
    
}

void CharacterGraphicsComponent::resize(float scale) {
    size *= scale;
}

void CharacterGraphicsComponent::takeHit(float staggerTime) {
    float wakeUpTime = animations["wake"].frames.size() / animations["wake"].fps;
    constexpr float extra = 0.2f;
    if (staggerTime < wakeUpTime) {
        // stagger only, no wake up
        remainingStaggerTime = staggerTime;
    } else {
        // stagger and wake up, stagger an little extra time 
        remainingStaggerTime = staggerTime - wakeUpTime + extra;
        remainingWakeUpTime = wakeUpTime;
    }
}

void CharacterGraphicsComponent::playAnim(const std::string& animName, bool restart) {
    auto it = animations.find(animName);
    if (it == animations.end() || (it->second).frames.empty()) {
        std::cerr << "Warning: Animation not found: " << animName << std::endl;
        return;
    }

    if (currentAnimName != animName || restart) {
        currentAnimName = animName;
        animStartTime = time;
    }

    const Animation& anim = it->second;
    
    float animTime = time - animStartTime;
    int frameIndex = static_cast<int>(animTime * anim.fps);

    if (anim.loop) {
        frameIndex %= anim.frames.size();
        toRenderCharacterTexture = anim.frames[frameIndex];
    } else {
        if (frameIndex >= anim.frames.size()) {
            toRenderCharacterTexture = anim.frames.back();
            std::cerr << "Warning: Tried to play a non-loop finished animation - " << animName << std::endl;
        } else {
            toRenderCharacterTexture = anim.frames[frameIndex];
        }
    }
}

bool CharacterGraphicsComponent::animFinished() const {
    auto it = animations.find(currentAnimName);
    if (it == animations.end()) {
        return true; // no animation playing..?
    }
    const Animation& anim = it->second;
    if (anim.loop) {
        return false;
    }
    float elapsedTime = time - animStartTime;
    float totalDuration = anim.frames.size() / anim.fps;
    return elapsedTime >= totalDuration; 
}

void CharacterGraphicsComponent::renderUnderlay() const {
    // TO DO: Properly do this right

    Unit::Vec2D pos = player->getPosition();
    Vector2 center = { pos.x, pos.y };

    // Draw health as hearts below player
    constexpr float heartSpacing = 22;
    for (int i = 0; i < 3; ++i) {
        Vector2 heartPos = { pos.x - 12 - heartSpacing + i * heartSpacing, pos.y + 70 };
        if (i < player->getHealth()) {
            DrawText("<3", static_cast<int>(heartPos.x), static_cast<int>(heartPos.y), 20, RED);
        } else {
            DrawText("<3", static_cast<int>(heartPos.x), static_cast<int>(heartPos.y), 20, DARKGRAY);
        }
    }

    // Draw stock as small blue circles below hearts
    constexpr float stockRadius = 6;
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
    Vector2 arrowEnd = { pos.x + arrow.x * 80, pos.y + arrow.y * 80 };
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
        DrawCircleV(center, radius * 4, Fade(RED, 0.7f));
        DrawCircleV(center, radius, BLACK);
    }
}

void CharacterGraphicsComponent::renderCharacter() const {
    if (!toRenderCharacterTexture) {
        std::cerr << "Warning: Character texture is not set!" << std::endl;
        return;
    }
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
        constexpr float flashFrequency = 4.0f;
        float flashAlpha = 0.5f * (sinf(time * flashFrequency * 2.0f * PI) + 1.0f); // 0.5 * [-1, 1]
        flashAlpha *= 0.7; // to avoid bright flashes
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