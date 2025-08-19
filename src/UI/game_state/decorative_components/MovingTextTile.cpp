#include "MovingTextTile.hpp"
#include <iostream>

MovingTextTile::MovingTextTile() :backgroundWidthRatio(1.0f), 
                                  backgroundHeightRatio(0.6f),
                                  initialized(false) {
}

MovingTextTile::~MovingTextTile() = default;

void MovingTextTile::setTileTexture(const std::string& texturePath) {
    movingTile.addTexture(texturePath);
}

void MovingTextTile::setTileStartPosition(Vector2 startPosition) {
    movingTile.setStartPosition(startPosition);
    movingText.setStartPosition(startPosition);
}

void MovingTextTile::setTileSpeed(float speed) {
    movingTile.setSpeed(speed);
}

void MovingTextTile::setTileAngle(float angle) {
    movingTile.setAngle(angle);
    movingText.setAngle(angle);
    background.setAngle(90 - angle);
}

void MovingTextTile::setTileUpward(bool upward) {
    movingTile.setUpward(upward);
    movingText.setUpward(upward);
}

void MovingTextTile::setTileRestrictArea(Rectangle area) {
    movingTile.setRestrictArea(area);
    movingText.setRestrictArea(area);
}

void MovingTextTile::setTileScale(float scale) {
    movingTile.setScale(scale);
}

void MovingTextTile::setTileInitialNum(int numTiles) {
    movingTile.setInitialNumTiles(numTiles);
    movingText.setInitialNumTexts(numTiles);
}

void MovingTextTile::setTileColor(Color color) {
    movingTile.setColor(color);
}

void MovingTextTile::setTileExpandingTime(float time) {
    movingTile.setExpandingTime(time);
}

void MovingTextTile::setTileStartExpand(bool startExpand) {
    movingTile.setStartExpand(startExpand);
}

void MovingTextTile::setText(const std::string& text) {
    movingText.setText(text);
}

void MovingTextTile::setTextFont(const std::string& fontPath) {
    movingText.loadFont(fontPath);
}

void MovingTextTile::setTextFontSize(int size) {
    movingText.setFontSize(size);
}

void MovingTextTile::setTextColor(Color color) {
    movingText.setTextColor(color);
}

void MovingTextTile::setTextSpacing(float spacing) {
    movingText.setTextSpacing(spacing);
}

void MovingTextTile::setTextSpeed(float speed) {
    movingText.setSpeed(speed);
}

void MovingTextTile::setBackgroundColor(Color color) {
    background.setBackgroundColor(color);
}

void MovingTextTile::setBackgroundWidthRatio(float ratio) {
    backgroundWidthRatio = ratio;
}

void MovingTextTile::setLayer(int layer) {
    baseLayer = layer;
    movingTile.setLayer(layer);
    background.setLayer(layer + 1);
    movingText.setLayer(layer + 2);
}

void MovingTextTile::setVisible(bool visible) {
    movingTile.setVisible(visible);
    background.setVisible(visible);
    movingText.setVisible(visible);
}

bool MovingTextTile::isExpanded() const {
    return movingTile.getStartExpand() && movingTile.getRatio() >= 0.9f;
}

Vector2 MovingTextTile::getMiddlePosition() const {
    return movingTile.getMiddlePosition();
}

void MovingTextTile::init() {
    // Initialize the components
    movingTile.init();

    // movingText.setInitialNumTexts(30);
    movingText.setStartPosition(movingTile.getMiddlePosition());
    movingText.setOriginRatio({0.5f, 0.435f});
    movingText.setSpeed(movingTile.getSpeed());
    movingText.init();
    
    initialized = true;
}

void MovingTextTile::update(float dt) {
    if (!initialized) {
        std::cerr << "MovingTextTile not initialized before update. Call init() first." << std::endl;
        return;
    }
    
    movingTile.update(dt);
    movingText.update(dt);
    
    float tileWidth = movingTile.getTileWidth();
    float width = 5000.0f;
    float height = tileWidth * backgroundHeightRatio;
    Vector2 pos = movingTile.getMiddlePosition();
    
    background.setBackgroundRect({pos.x, pos.y, width, height});
    background.setOriginMiddle();
}