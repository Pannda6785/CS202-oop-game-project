#include "CharacterGraphicsComponent.hpp"

#include "../player/Player.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../../graphics/TextureManager.hpp"

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

    if (player->isFocused()) {
        if (currentRingRadius > INNER_RING_RADIUS) {
            currentRingRadius -= dt / TRANSITION_SPEED * (OUTER_RING_RADIUS - INNER_RING_RADIUS);
            currentRingRadius = std::max(currentRingRadius, INNER_RING_RADIUS);
        }
        if (currentOpacity < 1.0f) {
            currentOpacity += dt / TRANSITION_SPEED * (1.0f - MIN_OPACITY);
            currentOpacity = std::min(currentOpacity, 1.0f);
        }
    } else {
        if (currentRingRadius < OUTER_RING_RADIUS) {
            currentRingRadius += dt / TRANSITION_SPEED * (OUTER_RING_RADIUS - INNER_RING_RADIUS);
            currentRingRadius = std::min(currentRingRadius, OUTER_RING_RADIUS);
        }
        if (currentOpacity > MIN_OPACITY) {
            currentOpacity -= dt / TRANSITION_SPEED * (1.0f - MIN_OPACITY);
            currentOpacity = std::max(currentOpacity, MIN_OPACITY);
        }
    }

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
    Unit::Vec2D pos = player->getPosition();
    Vector2 center = { pos.x, pos.y };

    // Magic ring (underlay), always rotating with RPS, with currentOpacity
    const Texture* magicCircle = TextureManager::instance().getTexture("../assets/sprites/universal/spr_direction_circle_0.png");
    const float magicCircleResize = (2 * MAGIC_CIRCLE_RADIUS) / ((3.5f / 6.0f) * magicCircle->width); 
    float angle = fmodf(time * RPS * 360.0f, 360.0f);

    Color ringColor = Fade(WHITE, currentOpacity);
    DrawTexturePro(
        *magicCircle,
        {0, 0, (float)magicCircle->width, (float)magicCircle->height},
        {center.x, center.y, magicCircle->width * magicCircleResize, magicCircle->height * magicCircleResize},
        {magicCircle->width * magicCircleResize / 2.0f, magicCircle->height * magicCircleResize / 2.0f},
        angle,
        ringColor
    );
}

void CharacterGraphicsComponent::renderOverlay() const {
    Unit::Vec2D pos = player->getPosition();
    Vector2 center = { pos.x, pos.y };

    // Prepare lighter signature color for overlays
    Color sigColor = { 
        (unsigned char)(signatureColor[0] + (255 - signatureColor[0]) * 3 / 4),
        (unsigned char)(signatureColor[1] + (255 - signatureColor[1]) * 3 / 4),
        (unsigned char)(signatureColor[2] + (255 - signatureColor[2]) * 3 / 4),
        (unsigned char)signatureColor[3]
    };

    // Draw the arrow (overlay), rotate to player->getArrow(), with currentOpacity and lighter signature color
    const Texture* arrow = TextureManager::instance().getTexture("../assets/sprites/universal/spr_direction_pointer_0.png");
    const float arrowResize = (2 * ARROW_RADIUS) / ((3.5f / 6.0f) * arrow->width);
    float arrowAngle = atan2f(player->getArrow().y, player->getArrow().x) * 180.0f / PI;

    Color arrowColor = Fade(sigColor, currentOpacity);
    DrawTexturePro(
        *arrow,
        {0, 0, (float)arrow->width, (float)arrow->height},
        {center.x, center.y, arrow->width * arrowResize, arrow->height * arrowResize},
        {arrow->width * arrowResize / 2.0f, arrow->height * arrowResize / 2.0f},
        arrowAngle,
        arrowColor
    );

    // Draw the ring (overlay), no rotate, using currentRingRadius and lighter signature color
    const Texture* ring = TextureManager::instance().getTexture("../assets/sprites/universal/spr_direction_circle_2_0.png");
    const float ringResize = (2 * currentRingRadius) / ((3.5f / 6.0f) * ring->width);
    DrawTexturePro(
        *ring,
        {0, 0, (float)ring->width, (float)ring->height},
        {center.x, center.y, ring->width * ringResize, ring->height * ringResize},
        {ring->width * ringResize / 2.0f, ring->height * ringResize / 2.0f},
        0.0f,
        Fade(sigColor, currentOpacity)
    );

    // Draw hitbox (overlay), with currentOpacity
    const CircleHitbox* hitbox = dynamic_cast<const CircleHitbox*>(player->getHitbox());
    if (hitbox) {
        float radius = hitbox->getRadius();
        Unit::Vec2D hitboxPos = hitbox->getPosition();
        Vector2 hitboxCenter = { hitboxPos.x, hitboxPos.y };

        // Draw a faint circle for the "visual" hitbox
        DrawCircleV(hitboxCenter, radius * HITBOX_RADIUS_RATIO, Fade(RED, currentOpacity * 0.7f));
        DrawCircleV(hitboxCenter, radius, Fade(BLACK, currentOpacity));

        // Draw the TRUE hitbox as a solid circle with signature color
        DrawCircleV(hitboxCenter, radius * 0.5f, sigColor);
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

    const float resize = CHARACTER_HEIGHT / (4 / 6.0f * tex.height);
    float scale = resize * size;
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
        float flashAlpha = 0.5f * (sinf(time * FLASH_FREQUENCY * 2.0f * PI) + 1.0f); // 0.5 * [-1, 1]
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