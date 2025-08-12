#ifndef HOT_BAR_HPP
#define HOT_BAR_HPP

#include "HotBarSlot.hpp"
#include "../../../../../game/hitbox/RectangleHitbox.hpp"
#include "../../../../../game/hitbox/CircleHitbox.hpp"
#include <vector>
#include <memory>

class HotBar {
public:
    HotBar();
    ~HotBar();

    // Initialization
    void loadTexture(std::vector<std::string> texturePaths);
    void init();
    void setPosition(Vector2 position); // Start position
    void setRectangleHitBox(Rectangle rec);
    void setCooldowns(const std::vector<float>& cooldowns);
    void setSide(bool isLeft);
    
    // Slot management
    HotBarSlot* getSlot(int index);
    int getSlotCount() const;
    void setCooldownDuration(int slotIndex, float duration);
    void setFadeHidding(bool hidden);
    
    // Collision detection
    void checkCollision(std::vector<const CircleHitbox*> circleHitbox);
    void resetFadeHidding();
    
    // Update
    void update(float dt);

private:
    std::vector<HotBarSlot> slots;
    std::unique_ptr<RectangleHitbox> hitbox = nullptr;
    
    Vector2 startPos = {0.0f, 0.0f};
    const float slotSpacing = 10.0f;
    Rectangle rectangleHitbox = {0, 0, 0, 0};
    
    bool fadeActive = false;
    bool isLeft = true;
    
    void updateSlotPositions();
    Vector2 getSymmetricPos(Vector2 pos);
};

#endif // HOT_BAR_HPP