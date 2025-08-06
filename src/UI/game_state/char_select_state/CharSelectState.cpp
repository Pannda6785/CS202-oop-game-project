#include "CharSelectState.hpp"
#include "../GameStateManager.hpp"
#include "../versus_player_state/VersusPlayerState.hpp"
#include <iostream>

CharSelectState::CharSelectState(GameStateManager& gsm)
    : gameStateManager(gsm), charSelectorLeft(), charSelectorRight() {
    enter();
}

CharSelectState::~CharSelectState() = default;

void CharSelectState::enter() {
    LayerInfoProvider::getInstance().init();

    movingTileEffect[0].addTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[0].setScale(0.75f);
    movingTileEffect[0].setUpward(false);
    movingTileEffect[0].setRestrictArea({0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() + 100});
    movingTileEffect[0].setStartPosition({690.0f, GetScreenHeight() * 1.0f});
    movingTileEffect[0].setAngle(10.0f);
    movingTileEffect[0].setSpeed(75.0f);
    movingTileEffect[0].setLayer(LayerInfoProvider::getInstance().getLayer("middle_tile_0"));
    movingTileEffect[0].init();

    movingTileEffect[1].addTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[1].setScale(0.75f);
    movingTileEffect[1].setRestrictArea({0.0f, -100.0f, (float)GetScreenWidth(), (float)GetScreenHeight() + 100.0f});
    movingTileEffect[1].setStartPosition({580.0f, 0.0f});
    movingTileEffect[1].setAngle(6.0f);
    movingTileEffect[1].setSpeed(80.0f);
    movingTileEffect[1].setLayer(LayerInfoProvider::getInstance().getLayer("middle_tile_0"));
    movingTileEffect[1].init();


    float characterSelectArtworkScale = 0.97f;
    characterSelectArtwork.addTexture("../assets/UI_sprites/charselect_mid_1.png");
    characterSelectArtwork.setPosition(GetScreenWidth() / 2 - characterSelectArtwork.getWidth() * characterSelectArtworkScale / 2, 0);
    characterSelectArtwork.setLayer(LayerInfoProvider::getInstance().getLayer("char_select_artwork"));
    characterSelectArtwork.setScale(characterSelectArtworkScale);

    float deltaX = 33.0f * characterSelectArtworkScale;
    float deltaY = 90.0f * characterSelectArtworkScale;

    Vector2 startPositionLeft = {960.0f, 165.0f};
    Vector2 startPositionRight = {950.0f, 90.0f};

    charSelectorLeft.loadTexture("../assets/UI_sprites/charselect_selector_left.png");
    charSelectorLeft.setSide(true);
    charSelectorLeft.setPosition(startPositionLeft);
    charSelectorLeft.setDirection({-deltaX, deltaY});
    charSelectorLeft.setAngleRotate(-30.0f);
    charSelectorLeft.setLayer(LayerInfoProvider::getInstance().getLayer("selector"));
    charSelectorLeft.setOptions(selectOptions);

    charSelectorRight.loadTexture("../assets/UI_sprites/charselect_selector_right.png");
    charSelectorRight.setSide(false);
    charSelectorRight.setPosition(startPositionRight);
    charSelectorRight.setDirection({-deltaX, deltaY});
    charSelectorRight.setAngleRotate(-30.0f);
    charSelectorRight.setLayer(LayerInfoProvider::getInstance().getLayer("selector"));
    charSelectorRight.setOptions(selectOptions);

    charSelectPreviewManagerLeft.init(true);
    charSelectPreviewManagerRight.init(false);
}

void CharSelectState::update(float dt) {
    for(int i = 0; i < 2; i++){
        movingTileEffect[i].update(dt);
    }

    charSelectorLeft.update(dt);
    charSelectorRight.update(dt);

    if(charSelectorLeft.getChangeSelection()){
        std::string characterName = selectOptions[charSelectorLeft.getCurrentSelection()];
        if(characterName == "Random Select") {
            int randomIndex = GetRandomValue(0, selectOptions.size() - 2);
            if(randomIndex >= charSelectorLeft.getCurrentSelection()) randomIndex++;
            characterName = selectOptions[randomIndex];
        }
        
        if(characterName == "Sun Priestess" || 
           characterName == "Silent Redhood" ||
           characterName == "Royal Arcanist" ||
           characterName == "Hero of Frost" ||
           characterName == "Dreadwyrm Heir" ||
           characterName == "Lich of Flowers" ||
           characterName == "Depth's Secret" ||
           characterName == "Stormbeast") {
            
            charSelectPreviewManagerLeft.setPreview(characterName, true);
        } else {
            charSelectPreviewManagerLeft.setPreview("Sun Priestess", true);
        }
    }

    if(charSelectorRight.getChangeSelection()){
        std::string characterName = selectOptions[charSelectorRight.getCurrentSelection()];
        if(characterName == "Random Select") {
            int randomIndex = GetRandomValue(0, selectOptions.size() - 2); // Exclude "Random Select"
            if(randomIndex >= charSelectorRight.getCurrentSelection()) randomIndex++;
            characterName = selectOptions[randomIndex];
        }
        
        if(characterName == "Sun Priestess" || 
           characterName == "Silent Redhood" ||
           characterName == "Royal Arcanist" ||
           characterName == "Hero of Frost" ||
           characterName == "Dreadwyrm Heir" ||
           characterName == "Lich of Flowers" ||
           characterName == "Depth's Secret" ||
           characterName == "Stormbeast") {
            
            charSelectPreviewManagerRight.setPreview(characterName, false);
        } else {
            charSelectPreviewManagerRight.setPreview("Sun Priestess", false);
        }
    }

    charSelectPreviewManagerLeft.update(dt);
    charSelectPreviewManagerRight.update(dt);

    if(charSelectorLeft.isLocked() && charSelectorRight.isLocked()) {
        startGame();
    }
}

void CharSelectState::startGame(){
    std::string player1Character = selectOptions[charSelectorLeft.getCurrentSelection()];
    std::string player2Character = selectOptions[charSelectorRight.getCurrentSelection()];

    gameStateManager.changeCurrentState(std::make_unique<VersusPlayerState>(gameStateManager, player1Character, player2Character));
}

void CharSelectState::exit() {
}