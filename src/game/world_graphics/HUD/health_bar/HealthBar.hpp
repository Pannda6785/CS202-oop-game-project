#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include "../../../../UI/game_state/decorative_components/Artwork.hpp"
#include "../../../../UI/game_state/decorative_components/GameText.hpp"
#include "../../../hitbox/RectangleHitbox.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include <raylib.h>
#include <vector>
#include <memory>

class IWorldView;

class HealthBar {
public:
    HealthBar(bool isLeftSide = true);
    virtual ~HealthBar();

    // Initialization
    virtual void init();
    void setSide(bool isLeft);
    void setPosition(Vector2 position);
    void setRectangleHitBox(Rectangle rec);
    void setWorldView(IWorldView* worldView);
    
    // State management
    void setHealth(int health);
    int getHealth() const { return health; }
    void setStock(int stock);
    int getStock() const { return stock; }
    void setSignatureColor(Color color);
    
    // Effects
    void activateShader(bool enable);
    void triggerShake();
    
    // Collision detection
    void checkCollision(std::vector<const CircleHitbox*> circleHitbox);
    
    // Update
    void update(float dt);

protected:
    // Visual elements
    Artwork background;
    Artwork avatar;
    Artwork heart[2];
    GameText healthText;
    std::vector<std::vector<Artwork>> stockIcons;
    
    // State
    int health = 3;
    int stock = 4;
    bool isLeft = true;
    Color signatureColor = {235, 115, 60, 255};
    bool shaderEnabled = false;
    bool blurActive = false;
    
    Rectangle hitboxRect = Rectangle{0.0f, 0.0f, 200.0f, 100.0f};
    std::unique_ptr<RectangleHitbox> hitbox = nullptr;

    IWorldView* worldView = nullptr;

    // Layout
    float scale = 1.0f;
    Vector2 backgroundPos = {0.0f, 0.0f};
    Vector2 avatarPos = {0.0f, 0.0f};
    Vector2 heartPos = {0.0f, 0.0f};
    Vector2 healthTextPos = {0.0f, 0.0f};
    Vector2 stockPosOffset = {0.0f, 0.0f};
    Vector2 stockPos = {0.0f, 0.0f};
    
    // Helpers
    Vector2 getSymmetricPos(Vector2 pos);
    void updatePositions();
    virtual void loadAssets();
};

#endif // HEALTH_BAR_HPP