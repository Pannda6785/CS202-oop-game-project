#include "HealthBar.hpp"
#include "../../../IWorldView.hpp"
#include "../../../player/Player.hpp"
#include <iostream>

HealthBar::HealthBar(bool isLeftSide) 
    : health(1), stock(4), isLeft(isLeftSide), 
      shaderEnabled(false), blurActive(false),
      scale(0.7f) {
    
    signatureColor = {235, 115, 60, 255}; // Default color
    
    // Set default positions
    backgroundPos = {220.0f, 120.0f};
    avatarPos = {160.0f, 120.0f};
    heartPos = {295.0f, 90.0f};
    healthTextPos = {250.0f, 100.0f};
    stockPos = {330.0f, 135.0f};
    stockPosOffset = {-40.0f, 20.0f};   
    
    // Configure the hitbox for collision detection
    hitboxRect = {
        0.0f, 
        0.0f,
        460.0f, // Width of the health bar
        330.0f  // Height of the health bar
    };

    if(!isLeft){
        backgroundPos = getSymmetricPos(backgroundPos);
        hitboxRect.x = getSymmetricPos({hitboxRect.x, hitboxRect.y}).x - hitboxRect.width;
        avatarPos = getSymmetricPos(avatarPos);
        heartPos = getSymmetricPos(heartPos);
        healthTextPos = getSymmetricPos(healthTextPos);
        stockPos = getSymmetricPos(stockPos);
        stockPosOffset = {-stockPosOffset.x, stockPosOffset.y};
    }
}

HealthBar::~HealthBar() = default;

void HealthBar::loadAssets() {
    // This is implemented by subclasses to load character-specific assets
}

void HealthBar::init() {
    // Load background
    std::string bgTexture = isLeft ? 
        "../assets/UI_sprites/health_bar/health_bar_background_left.png" : 
        "../assets/UI_sprites/health_bar/health_bar_background_right.png";
    background.addTexture(bgTexture);
    background.setScale(0.8f);
    background.setOriginRatio({0.5, 0.5f});
    background.setPosition(backgroundPos.x, backgroundPos.y);
    std::cout << "background pos " << backgroundPos.x << ' ' << backgroundPos.y << std::endl;

    // Load default avatar (will be overridden by character subclasses)
    float avtScale = 0.9f;
    avatar.setOriginRatio({0.5f, 0.5f});
    avatar.loadShader("../src/UI/game_state/versus_mode_state/HUD/health_bar/flash_red.fs");
    avatar.setScale(avtScale);
    avatar.setPosition(avatarPos.x, avatarPos.y);

    // Load heart
    for(int i = 0; i < 2; ++i) {
        heart[i].addTexture("../assets/UI_sprites/health_bar/heart.png");
        heart[i].setOriginRatio({0.5f, 0.5f});
        heart[i].setScale(scale * 0.7f);
        heart[i].loadShader("../src/UI/game_state/versus_mode_state/HUD/health_bar/flash_red.fs");
        heart[i].enableShader(shaderEnabled);
        heart[i].setPosition(heartPos.x, heartPos.y);
    }
    heart[1].setScale(scale * 0.7f * 0.7f);
    heart[1].setColor(signatureColor);
    
    // Load health text
    healthText.loadFont("../assets/fonts/Redressed.ttf");
    healthText.setFontSize(65);
    healthText.setOriginRatio({0.5f, 0.5f});
    healthText.loadShader("../src/UI/game_state/versus_mode_state/HUD/health_bar/flash_red.fs");
    healthText.enableShader(shaderEnabled);
    healthText.setPosition(healthTextPos.x, healthTextPos.y);

    // Setup stock icons
    int numStock = 4; // Default 4 stocks
    stockIcons.resize(numStock);
    for(int i = 0; i < numStock; i++){
        stockIcons[i].resize(2);
        std::string stockTexture = isLeft ? 
            "../assets/UI_sprites/health_bar/left_stock.png" : 
            "../assets/UI_sprites/health_bar/right_stock.png";
        stockIcons[i][0].addTexture(stockTexture);
        stockIcons[i][0].setOriginRatio({0.5f, 0.5f});
        stockIcons[i][0].setScale(scale * 0.7f);

        stockIcons[i][1].addTexture(stockTexture);
        stockIcons[i][1].setOriginRatio({0.5f, 0.5f});
        stockIcons[i][1].setColor(signatureColor);
        stockIcons[i][1].setScale(scale * 0.5f);

        stockIcons[i][0].setPosition(stockPos.x + i * stockPosOffset.x, stockPos.y + i * stockPosOffset.y);
        stockIcons[i][1].setPosition(stockPos.x + i * stockPosOffset.x, stockPos.y + i * stockPosOffset.y);
    }

    hitbox = std::make_unique<RectangleHitbox>(
        Unit::Vec2D(hitboxRect.x + hitboxRect.width / 2.0f, hitboxRect.y + hitboxRect.height / 2.0f), 
        hitboxRect.width, 
        hitboxRect.height
    );

    // Update all positions
    updatePositions();
}

void HealthBar::setSide(bool isLeftSide) {
    if (isLeft != isLeftSide) {
        isLeft = isLeftSide;
        
        // Reload background texture based on side
        std::string bgTexture = isLeft ? 
            "../assets/UI_sprites/health_bar/health_bar_background_left.png" : 
            "../assets/UI_sprites/health_bar/health_bar_background_right.png";
        background = Artwork(); // Clear existing
        background.addTexture(bgTexture);
        background.setScale(scale);
        
        updatePositions(); // Update positions
    }
}

void HealthBar::setPosition(Vector2 position) {
    backgroundPos = position;
    updatePositions();
}

void HealthBar::setRectangleHitBox(Rectangle rec) {
    hitboxRect = rec;
}

void HealthBar::setHealth(int newHealth) {
    health = newHealth;
    healthText.setText(std::to_string(health));
}

void HealthBar::setStock(int newStock) {
    stock = newStock;
    if (stockIcons.size() < static_cast<size_t>(stock)) {
        size_t oldSize = stockIcons.size();
        stockIcons.resize(stock);
        for (size_t i = oldSize; i < stockIcons.size(); i++) {
            stockIcons[i].resize(2);
            stockIcons[i][0].addTexture("../assets/UI_sprites/health_bar/stock.png");
            stockIcons[i][0].setOriginRatio({0.5f, 0.5f});
            stockIcons[i][0].setScale(scale * 0.7f);
            
            stockIcons[i][1].addTexture("../assets/UI_sprites/health_bar/stock.png");
            stockIcons[i][1].setOriginRatio({0.5f, 0.5f});
            stockIcons[i][1].setScale(scale * 0.5f);
            stockIcons[i][1].setColor(signatureColor);
        }
        updatePositions();
    }
    while (stockIcons.size() > static_cast<size_t>(stock)) {
        stockIcons.pop_back();
    }
}

void HealthBar::setSignatureColor(Color color) {
    signatureColor = color;
    
    // Update heart color
    heart[1].setColor(signatureColor);
    
    // Update stock icon colors
    for (auto& stockPair : stockIcons) {
        stockPair[1].setColor(signatureColor);
    }
}

void HealthBar::activateShader(bool enable) {
    shaderEnabled = enable;
    
    // Enable/disable shader for avatar, heart, and healthText
    avatar.enableShader(enable);
    heart[0].enableShader(enable);
    heart[1].enableShader(enable);
    healthText.enableShader(enable);
}

void HealthBar::triggerShake() {
    // Empty implementation for now - will animate healthText and heart
}

void HealthBar::checkCollision(std::vector<const CircleHitbox*> circleHitboxes) {
    if (circleHitboxes.empty()) {
        return;
    }
    bool collides = false;
    for (const auto& chb : circleHitboxes) {
        if (hitbox->collidesWithCircle(*chb)) {
            collides = true;
            break;
        }
    }
    // If collision state changed, update blur effect
    if (collides != blurActive) {
        blurActive = collides;
        // Apply blur effect by changing alpha
        float alpha = blurActive ? 0.1f : 1.0f;
        background.setAlphaColor(alpha);
        avatar.setAlphaColor(alpha);
        for (int i = 0; i < 2; i++) {
            heart[i].setAlphaColor(alpha);
        }
        healthText.setAlphaColor(alpha);
        for (auto& stockPair : stockIcons) {
            stockPair[0].setAlphaColor(alpha);
            stockPair[1].setAlphaColor(alpha);
        }
    }
}

void HealthBar::setWorldView(IWorldView* worldView) {
    this->worldView = worldView;
}

void HealthBar::update(float dt) {
    // If we have a world view pointer, get player data directly
    if (worldView) {
        std::vector<const Player*> players = worldView->getPlayers();
        if (!players.empty()) {
            // Get the appropriate player based on which side we're on
            int playerIndex = isLeft ? 0 : 1;
            
            if (playerIndex < players.size()) {
                const Player* player = players[playerIndex];
                
                // Get health and stock for this player
                int playerHealth = player->getHealth();
                int playerStock = player->getStock();
                
                // Update health and stock if they've changed
                if (playerHealth != health) {
                    setHealth(playerHealth);
                }
                
                if (playerStock != stock) {
                    setStock(playerStock);
                }
                
                // Check if player was just hit to activate shader effect
                // if (player->wasHit()) {
                //     activateShader(true);
                //     triggerShake();
                // }
            }
            
            // Get hitboxes for collision detection
            std::vector<const CircleHitbox*> circleHitboxes;
            for (const auto* player : players) {
                circleHitboxes.push_back(player->getHitbox());
            }
            
            // Check for collision
            checkCollision(circleHitboxes);
        }
    }

    // Update all components
    background.update(dt);
    avatar.update(dt);
    heart[0].update(dt);
    heart[1].update(dt);
    healthText.update(dt);
    for (auto& stockPair : stockIcons) {
        stockPair[0].update(dt);
        stockPair[1].update(dt);
    }
}

Vector2 HealthBar::getSymmetricPos(Vector2 pos) {
    return {GetScreenWidth() - pos.x, pos.y};
}

void HealthBar::updatePositions() {
    for (int i = 0; i < 2; i++) {
        heart[i].setPosition(heartPos.x, heartPos.y);
    }
    healthText.setPosition(healthTextPos.x, healthTextPos.y);
    healthText.setText(std::to_string(health));
    for (size_t i = 0; i < stockIcons.size(); i++) {
        Vector2 pos = {
            stockPos.x + i * stockPosOffset.x, 
            stockPos.y + i * stockPosOffset.y
        };
        stockIcons[i][0].setPosition(pos.x, pos.y);
        stockIcons[i][1].setPosition(pos.x, pos.y);
    }
}