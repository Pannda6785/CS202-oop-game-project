#include "CharSelectPreview.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>

CharSelectPreview::CharSelectPreview() {
    enter();
}

CharSelectPreview::~CharSelectPreview() {
    exit();
}

void CharSelectPreview::enter() {
    layers = {"background",
              "background_tile_0", 
              "background_tile_1", 
              "background_tile_2", 
              "main_portrait", 
              "ribbon_background",
              "front_tile",
              "below_background",
              "idle_anim_preview",
              "char_name"};
    if(isLeft){
        background.setBackgroundRect({0, 0, GetScreenWidth() / 2.0f, GetScreenHeight()});
    } else{
        mainPortraitPosition = {mainPortraitPosition.x + GetScreenWidth() / 2.0f, mainPortraitPosition.y};
        idleAnimPreviewPosition = {idleAnimPreviewPosition.x + GetScreenWidth() / 2.0f, idleAnimPreviewPosition.y};
        for(int i = 0; i < 3; i++){
            backgroundTilesPosition[i] = {backgroundTilesPosition[i].x + GetScreenWidth() / 2.0f, backgroundTilesPosition[i].y};
        }
        frontTilePosition = {frontTilePosition.x + GetScreenWidth() / 2.0f, frontTilePosition.y};
        charNamePosition = {charNamePosition.x + GetScreenWidth() / 2, charNamePosition.y};
        background.setBackgroundRect({GetScreenWidth() / 2.0f, 0, GetScreenWidth() / 2.0f, GetScreenHeight()});
    }
    mainPortrait.setPosition(mainPortraitPosition.x, mainPortraitPosition.y);
    mainPortrait.setScale(0.37f); // Set scale for main portrait
    mainPortrait.setLayer(getLayer("main_portrait"));
    mainPortrait.setFadeInTime(portraitFadeInTime);
    idleAnimPreview.setPosition(idleAnimPreviewPosition.x, idleAnimPreviewPosition.y);
    idleAnimPreview.setPeriod(0.28f); // Set animation period for idle animation
    idleAnimPreview.setScale(0.45f); // Set scale for idle animation
    idleAnimPreview.setLayer(getLayer("idle_anim_preview"));

    for(int i = 0; i < 3; i++){
        backgroundTiles[i].setScale(0.60f);
        backgroundTiles[i].setRestrictArea({0, 0, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
        backgroundTiles[i].setUpward(false);
        backgroundTilesLayer[i] = getLayer("background_tile_" + std::to_string(i));
        backgroundTiles[i].init(backgroundTilesPosition[i], backgroundTilesAngle[i], backgroundTilesSpeed[i], backgroundTilesLayer[i]);
    }
    
    charName.setPosition(charNamePosition.x, charNamePosition.y);
    charName.loadFont("../assets/fonts/Redressed.ttf");
    charName.setFontSize(50);
    charName.setColor(WHITE);
    charName.setLayer(getLayer("char_name"));

    background.setLayer(getLayer("background"));

    belowBackground.setLayer(getLayer("below_background"));
    belowBackground.setBackgroundRect({0, (float)GetScreenHeight() - belowBackgroundHeight, (float)GetScreenWidth() / 2.0f, belowBackgroundHeight});
    belowBackground.setBackgroundColor(BLACK);

    ribbonBackground.setLayer(getLayer("ribbon_background"));   
    ribbonBackground.setBackgroundRect(ribbonBackgroundRect);

    frontTile.setScale(0.60f);
    frontTile.addTexture("../assets/UI_sprites/side_ribbon.png");
    frontTile.setRestrictArea({-100, 0, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight()});
    std::cout << ribbonBackgroundRect.x << ' ' << ribbonBackgroundRect.y << std::endl;
    frontTile.init({ribbonBackgroundRect.x, (float)GetScreenHeight() - 22.0f}, 90.0f, 50.0f, getLayer("front_tile"));
    frontTile.setInitialNumTiles(7);
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
        backgroundTiles[i].update(dt);
    }
    frontTile.update(dt);
}

int CharSelectPreview::getLayer(std::string layerName) {
    auto it = std::find(layers.begin(), layers.end(), layerName);
    if (it != layers.end()) {
        return std::distance(layers.begin(), it) + 1;
    }
    assert(false);
    return 0; // Layer not found
}