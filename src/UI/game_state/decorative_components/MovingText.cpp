#include "MovingText.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

MovingText::MovingText() : GraphicsComponent(), textSpacing(10.0f) {
    sampleText = std::make_unique<GameText>();
}

MovingText::~MovingText() {
    // The unique_ptr will handle cleanup
}

void MovingText::setText(const std::string& text) {
    textContent = text;
    if (sampleText) {
        sampleText->setText(textContent);
    }
}

void MovingText::loadFont(const std::string& path) {
    fontPath = path;
    fontLoaded = true;
    if (sampleText) {
        sampleText->loadFont(fontPath);
    }
}

void MovingText::setFontSize(int size) {
    fontSize = size;
    if (sampleText) {
        sampleText->setFontSize(fontSize);
    }
}

void MovingText::setTextColor(Color color) {
    textColor = color;
    if (sampleText) {
        sampleText->setColor(textColor);
    }
}

void MovingText::setTextSpacing(float spacing) {
    textSpacing = spacing;
}

void MovingText::init() {
    if (textContent.empty()) {
        return;
    }
    
    positions.clear();
    
    // Configure the sample text
    sampleText->setText(textContent);
    if (fontLoaded) {
        sampleText->loadFont(fontPath);
    }
    sampleText->setFontSize(fontSize);
    sampleText->setColor(textColor);
    sampleText->setOriginRatio(originRatio);
    sampleText->setAngle(90 - angle);
    
    float textHeight = sampleText->getHeight() * scale;
    
    // Create initial position
    positions.push_back(startPosition);
    
    float deltaX = sin(angle * (PI / 180.0)) * (textHeight + textSpacing);
    float deltaY = cos(angle * (PI / 180.0)) * (textHeight + textSpacing);
    
    // Generate all positions
    for (int i = 0; i < initialNumTexts - 1; ++i) {
        float x = startPosition.x + (i + 1) * deltaX * (upward ? 1 : -1);
        float y = startPosition.y + (i + 1) * deltaY * (upward ? 1 : -1);
        positions.push_back({x, y});
    }
}

void MovingText::setStartPosition(Vector2 startPosition) {
    this->startPosition = startPosition;
}

void MovingText::setSpeed(float speed) {
    this->speed = speed;
}

void MovingText::setAngle(float angle) {
    this->angle = angle;
    if (sampleText) {
        sampleText->setAngle(90 - angle);
    }
}

void MovingText::setUpward(bool upward) {
    this->upward = upward;
}

void MovingText::setRestrictArea(Rectangle area) {
    restrictArea = area;
}

void MovingText::setScale(float scale) {
    this->scale = scale;
}

void MovingText::setInitialNumTexts(int numTexts) {
    initialNumTexts = numTexts;
}

void MovingText::setOriginRatio(Vector2 originRatio) {
    this->originRatio = originRatio;
    if (sampleText) {
        sampleText->setOriginRatio(originRatio);
    }
}

float MovingText::getTextWidth() const {
    if (!sampleText) return 0.0f;
    return sampleText->getWidth() * scale * getRatio();
}

float MovingText::getTextHeight() const {
    if (!sampleText) return 0.0f;
    return sampleText->getHeight() * scale * getRatio();
}

float MovingText::getRatio() const {
    return 1.0f;
}

Vector2 MovingText::getStartPositionToDraw() const {
    return positions.empty() ? Vector2({0.0f, 0.0f}) : getPositionToDraw(positions[0], getTextHeight(), getRatio());
}

Vector2 MovingText::getStartPosition() const {
    return positions.empty() ? Vector2({0.0f, 0.0f}) : positions[0];
}

Vector2 MovingText::getMiddlePosition() const {
    Vector2 pos = startPosition;
    float width = getTextWidth() / getRatio();
    float dx = width / 2.0f * cos(angle * (PI / 180.0));
    float dy = width / 2.0f * sin(angle * (PI / 180.0));
    Vector2 posToDraw = { pos.x + dx, pos.y - dy};
    return posToDraw;
}

Vector2 MovingText::getPositionToDraw(Vector2 pos, float textHeight, float ratio) const {
    float height = textHeight * scale;
    float dx = height / 2.0f * cos(angle * (PI / 180.0)) * (1.0f - ratio);
    float dy = height / 2.0f * sin(angle * (PI / 180.0)) * (1.0f - ratio);
    Vector2 posToDraw = { pos.x + dx, pos.y - dy};
    return posToDraw;
}

void MovingText::update(float dt) {
    if (textContent.empty() || !sampleText || positions.empty()) {
        return;
    }
    
    // Update the sample text
    sampleText->update(dt);
    
    float textHeight = getTextHeight();
    float sina = sin(angle * (PI / 180.0));
    float cosa = cos(angle * (PI / 180.0));
    
    // Move all existing positions
    for (auto& position : positions) {
        position.x -= speed * dt * sina * (upward ? 1 : -1);
        position.y -= speed * dt * cosa * (upward ? 1 : -1);
    }
    
    // Check if the first text has moved out of bounds
    if (positions[0].y < restrictArea.y || 
        positions[0].y > restrictArea.y + restrictArea.height ||
        positions[0].x > restrictArea.x + restrictArea.width || 
        positions[0].x < restrictArea.x) {
        
        // Remove the first position
        positions.erase(positions.begin());
        
        // Add a new position at the end
        Vector2 newPosition = { 
            positions.back().x + sina * (textHeight + textSpacing) * (upward ? 1 : -1), 
            positions.back().y + cosa * (textHeight + textSpacing) * (upward ? 1 : -1) 
        };
        positions.push_back(newPosition);
    }
}

void MovingText::render() const {
    if (textContent.empty() || !isVisible() || !sampleText || positions.empty()) return;
    
    // Save the original font size to restore after rendering
    int originalFontSize = sampleText->getFontSize();
    int scaledFontSize = fontSize * scale * getRatio();
    sampleText->setFontSize(scaledFontSize);
    
    // Render the sample text at each position
    for (const auto& position : positions) {
        sampleText->setPosition(position.x, position.y);
        sampleText->render();
    }
    
    // Restore original font size if needed
    if (originalFontSize != scaledFontSize) {
        sampleText->setFontSize(originalFontSize);
    }
}