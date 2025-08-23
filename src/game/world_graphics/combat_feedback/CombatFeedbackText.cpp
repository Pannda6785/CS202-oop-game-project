#include "CombatFeedbackText.hpp"

CombatFeedbackText::CombatFeedbackText() = default;

CombatFeedbackText::CombatFeedbackText(Vector2 hitPos, Vector2 hitterPos, std::string text)
    : CombatFeedback(hitPos, hitterPos) {
    // Set default properties
    gameText.setLayer(Unit::Layer::UI);
    gameText.loadFont("../assets/fonts/ferrum.otf");
    gameText.setText(text);
    gameText.setFontSize(140);
    gameText.setColor(WHITE);
    gameText.setPosition(static_cast<int>(hitPos.x), static_cast<int>(hitPos.y));
    hAlign = hitPos.x <= hitterPos.x ? HorizontalAlignment::RIGHT : HorizontalAlignment::LEFT;
    vAlign = hitPos.y <= hitterPos.y ? VerticalAlignment::DOWN : VerticalAlignment::UP;
    updatePosition();
    gameText.addTag("world_object");
}

CombatFeedbackText::~CombatFeedbackText() {
    // Clear text before destruction to prevent rendering issues
    gameText.setText("");
}

void CombatFeedbackText::setText(const std::string& text) {
    gameText.setText(text);
    updatePosition();
}

void CombatFeedbackText::setFontSize(int size) {
    gameText.setFontSize(size);
    updatePosition();
}

void CombatFeedbackText::setColor(Color color) {
    gameText.setColor(color);
}

void CombatFeedbackText::loadFont(const std::string& fontPath) {
    gameText.loadFont(fontPath);
    updatePosition();
}

void CombatFeedbackText::render() const {
    if (active) {
        gameText.render();
    }
}

void CombatFeedbackText::activate() {
    CombatFeedback::activate();
    updatePosition();
}

void CombatFeedbackText::updatePosition() {
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    
    // Adjust horizontal position
    if (hAlign == HorizontalAlignment::LEFT) {
        x -= static_cast<int>(gameText.getWidth()) + static_cast<int>(offset.x);
    } else {
        x += static_cast<int>(offset.x);
    }
    
    // Adjust vertical position
    if (vAlign == VerticalAlignment::UP) {
        y -= static_cast<int>(gameText.getHeight()) + static_cast<int>(offset.y);
    } else {
        y += static_cast<int>(offset.y);
    }
    
    gameText.setPosition(x, y);
}