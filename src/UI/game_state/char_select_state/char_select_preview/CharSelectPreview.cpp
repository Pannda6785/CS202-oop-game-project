#include "CharSelectPreview.hpp"
#include <iostream>
#include <assert.h> 
#include <algorithm>

CharSelectPreview::CharSelectPreview() {
    // enter();
}

CharSelectPreview::~CharSelectPreview() {
    exit();
}

void CharSelectPreview::enter() {
    layers = {"background",
              "background_tile_0", 
              "tile_rect_0",
              "background_tile_1", 
              "tile_rect_1",
              "background_tile_2", 
              "tile_rect_2",
              "main_portrait", 
              "ribbon_background",
              "front_tile",
              "below_background",
              "idle_anim_preview",
              "char_name"};

    mainPortrait.setMiddle(true);
    mainPortrait.setScale(0.37f); // Set scale for main portrait
    idleAnimPreview.setMiddle(true);
    idleAnimPreview.setScale(0.45f); // Set scale for idle animation

    if(isLeft){
        background.setBackgroundRect({0, 0, GetScreenWidth() / 2.0f, GetScreenHeight()});
    } else{
        background.setBackgroundRect({GetScreenWidth() / 2.0f, 0, GetScreenWidth() / 2.0f, GetScreenHeight()});
        mainPortraitPosition = getSymetricPos(mainPortraitPosition);
        mainPortraitPosition.x -= mainPortrait.getWidth();
        idleAnimPreviewPosition = getSymetricPos(idleAnimPreviewPosition);
        idleAnimPreviewPosition.x -= idleAnimPreview.getWidth();
        for(int i = 0; i < 3; i++) backgroundTilesPosition[i] = getSymetricPos(backgroundTilesPosition[i]);
        for(int i = 0; i < 3; i++) backgroundTilesAngle[i] = 180.0f - backgroundTilesAngle[i];
        charNamePosition = getSymetricPos(charNamePosition);
        charNamePosition.x -= charName.getWidth();
        ribbonBackgroundRect = {GetScreenWidth() / 2.0f, (float)GetScreenHeight() - belowBackgroundHeight - ribbonBackgroundHeight, (float)GetScreenWidth() / 2.0f, ribbonBackgroundHeight};
        mainPortrait.setFlip(true);
        idleAnimPreview.setFlip(true);
    }

    mainPortrait.setPosition(mainPortraitPosition.x, mainPortraitPosition.y);
    mainPortrait.setLayer(getLayer("main_portrait"));
    mainPortrait.setFadeInTime(portraitFadeInTime);
    
    idleAnimPreview.setPosition(idleAnimPreviewPosition.x, idleAnimPreviewPosition.y);
    idleAnimPreview.setLayer(getLayer("idle_anim_preview"));
    idleAnimPreview.setPeriod(0.28f); // Set animation period for idle animation

    for(int i = 0; i < 3; i++){
        backgroundTiles[i].setScale(0.60f);
        backgroundTiles[i].setRestrictArea({isLeft ? 0 : (float)GetScreenWidth() / 2.0f, 0, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
        backgroundTiles[i].setUpward(!isLeft);
        backgroundTilesLayer[i] = getLayer("background_tile_" + std::to_string(i));
        backgroundTiles[i].setExpandingTime(expandingTilesTime);
        backgroundTiles[i].init(backgroundTilesPosition[i], backgroundTilesAngle[i], backgroundTilesSpeed[i], backgroundTilesLayer[i]);
    }

    for(int i = 0; i < 3; i++){
        movingTileBackground[i].setLayer(getLayer("tile_rect_" + std::to_string(i)));
        movingTileBackground[i].setBackgroundColor(MovingTileBackgroundColor);
        if(isLeft) movingTileBackground[i].setAngle(-(90.0f + backgroundTilesAngle[i]));
        else movingTileBackground[i].setAngle(-(backgroundTilesAngle[i] - 90.0f));
    }
    
    charName.setPosition(charNamePosition.x, charNamePosition.y);
    charName.loadFont("../assets/fonts/Redressed.ttf");
    charName.setFontSize(50);
    charName.setColor(WHITE);
    charName.setLayer(getLayer("char_name"));

    background.setLayer(getLayer("background"));

    belowBackground.setLayer(getLayer("below_background"));
    belowBackground.setBackgroundRect({isLeft ? 0 : GetScreenWidth() / 2.0f, (float)GetScreenHeight() - belowBackgroundHeight, (float)GetScreenWidth() / 2.0f, belowBackgroundHeight});
    belowBackground.setBackgroundColor(BLACK);

    ribbonBackground.setLayer(getLayer("ribbon_background"));
    ribbonBackground.setBackgroundRect(ribbonBackgroundRect);

    frontTile.setScale(0.60f);
    frontTile.addTexture("../assets/UI_sprites/side_ribbon.png");
    if(isLeft){
        frontTile.setRestrictArea({-100, 0, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
    } else{
        frontTile.setRestrictArea({(float)GetScreenWidth() / 2.0f, 0, GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
    }
    frontTile.setInitialNumTiles(isLeft ? 6 : 9);
    frontTile.init({ribbonBackgroundRect.x, (float)GetScreenHeight() - 22.0f}, 90.0f, 50.0f, getLayer("front_tile"));
}

void CharSelectPreview::setSide(bool isLeft) {
    this->isLeft = isLeft;
}

void CharSelectPreview::addTextureMainPortrait(const std::string & texturePath) {
    mainPortrait.addTexture(texturePath);
    mainPortrait.setPosition(mainPortraitPosition.x, mainPortraitPosition.y);
}

void CharSelectPreview::addTextureIdleAnimPreview(const std::string & texturePath) {
    idleAnimPreview.addTexture(texturePath);
    idleAnimPreview.setPosition(idleAnimPreviewPosition.x, idleAnimPreviewPosition.y);
}

void CharSelectPreview::addTextureBackgroundTiles(int id, const std::string & texturePath) {
    if(id < 0 || id >= 3) return; // Ensure id is within bounds
    backgroundTiles[id].addTexture(texturePath);
}

void CharSelectPreview::addTextureFrontTile(const std::string & texturePath) {
    frontTile.addTexture(texturePath);
}

void CharSelectPreview::setBackgroundColor(Color color) {
    background.setBackgroundColor(color);
}

void CharSelectPreview::setRibbonBackgroundColor(Color color) {
    ribbonBackground.setBackgroundColor(color);
}

void CharSelectPreview::setCharName(const std::string& text) {
    charName.setText(text);
    charName.setPosition(charNamePosition.x, charNamePosition.y);
}

void CharSelectPreview::setFrontTileColor(Color color) {
    frontTile.setColor(color);
}

void CharSelectPreview::setMovingTileBackgroundColor(Color color) {
    MovingTileBackgroundColor = color;
}

void CharSelectPreview::exit() {
    mainPortrait.unloadTextures();
    idleAnimPreview.unloadTextures();
    for(int i = 0; i < 3; i++){
        backgroundTiles[i].unloadTextures();
    }
    frontTile.unloadTextures();
    charName.unloadFont();
}

void CharSelectPreview::update(float dt) {
    mainPortrait.update(dt);
    for(int i = 0; i < 3; i++){
        if(mainPortrait.finishedFadeIn()) {
            backgroundTiles[i].setStartExpand(true);
        }
        backgroundTiles[i].update(dt);
        if(backgroundTiles[i].getStartExpand()) {
            float ratioRect = 0.6f;
            Vector2 size = {1000.0f, backgroundTiles[i].getTileWidth() * ratioRect};
            Vector2 pos = backgroundTiles[i].getMiddlePostion();
            movingTileBackground[i].setBackgroundRect({pos.x, pos.y, size.x, size.y});
            movingTileBackground[i].setOriginMiddle();
        } 
    }
    frontTile.update(dt);
}

int CharSelectPreview::getLayer(std::string layerName) {
    auto it = std::find(layers.begin(), layers.end(), layerName);
    if (it != layers.end()) {
        return std::distance(layers.begin(), it);
    }
    assert(false);
    return 0; // Layer not found
}

Vector2 CharSelectPreview::getSymetricPos(Vector2 pos) {
    float dx = GetScreenWidth() / 2.0f - pos.x;
    return {GetScreenWidth() / 2.0f + dx, pos.y};
}