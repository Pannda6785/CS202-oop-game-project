#include "MovingTextTileManager.hpp"
#include <algorithm>
#include <iostream>

MovingTextTileManager::MovingTextTileManager() {
}

MovingTextTileManager::~MovingTextTileManager() {
    // clear();
}

void MovingTextTileManager::addReady(float displayTime) {
    if (displayTime <= 0.0f) {
        std::cerr << "Warning: Invalid display time for READY tile" << std::endl;
        return;
    }
    
    createReadyTile(displayTime);
}

void MovingTextTileManager::addCountdown(float displayTime) {
    if (displayTime <= 0.0f) {
        std::cerr << "Warning: Invalid display time for countdown tile" << std::endl;
        return;
    }
    
    createCountdownTile(displayTime);
}

void MovingTextTileManager::addPause() {
    createPauseTile();
}

void MovingTextTileManager::update(float dt) {
    bool needsCleanup = false;
    
    // Update all tiles and their timers
    for (auto& pair : movingTextTileList) {
        if (pair.first > 0.0f) {
            pair.first -= dt;
            
            if (pair.first <= 0.0f) {
                pair.first = 0.0f;
                needsCleanup = true;
            }
        }
        
        if (pair.second) {
            pair.second->update(dt);
        }
    }
    
    // Remove any expired tiles
    if (needsCleanup) {
        auto it = std::remove_if(
            movingTextTileList.begin(), 
            movingTextTileList.end(),
            [](const auto& pair) { 
                return pair.first <= 0.0f && pair.second != nullptr; 
            }
        );
        
        movingTextTileList.erase(it, movingTextTileList.end());
    }
    if(countdownTileIndex != -1 && countdownTileIndex < movingTextTileList.size()){
        std::string countdown = std::to_string(movingTextTileList[countdownTileIndex].first);
        while(countdown[countdown.size() - 3] != '.' && countdown.size() > 0) countdown.pop_back();
        if(countdown.size() == 0) countdown = "0.0";
        countdown += " SECONDS";
        movingTextTileList[countdownTileIndex].second->setText(countdown);
    }
}

void MovingTextTileManager::setVisible(bool visible) {
    for (auto& pair : movingTextTileList) {
        if (pair.second) {
            pair.second->setVisible(visible);
        }
    }
}

void MovingTextTileManager::clear() {
    movingTextTileList.clear();
}

void MovingTextTileManager::createReadyTile(float displayTime) {
    float padding = 150.0f;
    auto readyTile = MovingTextTileBuilder()
        .withTileTexture("../assets/UI_sprites/charselect_ribbon_mid.png")
        .withTileStartPosition({0, 450})
        .withTileSpeed(75.0f)
        .withTileAngle(93.0f)
        .withTileScale(0.75f)
        .withTileInitialNum(20)
        // .withTileExpandingTime(0.3f)
        // .withTileStartExpand(true)
        .withTileRestrictArea({-padding, -padding, GetScreenWidth() + padding * 2.0f, GetScreenHeight() + padding * 2.0f})
        
        .withBackgroundColor(WHITE) // Blue background
        .withBackgroundWidthRatio(0.8f)
        
        .withText("READY")
        .withTextFont("../assets/fonts/ferrum.otf")
        .withTextFontSize(145)
        .withTextColor(BLACK)
        .withTextSpacing(300.0f)

        .withLayer(1) // High layer to appear above game elements
        .build();
    
    // Add to the list with timer
    movingTextTileList.emplace_back(displayTime, std::move(readyTile));
    readyTileIndex = movingTextTileList.size() - 1;
}

void MovingTextTileManager::createCountdownTile(float displayTime) {
    // Calculate what number to show based on displayTime (3, 2, or 1)
    int countdownNumber = static_cast<int>(displayTime) + 1;
    if (countdownNumber < 1) countdownNumber = 1;
    if (countdownNumber > 3) countdownNumber = 3;   
    
    float padding = 350.0f;
    auto countdownTile = MovingTextTileBuilder()
        .withTileTexture("../assets/UI_sprites/charselect_ribbon_mid.png")
        .withTileStartPosition({0, 600})
        .withTileSpeed(75.0f)
        .withTileAngle(85.0f)
        .withTileScale(0.75f)
        .withTileInitialNum(20)
        // .withTileExpandingTime(0.3f)
        // .withTileStartExpand(true)
        .withTileRestrictArea({-padding, -padding, GetScreenWidth() + padding * 2.0f, GetScreenHeight() + padding * 2.0f})
        
        .withBackgroundColor(WHITE)
        .withBackgroundWidthRatio(0.8f)
        
        .withText(std::to_string(countdownNumber) + ".00 SECONDS")
        .withTextFont("../assets/fonts/ferrum.otf")
        .withTextFontSize(145)
        .withTextColor(BLACK)
        .withTextSpacing(700.0f)
        
        .withLayer(1) // High layer to appear above game elements
        .build();
    
    // Add to the list with timer
    movingTextTileList.emplace_back(displayTime, std::move(countdownTile));
    countdownTileIndex = movingTextTileList.size() - 1;
}

void MovingTextTileManager::createPauseTile() {
    float padding = 180.0f;
    auto pauseTile = MovingTextTileBuilder()
        .withTileTexture("../assets/UI_sprites/charselect_ribbon_mid.png")
        .withTileStartPosition({0, 450})
        .withTileSpeed(75.0f)
        .withTileAngle(93.0f)
        .withTileScale(0.75f)
        .withTileInitialNum(20)
        // .withTileExpandingTime(0.5f)
        // .withTileStartExpand(true)
        .withTileRestrictArea({-padding, -padding, GetScreenWidth() + padding * 2.0f, GetScreenHeight() + padding * 2.0f})

        .withBackgroundColor(WHITE)
        .withBackgroundWidthRatio(0.8f)

        .withText("PAUSED")
        .withTextFont("../assets/fonts/ferrum.otf")
        .withTextFontSize(145)
        .withTextColor(BLACK) // Light gray/white
        .withTextSpacing(300.0f)

        .withLayer(100) // High layer
        .build();
    
    // Add to the list with special timer value (-1 means no timer)
    movingTextTileList.emplace_back(1e9, std::move(pauseTile));
}

void MovingTextTileManager::addAnnouncement(std::string announcement) {
    float padding = 300.0f;
    auto resultTile = MovingTextTileBuilder()
        .withTileTexture("../assets/UI_sprites/charselect_ribbon_mid.png")
        .withTileStartPosition({0, 450})
        .withTileSpeed(75.0f)
        .withTileAngle(93.0f)
        .withTileScale(0.75f)
        .withTileInitialNum(30)

        .withTileRestrictArea({-padding, -padding, GetScreenWidth() + padding * 2.0f, GetScreenHeight() + padding * 2.0f})
        
        .withBackgroundColor(WHITE)
        .withBackgroundWidthRatio(0.8f)
        
        .withText(announcement)
        .withTextFont("../assets/fonts/ferrum.otf")
        .withTextFontSize(145)
        .withTextColor(BLACK)
        .withTextSpacing(600.0f)
        
        .withLayer(100)
        .build();

    movingTextTileList.emplace_back(1e9, std::move(resultTile));
}
