#include "HotBar.hpp"
#include <iostream>

HotBar::HotBar() : fadeActive(false), hitbox(nullptr) {
    // Set the default position based on the side
    Vector2 startPos = {100.0f, GetScreenHeight() - 150.0f};
    setPosition(startPos);

    // Configure the hitbox for collision detection
    float width = 500.0f;
    float height = 300.0f;
    Rectangle hitboxRect = {
        0,
        GetScreenHeight() - height,
        width,
        height
    };
    setRectangleHitBox(hitboxRect);
}

HotBar::~HotBar() = default;

void HotBar::loadTexture(std::vector<std::string> texturePaths) {
    slots.resize(texturePaths.size());
    for (size_t i = 0; i < texturePaths.size(); ++i) {
        slots[i].loadSkillIconSlotTexture(texturePaths[i]);
    }
}

void HotBar::init() {
    if(!isLeft){
        startPos = getSymmetricPos(startPos);
        rectangleHitbox.x = getSymmetricPos({rectangleHitbox.x, rectangleHitbox.y}).x - rectangleHitbox.width;
    }
    updateSlotPositions();
    hitbox = std::make_unique<RectangleHitbox>(
        Unit::Vec2D(rectangleHitbox.x + rectangleHitbox.width / 2.0f, rectangleHitbox.y + rectangleHitbox.height / 2.0f), 
        rectangleHitbox.width, 
        rectangleHitbox.height
    );
}

void HotBar::setPosition(Vector2 position) {
    const_cast<Vector2&>(startPos) = position;
}

void HotBar::setRectangleHitBox(Rectangle rec){
    rectangleHitbox = rec;
}

void HotBar::setCooldowns(const std::vector<float>& cooldowns) {
    for (size_t i = 0; i < slots.size() && i < cooldowns.size(); ++i) {
        slots[i].setCooldownDuration(cooldowns[i]);
    }
}

void HotBar::setSide(bool isLeft){
    this->isLeft = isLeft;
}

HotBarSlot* HotBar::getSlot(int index) {
    if (index < 0 || index >= static_cast<int>(slots.size())) {
        std::cerr << "Error: HotBar slot index " << index << " out of range." << std::endl;
        return nullptr;
    }
    return &slots[index];
}

int HotBar::getSlotCount() const {
    return static_cast<int>(slots.size());
}

void HotBar::setCooldownDuration(int slotIndex, float duration) {
    if (slotIndex < 0 || slotIndex >= static_cast<int>(slots.size())) {
        std::cerr << "Error: HotBar slot index " << slotIndex << " out of range." << std::endl;
        return;
    }
    slots[slotIndex].setCooldownDuration(duration);
}

void HotBar::checkCollision(std::vector<const CircleHitbox*> circleHitbox) {
    if (circleHitbox.empty() || !hitbox) {
        return;
    }
    bool collides = false;
    for (const auto& chb : circleHitbox) {
        if (hitbox->collidesWithCircle(*chb)) {
            collides = true;
            break;
        }
    }
    if (collides != fadeActive) {
        fadeActive = collides;
        setFadeHidding(fadeActive);
    }
}

void HotBar::resetFadeHidding() {
    fadeActive = false;
    for (auto& slot : slots) {
        slot.setFadeHidding(false);
    }
}

void HotBar::setFadeHidding(bool hidden) {
    fadeActive = hidden;
    for (auto& slot : slots) {
        slot.setFadeHidding(fadeActive);
    }
}

void HotBar::update(float dt) {
    // Update all slots
    for (auto& slot : slots) {
        slot.update(dt);
    }
}

void HotBar::updateSlotPositions() {
    if (slots.empty()) {
        return;
    }
    // Set position for each slot
    float posX = startPos.x;
    for (size_t i = 0; i < slots.size(); ++i) {
        Vector2 slotPos = {
            posX,
            startPos.y
        };
        slots[i].setPosition(slotPos);
        posX += (slots[i].getWidth() + slotSpacing) * (isLeft ? 1 : -1);
    }
}

Vector2 HotBar::getSymmetricPos(Vector2 pos) {
    return {GetScreenWidth() - pos.x, pos.y};
}