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
    float period = 0.15f;
    artwork.setLayer(Unit::Layer::Foreground);
    artwork.setScale(0.8f);
    artwork.setPeriod(period);
    artwork.setPosition(static_cast<int>(hitPos.x), static_cast<int>(hitPos.y));
    artwork.setOriginRatio(hitEffectOriginRatio);
    setDuration(period * static_cast<float>(texturePaths.size()));
    artwork.addTag("world_object");
    if(hitPos.x > hitterPos.x){
        artwork.setFlipVertical(true);
    }
    if(hitPos.y > hitterPos.y){
        artwork.setFlipHorizontal(true);
    }
}

CombatFeedbackEffect::~CombatFeedbackEffect() {
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
    artwork.setPosition(x, y);
}