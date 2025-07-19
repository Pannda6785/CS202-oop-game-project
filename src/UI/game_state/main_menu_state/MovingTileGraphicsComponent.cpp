#include "MovingTileGraphicsComponent.hpp"
#include <cmath>
#include <cassert>

MovingTileGraphicsComponent::MovingTileGraphicsComponent() = default;

MovingTileGraphicsComponent::~MovingTileGraphicsComponent() {
    unloadTextures();
}

void MovingTileGraphicsComponent::loadTexture(const std::string& texturePath){
    tilePattern = LoadTexture(texturePath.c_str());
    loadedTilePattern = (tilePattern.id != 0);
}

void MovingTileGraphicsComponent::unloadTextures() {
    if (loadedTilePattern) {
        UnloadTexture(tilePattern);
        loadedTilePattern = false;
    }
    if (loadedSideLines) {
        UnloadTexture(sideLines);
        loadedSideLines = false;
    }
}

void MovingTileGraphicsComponent::loadSideLines(const std::string& sideLinesPath) {
    sideLines = LoadTexture(sideLinesPath.c_str());
}

void MovingTileGraphicsComponent::init(Vector2 _startPosition, float _angle, float _speed, int layer) {
    // Initialize positions or any other setup needed
    startPosition = _startPosition; // Starting position of the tiles
    angle = _angle;
    speed = _speed;
    setLayer(layer);
    positions.clear();
    positions.push_back(startPosition); // Example position
    int numTiles = 15; // Number of tiles to generate
    int tileHeight = tilePattern.height; // Height of the tile texture
    float deltaX = sin(angle * (PI / 180.0)) * tileHeight; // Horizontal distance between tiles
    float deltaY = cos(angle * (PI / 180.0)) * tileHeight; // Vertical distance between tiles
    for (int i = 0; i < numTiles; ++i) {
        float x = startPosition.x + i * deltaX;
        float y = startPosition.y + i * deltaY;
        positions.push_back({x, y});
    }
}

void MovingTileGraphicsComponent::update(float dt) {
    int tileHeight = tilePattern.height; // Height of the tile texture
    float sina = sin(angle * (PI / 180.0));
    float cosa = cos(angle * (PI / 180.0));
    for(int i = 0; i < positions.size(); ++i) {
        // Update each position based on speed and angle
        positions[i].x -= speed * dt * sina;
        positions[i].y -= speed * dt * cosa;
    }
    if(positions[0].y + tilePattern.height < 0) {
        positions.erase(positions.begin());
        // Add a new position at the bottom of the screen
        Vector2 newPosition = { positions.back().x + sina * tileHeight, positions.back().y + cosa * tilePattern.height };
        positions.push_back(newPosition);
    }
}

void MovingTileGraphicsComponent::render() const {
    if (!isVisible() || tilePattern.id == 0) return; // Check if the texture is loaded

    for (const auto& pos : positions) {
        DrawTextureEx(tilePattern, pos, -angle, 1.0f, WHITE);
        if(sideLines.id != 0) DrawTextureEx(sideLines, pos, -angle, 1.0f, WHITE);
    }
}