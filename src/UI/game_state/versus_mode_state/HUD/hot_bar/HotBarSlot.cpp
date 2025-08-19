#include "HotBarSlot.hpp"
#include <iostream>
#include <cmath>

HotBarSlot::HotBarSlot() {
    skillIconSlot.setOriginRatio({0.5f, 0.5f});
    skillIconSlot.setLayer(5);
    
    cooldownText.setFontSize(40);
    cooldownText.setColor(WHITE);
    cooldownText.loadFont("../assets/fonts/18thCentury.ttf");
    cooldownText.setOriginRatio({0.5f, 0.5f});
}

HotBarSlot::~HotBarSlot() {
    // Resources will be automatically cleaned up by Artwork and GameText destructors
}

void HotBarSlot::loadSkillIconSlotTexture(std::string texturePath) {
    if (!skillIconSlot.addTexture(texturePath)) {
        std::cerr << "Failed to load slot background: " << texturePath << std::endl;
    }
    updateTransparency();
}

void HotBarSlot::setPosition(Vector2 position) {
    pos = position;
    skillIconSlot.setPosition(static_cast<int>(pos.x), static_cast<int>(pos.y));
    cooldownText.setPosition(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void HotBarSlot::setCooldownDuration(float duration) {
    cooldownDuration = duration;
    updateCooldownText();
    updateTransparency();
}

void HotBarSlot::setFadeHidding(bool hidden) {
    fadeHidding = hidden;
    updateTransparency();
}

bool HotBarSlot::isOnCooldown() const {
    return cooldownDuration > 0.0f;
}

bool HotBarSlot::isHidden() const {
    return fadeHidding;
}

float HotBarSlot::getWidth() const {
    return skillIconSlot.getWidth();
}

Vector2 HotBarSlot::getPosition() const {
    return pos;
}

void HotBarSlot::update(float dt) {
    updateCooldownText();
    updateTransparency();
    skillIconSlot.update(dt);
}

void HotBarSlot::updateCooldownText() {
    if (cooldownDuration > 0.0f) {
        std::string text = std::to_string(cooldownDuration);
        if (text.find('.') != std::string::npos) {
            size_t dotPos = text.find('.');
            if (dotPos + 2 < text.length()) {
                text = text.substr(0, dotPos + 2);
            }
        }
        cooldownText.setText(text);
    } else {
        cooldownText.setText("");
    }
}

void HotBarSlot::updateTransparency() {
    if (fadeHidding) {
        skillIconSlot.setAlphaColor(fadeHiddingAlpha);
        cooldownText.setAlphaColor(fadeHiddingAlpha);
    } else if (cooldownDuration > 0.0f) {
        skillIconSlot.setAlphaColor(fadeCooldown);
        cooldownText.setAlphaColor(1.0f);
    } else {
        skillIconSlot.setAlphaColor(1.0f);
    }
}