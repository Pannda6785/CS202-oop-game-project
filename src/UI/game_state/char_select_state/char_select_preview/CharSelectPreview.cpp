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
        mainPortrait.setScale(0.37f);
        mainPortraitPosition = getSymetricPos(mainPortraitPosition);
        mainPortraitPosition.x -= mainPortrait.getWidth();
        mainPortrait.setFlip(true);

        idleAnimPreview.setScale(0.45f);
        idleAnimPreviewPosition = getSymetricPos(idleAnimPreviewPosition);
        idleAnimPreviewPosition.x -= idleAnimPreview.getWidth();
        idleAnimPreview.setFlip(true);
        
        charNamePosition = getSymetricPos(charNamePosition);
        charNamePosition.x -= charName.getWidth();
        
        ribbonBackgroundRect = {GetScreenWidth() / 2.0f, (float)GetScreenHeight() - belowBackgroundHeight - ribbonBackgroundHeight, (float)GetScreenWidth() / 2.0f, ribbonBackgroundHeight};
        
        backgroundRect = {GetScreenWidth() / 2.0f, 0.0f, GetScreenWidth() / 2.0f, GetScreenHeight() * 1.0f};
        
        for(int i = 0; i < 3; i++){
            backgroundTilesPosition[i] = getSymetricPos(backgroundTilesPosition[i]);
            backgroundTilesAngle[i] = 180.0f - backgroundTilesAngle[i];
        }
    }

    mainPortrait.setMiddle(true);
    mainPortrait.setScale(0.37f);
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
    belowBackground.setBackgroundRect({isLeft ? 0 : GetScreenWidth() / 2.0f, (float)GetScreenHeight() - belowBackgroundHeight, (float)GetScreenWidth() / 2.0f, belowBackgroundHeight});
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
        backgroundTiles[i].setRestrictArea({isLeft ? 0 : (float)GetScreenWidth() / 2.0f, 0, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
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
        frontTile.setRestrictArea({-100, 0, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
    } else{
        frontTile.setRestrictArea({(float)GetScreenWidth() / 2.0f, 0, GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
    }
    frontTile.setInitialNumTiles(isLeft ? 8 : 10);
    frontTile.setStartPosition({ribbonBackgroundRect.x, (float)GetScreenHeight() - 22.0f});
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
        assert(checkFadeIn);
    }
    for(int i = 0; i < 3; i++){
        if(mainPortrait.finishedFadeIn()) {
            backgroundTiles[i].setStartExpand(true);
            // if(debugFlag && !out){
            //     out = true;
            //     std::cout << "HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAH" << std::endl;
            // }
        }
        backgroundTiles[i].update(dt);
        if(backgroundTiles[i].getStartExpand()) {
            float ratioRect = 0.6f;
            Vector2 size = {1000.0f, backgroundTiles[i].getTileWidth() * ratioRect};
            Vector2 pos = backgroundTiles[i].getMiddlePostion();
            movingTileBackground[i].setBackgroundRect({pos.x, pos.y, size.x, size.y});
            movingTileBackground[i].setOriginMiddle();
            if(debugFlag && !out){
                out = true;
                std::cout << "HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAH" << std::endl;
            }
        } 
    }
    frontTile.update(dt);
}

Vector2 CharSelectPreview::getSymetricPos(Vector2 pos) {
    float dx = GetScreenWidth() / 2.0f - pos.x;
    return {GetScreenWidth() / 2.0f + dx, pos.y};
}