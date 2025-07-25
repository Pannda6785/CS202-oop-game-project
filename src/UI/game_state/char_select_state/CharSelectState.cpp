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
    movingTileEffect[0].loadTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[1].loadTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[0].init({500, 0}, 10.0f, 100.0f, 9);
    movingTileEffect[1].init({550, 0}, 6.0f, 120.0f, 10);

    characterSelectArtwork.addTexture("../assets/UI_sprites/charselect_mid_1.png");
    characterSelectArtwork.setPosition(GetScreenWidth() / 2 - characterSelectArtwork.getWidth() / 2, 0);
    characterSelectArtwork.setLayer(50);

    float deltaX = 33.0f;
    float deltaY = 90.0f;

    Vector2 startPositionLeft = {960.0f, 165.0f};
    Vector2 startPositionRight = {960.0f, 90.0f};

    charSelectorLeft.init(selectOptions);
    charSelectorLeft.loadSelectionCursorTexture("../assets/UI_sprites/charselect_selector_left.png");
    charSelectorLeft.setSide(true);
    charSelectorLeft.setPosition(startPositionLeft);
    charSelectorLeft.setDirection({-deltaX, deltaY});
    charSelectorLeft.setAngleRotate(-30.0f);

    charSelectorRight.init(selectOptions);
    charSelectorRight.loadSelectionCursorTexture("../assets/UI_sprites/charselect_selector_right.png");
    charSelectorRight.setSide(false);
    charSelectorRight.setPosition(startPositionRight);
    charSelectorRight.setDirection({-deltaX, deltaY});
    charSelectorRight.setAngleRotate(-30.0f);

}

void CharSelectState::update(float dt) {
    for(int i = 0; i < 2; i++){
        movingTileEffect[i].update(dt);
    }
    charSelectorLeft.update(dt);
    charSelectorRight.update(dt);
}

void CharSelectState::exit() {
    for(int i = 0; i < 2; i++) {
        movingTileEffect[i].unloadTextures();
    }
    characterSelectArtwork.unloadTextures();
    charSelectorLeft.unloadTextures();
    charSelectorRight.unloadTextures();
}