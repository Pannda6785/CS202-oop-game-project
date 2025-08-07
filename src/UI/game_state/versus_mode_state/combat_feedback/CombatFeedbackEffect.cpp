#include "CombatFeedbackEffect.hpp"
#include <iostream>

CombatFeedbackEffect::CombatFeedbackEffect() = default;

CombatFeedbackEffect::CombatFeedbackEffect(Vector2 hitPos, Vector2 hitterPos)
    : CombatFeedback(hitPos, hitterPos) {
    // Set default properties
    std::vector<std::string> texturePaths = {
        "../assets/UI_sprites/spr_splatter_0.png",
        "../assets/UI_sprites/spr_splatter_1.png",
        "../assets/UI_sprites/spr_splatter_2.png"
    };
    for (const auto& path : texturePaths) {
        artwork.addTexture(path);
    }
    float period = 100.0f;
    artwork.setLayer(100);
    artwork.setScale(0.7f);
    artwork.setPeriod(period);
    artwork.setPosition(static_cast<int>(hitPos.x), static_cast<int>(hitPos.y));
    setDuration(period * static_cast<float>(texturePaths.size()));

    // Determine alignment based on relative positions
    hAlign = hitPos.x <= hitterPos.x ? HorizontalAlignment::LEFT : HorizontalAlignment::RIGHT;
    vAlign = hitPos.y <= hitterPos.y ? VerticalAlignment::UP : VerticalAlignment::DOWN;
}

CombatFeedbackEffect::~CombatFeedbackEffect() {
    // Ensure artwork is unloaded properly
    // (No need to explicitly clear textures as Artwork destructor handles this)
}

bool CombatFeedbackEffect::addTexture(const std::string& filePath) {
    return artwork.addTexture(filePath);
}

void CombatFeedbackEffect::setScale(float scale) {
    artwork.setScale(scale);
    updatePosition();
}

void CombatFeedbackEffect::setAnimationPeriod(float period) {
    artwork.setPeriod(period);
}

void CombatFeedbackEffect::setFlip(bool flip) {
    artwork.setFlip(flip);
}

void CombatFeedbackEffect::update(float dt) {
    CombatFeedback::update(dt); // Call base class update for timer
    
    if (active) {
        artwork.update(dt); // Update animation
    }
}

void CombatFeedbackEffect::render() const {
    if (active) {
        artwork.render();
    }
}

void CombatFeedbackEffect::activate() {
    CombatFeedback::activate();
    updatePosition();
}

void CombatFeedbackEffect::updatePosition() {
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    
    int width = artwork.getWidth();
    
    // Adjust horizontal position
    if (hAlign == HorizontalAlignment::LEFT) {
        x -= width - static_cast<int>(offset.x);
    } else {
        x += static_cast<int>(offset.x);
    }
    
    // Adjust vertical position
    if (vAlign == VerticalAlignment::UP) {
        y -= width - static_cast<int>(offset.y); // Approximate height with width since artwork might not have getHeight()
    } else {
        y += static_cast<int>(offset.y);
    }
    
    artwork.setPosition(x, y);
}