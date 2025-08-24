#ifndef MOVING_TEXT_TILE_MANAGER_HPP
#define MOVING_TEXT_TILE_MANAGER_HPP

#include "MovingTextTileBuilder.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <raylib.h>

class MovingTextTileManager {
public:
    MovingTextTileManager();
    ~MovingTextTileManager();

    // Add different types of moving text tiles
    void addReady(float displayTime);     // "READY" announcement
    void addCountdown(float displayTime); // Countdown 3...2...1
    void addPause();                      // "PAUSED" notification (no timer)
    void addResultAnnouncement(std::string annoucement); // "WIN" announcement

    // Core functions
    void update(float dt);
    void setVisible(bool visible);
    
    // Utility functions
    void clear();                        // Remove all tiles

private:
    std::vector<std::pair<float, std::unique_ptr<MovingTextTile>>> movingTextTileList;
    
    int countdownTileIndex = -1;
    int readyTileIndex = -1;

    // Helper methods
    void createReadyTile(float displayTime);
    void createCountdownTile(float displayTime);
    void createPauseTile();
};

#endif // MOVING_TEXT_TILE_MANAGER_HPP