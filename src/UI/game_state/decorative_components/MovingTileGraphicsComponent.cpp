#include "MovingTileGraphicsComponent.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

MovingTileGraphicsComponent::MovingTileGraphicsComponent() = default;

MovingTileGraphicsComponent::~MovingTileGraphicsComponent() {
}

void MovingTileGraphicsComponent::addTexture(const std::string& texturePath){
    Texture2D texture = {0};
    texture = LoadTexture(texturePath.c_str());
    textures.push_back(texture);
}

void MovingTileGraphicsComponent::unloadTextures() {
    for (auto& texture : textures) {
        if (texture.id != 0) UnloadTexture(texture);
    }
    textures.clear();
}

void MovingTileGraphicsComponent::init(Vector2 _startPosition, float _angle, float _speed, int layer) {
    if(textures.empty() || textures[0].id == 0) {
        return;
    }
    startPosition = _startPosition;
    angle = _angle;
    speed = _speed;
    setLayer(layer);
    color = WHITE;
    positions.clear();
    positions.push_back(startPosition);
    int numTiles = initialNumTiles;
    int tileHeight = textures[0].height * scale;
    float deltaX = sin(angle * (PI / 180.0)) * tileHeight;
    float deltaY = cos(angle * (PI / 180.0)) * tileHeight;
    for (int i = 0; i < numTiles; ++i) {
        float x = startPosition.x + i * deltaX * (upward ? 1 : -1);
        float y = startPosition.y + i * deltaY * (upward ? 1 : -1);
        positions.push_back({x, y});
    }
}

void MovingTileGraphicsComponent::setUpward(bool upward) {
    this->upward = upward;
}

void MovingTileGraphicsComponent::setRestrictArea(Rectangle area) {
    restrictArea = area;
}

void MovingTileGraphicsComponent::setScale(float scale) {
    this->scale = scale;
}

void MovingTileGraphicsComponent::setInitialNumTiles(int numTiles) {
    initialNumTiles = numTiles;
}

void MovingTileGraphicsComponent::setColor(Color color) {
    this->color = color;
}

void MovingTileGraphicsComponent::update(float dt) {
    if(textures.empty() || textures[0].id == 0){
        return; // Check if the texture is loaded
    }
    int tileHeight = textures[0].height * scale; // Height of the tile texture
    int tileWidth = textures[0].width * scale; // Width of the tile texture
    float sina = sin(angle * (PI / 180.0));
    float cosa = cos(angle * (PI / 180.0));
    for(int i = 0; i < positions.size(); ++i) {
        // Update each position based on speed and angle
        positions[i].x -= speed * dt * sina * (upward ? 1 : -1);
        positions[i].y -= speed * dt * cosa * (upward ? 1 : -1);
    }
    // assert(positions.size() > 0);
    if(positions[0].y < restrictArea.y || 
        positions[0].y > restrictArea.y + restrictArea.height ||
        positions[0].x > restrictArea.x + restrictArea.width || 
        positions[0].x < restrictArea.x) {
        // If the first tile is out of the screen, remove it and add a new one at the bottom
        positions.erase(positions.begin());
        // Add a new position at the bottom of the screen
        Vector2 newPosition = { positions.back().x + sina * tileHeight * (upward ? 1 : -1), positions.back().y + cosa * tileHeight * (upward ? 1 : -1) };
        positions.push_back(newPosition);
    }
    // if(positions[0].y + textures[0].height < 0) {
    //     positions.erase(positions.begin());
    //     // Add a new position at the bottom of the screen
    //     Vector2 newPosition = { positions.back().x + sina * tileHeight, positions.back().y + cosa * tileHeight };
    //     positions.push_back(newPosition);
    // }
}

void MovingTileGraphicsComponent::render() const {
    if (textures.empty() || !isVisible() || textures[0].id == 0) return; // Check if the texture is loaded

    for (const auto& pos : positions) {
        for(const auto& texture : textures){
            Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
            Rectangle dest = { pos.x, pos.y, texture.width * scale, texture.height * scale };
            Vector2 origin = { 0, 0 };
            float rotation = -angle;
            DrawTexturePro(texture, source, dest, origin, rotation, color);
        }
    }
}