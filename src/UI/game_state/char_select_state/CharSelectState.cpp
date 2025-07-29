#include "CharSelectState.hpp"
#include "../GameStateManager.hpp"
#include <iostream>

CharSelectState::CharSelectState(GameStateManager& gsm)
    : gameStateManager(gsm), charSelectorLeft(), charSelectorRight() {
    enter();
}

CharSelectState::~CharSelectState() {
    exit();
}

void CharSelectState::enter() {
    movingTileEffect[0].addTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[1].addTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[0].setScale(0.75f);
    movingTileEffect[1].setScale(0.75f);
    movingTileEffect[0].setUpward(false);
    movingTileEffect[0].setRestrictArea({0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() + 100});
    movingTileEffect[1].setRestrictArea({0.0f, -100.0f, (float)GetScreenWidth(), (float)GetScreenHeight() + 100.0f});
    movingTileEffect[0].init({680.0f, GetScreenHeight() * 1.0f}, 10.0f, 100.0f, 9);
    movingTileEffect[1].init({550.0f, 0.0f}, 6.0f, 120.0f, 10);


    float characterSelectArtworkScale = 0.97f;
    characterSelectArtwork.addTexture("../assets/UI_sprites/charselect_mid_1.png");
    characterSelectArtwork.setPosition(GetScreenWidth() / 2 - characterSelectArtwork.getWidth() * characterSelectArtworkScale / 2, 0);
    characterSelectArtwork.setLayer(50);
    characterSelectArtwork.setScale(characterSelectArtworkScale);

    float deltaX = 33.0f * characterSelectArtworkScale;
    float deltaY = 90.0f * characterSelectArtworkScale;

    Vector2 startPositionLeft = {960.0f, 165.0f};
    Vector2 startPositionRight = {950.0f, 90.0f};

    charSelectorLeft.init(selectOptions);
    charSelectorLeft.loadSelectionCursorTexture("../assets/UI_sprites/charselect_selector_left.png");
    charSelectorLeft.setSide(true);
    charSelectorLeft.setPosition(startPositionLeft);
    charSelectorLeft.setDirection({-deltaX, deltaY});
    charSelectorLeft.setAngleRotate(-30.0f);
    charSelectorRight.setLayer(60);

    charSelectorRight.init(selectOptions);
    charSelectorRight.loadSelectionCursorTexture("../assets/UI_sprites/charselect_selector_right.png");
    charSelectorRight.setSide(false);
    charSelectorRight.setPosition(startPositionRight);
    charSelectorRight.setDirection({-deltaX, deltaY});
    charSelectorRight.setAngleRotate(-30.0f);
    charSelectorRight.setLayer(60);

    charSelectPreviewManager.init(true); // Initialize with left side by default
}

void CharSelectState::update(float dt) {
    for(int i = 0; i < 2; i++){
        movingTileEffect[i].update(dt);
    }
    charSelectorLeft.update(dt);
    charSelectorRight.update(dt);
    if(charSelectorLeft.getChangeSelection()){
        charSelectPreviewManager.setPreview("Silent Redhood", true);
    }
    charSelectPreviewManager.update(dt);
}

void CharSelectState::exit() {
    for(int i = 0; i < 2; i++) {
        movingTileEffect[i].unloadTextures();
    }
    characterSelectArtwork.unloadTextures();
    charSelectorLeft.unloadTextures();
    charSelectorRight.unloadTextures();
}