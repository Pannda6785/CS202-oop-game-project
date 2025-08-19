#include "MovingTextTileBuilder.hpp"
#include <iostream>

MovingTextTileBuilder::MovingTextTileBuilder() {
    reset();
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileTexture(const std::string& texturePath) {
    textTile->setTileTexture(texturePath);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileStartPosition(Vector2 startPosition) {
    textTile->setTileStartPosition(startPosition);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileSpeed(float speed) {
    textTile->setTileSpeed(speed);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileAngle(float angle) {
    textTile->setTileAngle(angle);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileUpward(bool upward) {
    textTile->setTileUpward(upward);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileRestrictArea(Rectangle area) {
    textTile->setTileRestrictArea(area);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileScale(float scale) {
    textTile->setTileScale(scale);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileInitialNum(int numTiles) {
    textTile->setTileInitialNum(numTiles);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileColor(Color color) {
    textTile->setTileColor(color);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileExpandingTime(float time) {
    textTile->setTileExpandingTime(time);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTileStartExpand(bool startExpand) {
    textTile->setTileStartExpand(startExpand);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withText(const std::string& text) {
    textTile->setText(text);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTextFont(const std::string& fontPath) {
    textTile->setTextFont(fontPath);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTextFontSize(int size) {
    textTile->setTextFontSize(size);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTextColor(Color color) {
    textTile->setTextColor(color);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTextSpacing(float spacing) {
    textTile->setTextSpacing(spacing);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withTextSpeed(float speed) {
    textTile->setTextSpeed(speed);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withBackgroundColor(Color color) {
    textTile->setBackgroundColor(color);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withBackgroundWidthRatio(float ratio) {
    textTile->setBackgroundWidthRatio(ratio);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withLayer(int layer) {
    textTile->setLayer(layer);
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withCharacterNamePreset(const std::string& characterName) {
    // Default settings for character name ribbon
    withTileTexture("../assets/UI_sprites/ribbon/ribbon_mid.png");
    withTileScale(0.75f);
    withTileAngle(10.0f);
    withTileSpeed(75.0f);
    withTileInitialNum(20);
    withTileExpandingTime(1.0f);
    
    withBackgroundColor(WHITE);
    
    withText(characterName);
    withTextFont("../assets/fonts/18thCentury.ttf");
    withTextFontSize(42);
    withTextColor(BLACK);
    withTextSpacing(15.0f);

    withLayer(10);
    
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withGameTitlePreset() {
    // Default settings for game title ribbon
    withTileTexture("../assets/UI_sprites/ribbon/ribbon_large.png");
    withTileScale(1.0f);
    withTileAngle(0.0f);
    withTileSpeed(50.0f);
    withTileInitialNum(15);
    withTileExpandingTime(2.0f);
    
    withBackgroundColor({255, 215, 0, 255}); // Gold color
    
    withText("ELEMENTAL DUEL");
    withTextFont("../assets/fonts/18thCentury.ttf");
    withTextFontSize(72);
    withTextColor(BLACK);
    withTextSpacing(25.0f);
    
    withLayer(20);
    
    return *this;
}

MovingTextTileBuilder& MovingTextTileBuilder::withVersusPreset() {
    // Default settings for versus text ribbon
    withTileTexture("../assets/UI_sprites/ribbon/ribbon_small.png");
    withTileScale(0.6f);
    withTileAngle(-15.0f);
    withTileSpeed(100.0f);
    withTileInitialNum(10);
    withTileExpandingTime(0.8f);
    
    withBackgroundColor({180, 0, 0, 255}); // Dark red
    
    withText("VS");
    withTextFont("../assets/fonts/18thCentury.ttf");
    withTextFontSize(60);
    withTextColor(WHITE);
    withTextSpacing(10.0f);
    withTextSpeed(-100.0f);

    withLayer(15);
    
    return *this;
}

std::unique_ptr<MovingTextTile> MovingTextTileBuilder::build() {
    std::unique_ptr<MovingTextTile> result = std::move(textTile);
    result->init();
    reset();
    return result;
}

void MovingTextTileBuilder::reset() {
    textTile = std::make_unique<MovingTextTile>();
}