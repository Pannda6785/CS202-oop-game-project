#include "MovingTileGraphicsComponent.hpp"
#include "../../../graphics/TextureManager.hpp"
#include <cmath>
#include <cassert>
#include <iostream>

MovingTileGraphicsComponent::MovingTileGraphicsComponent() = default;

MovingTileGraphicsComponent::~MovingTileGraphicsComponent() {
    unloadTextures();
}

void MovingTileGraphicsComponent::addTexture(const std::string& texturePath) {
    textures.push_back(TextureManager::instance().getTexture(texturePath));
}

void MovingTileGraphicsComponent::unloadTextures() {
}

void MovingTileGraphicsComponent::init() {
    if (textures.empty() || textures[0] == nullptr || textures[0]->id == 0) {
        return;
    }
    
    positions.clear();
    positions.push_back(startPosition);
    int numTiles = initialNumTiles;
    int tileHeight = textures[0]->height * scale;
    if(expandingTime > 0.0f){
        tileHeight *= expandingTimer / expandingTime;
    }
    float deltaX = sin(angle * (PI / 180.0)) * tileHeight;
    float deltaY = cos(angle * (PI / 180.0)) * tileHeight;
    
    for (int i = 0; i < numTiles - 1; ++i) {
        float x = startPosition.x + i * deltaX * (upward ? 1 : -1);
        float y = startPosition.y + i * deltaY * (upward ? 1 : -1);
        positions.push_back({x, y});
    }
}

void MovingTileGraphicsComponent::setStartPosition(Vector2 startPosition) {
    this->startPosition = startPosition;
}

void MovingTileGraphicsComponent::setSpeed(float speed) {
    this->speed = speed;
}

void MovingTileGraphicsComponent::setAngle(float angle) {
    this->angle = angle;
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

void MovingTileGraphicsComponent::setExpandingTime(float time) {
    expandingTime = time;
    expandingTimer = 0.4f * expandingTime;
    startExpand = false;
}

bool MovingTileGraphicsComponent::getStartExpand() const {
    return startExpand;
}

bool MovingTileGraphicsComponent::doneExpand() const {
    return expandingTimer >= expandingTime;
}

void MovingTileGraphicsComponent::setStartExpand(bool startExpand) {
    this->startExpand = startExpand;
}

// Rendered tile's width
float MovingTileGraphicsComponent::getTileWidth() const {
    if (textures.empty() || textures[0] == nullptr || textures[0]->id == 0) return 0.0f;
    float ratio = expandingTime > 0.0f ? expandingTimer / expandingTime : 1.0f;
    return textures[0]->width * scale * ratio;
}

float MovingTileGraphicsComponent::getRatio() const {
    return expandingTime > 0.0f ? expandingTimer / expandingTime : 1.0f;
}

Vector2 MovingTileGraphicsComponent::getStartPositionToDraw() const {
    return positions.empty() ? Vector2({0.0f, 0.0f}) : getPositionToDraw(positions[0], getTileWidth(), getRatio());
}

Vector2 MovingTileGraphicsComponent::getStartPosition() const {
    return positions.empty() ? Vector2({0.0f, 0.0f}) : positions[0];
}

Vector2 MovingTileGraphicsComponent::getMiddlePosition() const {
    Vector2 pos = startPosition;
    float width = getTileWidth() / getRatio();
    float dx = width / 2.0f * cos(angle * (PI / 180.0));
    float dy = width / 2.0f * sin(angle * (PI / 180.0));
    Vector2 posToDraw = { pos.x + dx, pos.y - dy};
    return posToDraw;
}

Vector2 MovingTileGraphicsComponent::getPositionToDraw(Vector2 pos, float textureWidth, float ratio) const {
    float width = textureWidth * scale;
    float dx = width / 2.0f * cos(angle * (PI / 180.0)) * (1.0f - ratio);
    float dy = width / 2.0f * sin(angle * (PI / 180.0)) * (1.0f - ratio);
    Vector2 posToDraw = { pos.x + dx, pos.y - dy};
    return posToDraw;
}

float MovingTileGraphicsComponent::getAngle() const {
    return angle;
}

float MovingTileGraphicsComponent::getSpeed() const {
    return speed;
}

void MovingTileGraphicsComponent::update(float dt) {
    if (textures.empty() || textures[0] == nullptr || textures[0]->id == 0) {
        return;
    }
    
    float ratio = expandingTime > 0.0f ? expandingTimer / expandingTime : 1.0f;
    if (ratio == 1.0f) {
        int tileHeight = textures[0]->height * scale;
        int tileWidth = textures[0]->width * scale;
        float sina = sin(angle * (PI / 180.0));
        float cosa = cos(angle * (PI / 180.0));
        for(int i = 0; i < positions.size(); ++i) {
            positions[i].x -= speed * dt * sina * (upward ? 1 : -1);
            positions[i].y -= speed * dt * cosa * (upward ? 1 : -1);
        }
        if(positions[0].y < restrictArea.y || 
            positions[0].y > restrictArea.y + restrictArea.height ||
            positions[0].x > restrictArea.x + restrictArea.width || 
            positions[0].x < restrictArea.x) {
            positions.erase(positions.begin());
            Vector2 newPosition = { positions.back().x + sina * tileHeight * (upward ? 1 : -1), positions.back().y + cosa * tileHeight * (upward ? 1 : -1) };
            positions.push_back(newPosition);
        }
    } else {
        if (!startExpand) {
            positions.clear();
            return;
        }
        expandingTimer += dt;
        if (expandingTimer >= expandingTime) {
            expandingTimer = expandingTime;
        }
        positions.clear();
        positions.push_back(startPosition);
        int numTiles = initialNumTiles;
        int tileHeight = textures[0]->height * scale * ratio;
        float deltaX = sin(angle * (PI / 180.0)) * tileHeight * ratio;
        float deltaY = cos(angle * (PI / 180.0)) * tileHeight * ratio;
        for (int i = 0; i < numTiles - 1; ++i) {
            float x = startPosition.x + i * deltaX * (upward ? 1 : -1);
            float y = startPosition.y + i * deltaY * (upward ? 1 : -1);
            positions.push_back({x, y});
        }
    }
}

void MovingTileGraphicsComponent::render() const {
    if (textures.empty() || !isVisible() || textures[0] == nullptr || textures[0]->id == 0) return;
    
    // Replace debug output with one-time warning
    static bool mismatchWarned = false;
    if (positions.size() != initialNumTiles && !mismatchWarned) {
        std::cerr << "Warning: Tile count mismatch: " << positions.size() 
                 << " vs expected " << initialNumTiles << std::endl;
        mismatchWarned = true;
    }
    
    for (const auto& pos : positions) {
        for (const auto& texture : textures) {
            if (texture == nullptr) continue;
            
            Rectangle source = { 0, 0, (float)texture->width, (float)texture->height };
            float ratio = expandingTime > 0.0f ? expandingTimer / expandingTime : 1.0f;
            Vector2 posToDraw = getPositionToDraw(pos, texture->width, ratio);
            Rectangle dest = { posToDraw.x, posToDraw.y, texture->width * scale * ratio, texture->height * scale };
            Vector2 origin = { 0, 0 };
            float rotation = -angle;
            DrawTexturePro(*texture, source, dest, origin, rotation, color);
        }
    }
}