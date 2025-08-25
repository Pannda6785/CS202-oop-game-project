#include "CharSelectPreview.hpp"
#include "../../../../audio/AudioManager.hpp"
#include <iostream>
#include <assert.h> 
#include <algorithm>

CharSelectPreview::CharSelectPreview() {
}

// CharSelectPreview::~CharSelectPreview() {
//     exit();
// }

CharSelectPreview::~CharSelectPreview() = default;

void CharSelectPreview::enter() {
    if(!isLeft) {
        mainPortrait.setScale(mainPortraitScale);
        mainPortraitPosition = getSymetricPos(mainPortraitPosition);
        mainPortraitPosition.x -= mainPortrait.getWidth();
        mainPortrait.setFlip(false);

        idleAnimPreview.setScale(0.45f);
        idleAnimPreviewPosition = getSymetricPos(idleAnimPreviewPosition);
        idleAnimPreviewPosition.x -= idleAnimPreview.getWidth();
        idleAnimPreview.setFlip(true);
        
        charNamePosition = getSymetricPos(charNamePosition);
        charNamePosition.x -= charName.getWidth();
        
        ribbonBackgroundRect = {GraphicsComponentManager::NATIVE_WIDTH / 2.0f, (float)GraphicsComponentManager::NATIVE_HEIGHT - belowBackgroundHeight - ribbonBackgroundHeight, (float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, ribbonBackgroundHeight};
        
        backgroundRect = {GraphicsComponentManager::NATIVE_WIDTH / 2.0f, 0.0f, GraphicsComponentManager::NATIVE_WIDTH / 2.0f, GraphicsComponentManager::NATIVE_HEIGHT * 1.0f};
        
        for(int i = 0; i < 3; i++){
            backgroundTilesPosition[i] = getSymetricPos(backgroundTilesPosition[i]);
            backgroundTilesAngle[i] = 180.0f - backgroundTilesAngle[i];
        }
    }

    mainPortrait.setMiddle(true);
    mainPortrait.setScale(mainPortraitScale);
    mainPortrait.setPosition(mainPortraitPosition.x, mainPortraitPosition.y);
    mainPortrait.setLayer(LayerInfoProvider::getInstance().getLayer("main_portrait"));
    mainPortrait.setFadeInTime(portraitFadeInTime);
    
    idleAnimPreview.setMiddle(true);
    idleAnimPreview.setScale(0.45f);
    idleAnimPreview.setPosition(idleAnimPreviewPosition.x, idleAnimPreviewPosition.y);
    idleAnimPreview.setLayer(LayerInfoProvider::getInstance().getLayer("idle_anim_preview"));
    idleAnimPreview.setPeriod(0.28f);

    charName.setPosition(charNamePosition.x, charNamePosition.y);
    charName.loadFont("../assets/fonts/Redressed.ttf");
    charName.setFontSize(50);
    charName.setColor(WHITE);
    charName.setLayer(LayerInfoProvider::getInstance().getLayer("char_name"));

    background.setBackgroundRect(backgroundRect);
    background.setLayer(LayerInfoProvider::getInstance().getLayer("background"));

    belowBackground.setLayer(LayerInfoProvider::getInstance().getLayer("below_background"));
    belowBackground.setBackgroundRect({isLeft ? 0 : GraphicsComponentManager::NATIVE_WIDTH / 2.0f, (float)GraphicsComponentManager::NATIVE_HEIGHT - belowBackgroundHeight, (float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, belowBackgroundHeight});
    belowBackground.setBackgroundColor(BLACK);

    ribbonBackground.setLayer(LayerInfoProvider::getInstance().getLayer("ribbon_background"));
    ribbonBackground.setBackgroundRect(ribbonBackgroundRect);

    for(int i = 0; i < 3; i++){
        movingTileBackground[i].setLayer(LayerInfoProvider::getInstance().getLayer("tile_rect_" + std::to_string(i)));
        movingTileBackground[i].setBackgroundColor(movingTileBackgroundColor);
        if(isLeft) movingTileBackground[i].setAngle(-(90.0f + backgroundTilesAngle[i]));
        else movingTileBackground[i].setAngle(-(backgroundTilesAngle[i] - 90.0f));
    }

    for(int i = 0; i < 3; i++){
        backgroundTiles[i].setScale(0.60f);
        backgroundTiles[i].setRestrictArea({isLeft ? 0 : (float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, 0, (float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, (float)GraphicsComponentManager::NATIVE_HEIGHT});
        backgroundTiles[i].setUpward(!isLeft);
        backgroundTilesLayer[i] = LayerInfoProvider::getInstance().getLayer("background_tile_" + std::to_string(i));
        backgroundTiles[i].setExpandingTime(expandingTilesTime);
        backgroundTiles[i].setStartPosition(backgroundTilesPosition[i]);
        backgroundTiles[i].setAngle(backgroundTilesAngle[i]);
        backgroundTiles[i].setSpeed(backgroundTilesSpeed[i]);
        backgroundTiles[i].setLayer(backgroundTilesLayer[i]);
        backgroundTiles[i].init();
    }

    frontTile.setScale(0.60f);
    frontTile.addTexture("../assets/UI_sprites/side_ribbon.png");
    if(isLeft){
        frontTile.setRestrictArea({-100, 0, (float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, (float)GraphicsComponentManager::NATIVE_HEIGHT});
    } else{
        frontTile.setRestrictArea({(float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, 0, GraphicsComponentManager::NATIVE_WIDTH / 2.0f, (float)GraphicsComponentManager::NATIVE_HEIGHT});
    }
    frontTile.setInitialNumTiles(isLeft ? 8 : 10);
    frontTile.setStartPosition({ribbonBackgroundRect.x, (float)GraphicsComponentManager::NATIVE_HEIGHT - 22.0f});
    frontTile.setAngle(90.0f);
    frontTile.setSpeed(50.0f);
    frontTile.setLayer(LayerInfoProvider::getInstance().getLayer("front_tile"));
    frontTile.init();
}

void CharSelectPreview::addTextureMainPortrait(const std::string & texturePath) {
    mainPortrait.addTexture(texturePath);
}

void CharSelectPreview::addTextureIdleAnimPreview(const std::string & texturePath) {
    idleAnimPreview.addTexture(texturePath);
}

void CharSelectPreview::addTextureBackgroundTiles(int id, const std::string & texturePath) {
    if(id < 0 || id >= 3) return; // Ensure id is within bounds
    backgroundTiles[id].addTexture(texturePath);
}

void CharSelectPreview::addTextureFrontTile(const std::string & texturePath) {
    frontTile.addTexture(texturePath);
}

void CharSelectPreview::setSide(bool isLeft) {
    this->isLeft = isLeft;
}

void CharSelectPreview::setBackgroundColor(Color color) {
    background.setBackgroundColor(color);
}

void CharSelectPreview::setRibbonBackgroundColor(Color color) {
    ribbonBackground.setBackgroundColor(color);
}

void CharSelectPreview::setCharName(const std::string& text) {
    charName.setText(text);
}

void CharSelectPreview::setFrontTileColor(Color color) {
    frontTile.setColor(color);
}

void CharSelectPreview::setMovingTileBackgroundColor(Color color) {
    movingTileBackgroundColor = color;
}

void CharSelectPreview::exit() {
    // mainPortrait.unloadTextures();
    // idleAnimPreview.unloadTextures();
    // for(int i = 0; i < 3; i++){
    //     backgroundTiles[i].unloadTextures();
    // }
    // frontTile.unloadTextures();
    // charName.unloadFont();
}

void CharSelectPreview::update(float dt) {
    mainPortrait.update(dt);
    if(mainPortrait.finishedFadeIn() && !backgroundTiles[0].getStartExpand()) {
        AudioManager::getInstance().playSound("CharSelectRibbon");
    }
    if(!mainPortrait.finishedFadeIn()){
        checkFadeIn = true;
    }
    if(mainPortrait.finishedFadeIn()){
        // assert(checkFadeIn);
    }
    for(int i = 0; i < 3; i++){
        if(mainPortrait.finishedFadeIn()) {
            backgroundTiles[i].setStartExpand(true);
        }
        backgroundTiles[i].update(dt);
        if(backgroundTiles[i].getStartExpand()) {
            float ratioRect = 0.6f;
            Vector2 size = {1000.0f, backgroundTiles[i].getTileWidth() * ratioRect};
            Vector2 pos = backgroundTiles[i].getMiddlePosition();
            movingTileBackground[i].setBackgroundRect({pos.x, pos.y, size.x, size.y});
            movingTileBackground[i].setOriginMiddle();
            if(debugFlag && !out){
                out = true;
            }
        } 
    }
    frontTile.update(dt);
}

Vector2 CharSelectPreview::getSymetricPos(Vector2 pos) {
    float dx = GraphicsComponentManager::NATIVE_WIDTH / 2.0f - pos.x;
    return {GraphicsComponentManager::NATIVE_WIDTH / 2.0f + dx, pos.y};
}