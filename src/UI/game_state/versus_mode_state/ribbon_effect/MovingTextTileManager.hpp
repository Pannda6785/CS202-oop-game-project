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
    
    // Core functions
    void update(float dt);
    
    // Utility functions
    void clear();                        // Remove all tiles
    bool hasPauseTile() const;           // Check if a pause tile exists
    bool hasActiveTiles() const;         // Check if any tiles are active
    void removePauseTile();              // Remove only pause tiles

private:
    // List of <timer, tile> pairs (timer counts down to removal)
    std::vector<std::pair<float, std::unique_ptr<MovingTextTile>>> movingTextTileList;
    
    // Track if we have a pause tile (which has no timer)
    bool pauseTileActive;
    int pauseTileIndex;
    int countdownTileIndex = -1;
    int readyTileIndex = -1;

    // Helper methods
    void createReadyTile(float displayTime);
    void createCountdownTile(float displayTime);
    void createPauseTile();
};

#endif // MOVING_TEXT_TILE_MANAGER_HPP