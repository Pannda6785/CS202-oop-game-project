#include "CharSelectState.hpp"
#include "../GameStateManager.hpp"
#include "../versus_mode_state/VersusModeState.hpp"
#include "../../../input/InputInterpreterManager.hpp"
#include "../../../game/ai/GeneralAIInterpreter.hpp"
#include "../../../graphics/GraphicsComponentManager.hpp"
#include <algorithm>
#include <iostream>

CharSelectState::CharSelectState(GameStateManager& gsm, bool isVsPlayer)
    : gameStateManager(gsm), charSelectorLeft(), charSelectorRight(), isVsPlayer(isVsPlayer), worldBuilder(isVsPlayer) {
    enter();
}

CharSelectState::~CharSelectState() = default;

void CharSelectState::enter() {
    LayerInfoProvider::getInstance().init();

    movingTileEffect[0].addTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[0].setScale(0.75f);
    movingTileEffect[0].setUpward(false);
    movingTileEffect[0].setRestrictArea({0.0f, 0.0f, (float)GraphicsComponentManager::NATIVE_WIDTH, (float)GraphicsComponentManager::NATIVE_HEIGHT + 100});
    movingTileEffect[0].setStartPosition({690.0f, GraphicsComponentManager::NATIVE_HEIGHT * 1.0f});
    movingTileEffect[0].setAngle(10.0f);
    movingTileEffect[0].setSpeed(75.0f);
    movingTileEffect[0].setLayer(LayerInfoProvider::getInstance().getLayer("middle_tile_0"));
    movingTileEffect[0].init();

    movingTileEffect[1].addTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    movingTileEffect[1].setScale(0.75f);
    movingTileEffect[1].setRestrictArea({0.0f, -100.0f, (float)GraphicsComponentManager::NATIVE_WIDTH, (float)GraphicsComponentManager::NATIVE_HEIGHT + 100.0f});
    movingTileEffect[1].setStartPosition({580.0f, 0.0f});
    movingTileEffect[1].setAngle(6.0f);
    movingTileEffect[1].setSpeed(80.0f);
    movingTileEffect[1].setLayer(LayerInfoProvider::getInstance().getLayer("middle_tile_0"));
    movingTileEffect[1].init();


    float characterSelectArtworkScale = 0.97f;
    characterSelectArtwork.addTexture("../assets/UI_sprites/charselect_mid.png");
    characterSelectArtwork.setPosition(GraphicsComponentManager::NATIVE_WIDTH / 2 - characterSelectArtwork.getWidth() * characterSelectArtworkScale / 2, 0);
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
    if(charSelectorLeft.isLocked() && charSelectorRight.isLocked()){
        startGame();
        return;
    }

    for(int i = 0; i < 2; i++){
        movingTileEffect[i].update(dt);
    }

    registerInputInterpreter();

    for(auto const& interpreter : interpreters) {
        if(interpreter && interpreter->isInputPressed(Unit::Input::Pause)){
            gameStateManager.popState();
            return;
        }
    }

    if(!charSelectorLeft.isLocked() && charSelectorLeft.getInputInterpreter() != nullptr && charSelectorLeft.getInputInterpreter()->isInputPressed(Unit::Input::Back)){
        gameStateManager.popState();
        return;
    }

    if(!charSelectorRight.isLocked() && charSelectorRight.getInputInterpreter() != nullptr && charSelectorRight.getInputInterpreter()->isInputPressed(Unit::Input::Back)) {
        gameStateManager.popState();
        return;
    }

    charSelectorLeft.update(dt);
    charSelectorRight.update(dt);

    if(charSelectorLeft.isLocked()){
        worldBuilder.setPlayer(0, getCurrentSelectionName(selectOptions[charSelectorLeft.getCurrentSelection()]), charSelectorLeft.getInputInterpreter());
    }

    if(charSelectorRight.isLocked()){
        if(isVsPlayer) worldBuilder.setPlayer(1, getCurrentSelectionName(selectOptions[charSelectorRight.getCurrentSelection()]), charSelectorRight.getInputInterpreter());
        else{
            worldBuilder.setAI(1, getCurrentSelectionName(selectOptions[charSelectorRight.getCurrentSelection()]));
        }
    }

    if(charSelectorLeft.getChangeSelection()){
        std::string characterName = selectOptions[charSelectorLeft.getCurrentSelection()];
        charSelectPreviewManagerLeft.setPreview(characterName, true);
    }

    if(charSelectorRight.getChangeSelection()){
        std::string characterName = selectOptions[charSelectorRight.getCurrentSelection()];
        charSelectPreviewManagerRight.setPreview(characterName, false);
    }

    charSelectPreviewManagerLeft.update(dt);
    charSelectPreviewManagerRight.update(dt);
}

void CharSelectState::registerInputInterpreter(){
    if(interpreters.size() >= 2) return;
    for(const auto& interpreter : InputInterpreterManager::getInstance().getInterpreters()) {
        bool isPressed = false;
        for(int i = 0; i < static_cast<int>(Unit::Input::InputCount) && !isPressed; i++) {
            isPressed |= interpreter->isInputPressed(static_cast<Unit::Input>(i));
        }
        if(isPressed){
            bool alreadyExists = false;
            for(int i = 0; i < interpreters.size(); i++) {
                if(interpreters[i] == interpreter) {
                    alreadyExists = true;
                    break;
                }
            }
            if(!alreadyExists) {
                interpreters.push_back(interpreter);
                if(interpreters.size() == 1) charSelectorLeft.setInputInterpreter(interpreter);
                else charSelectorRight.setInputInterpreter(interpreter);
                return;
            }
        }
    }
}

std::string CharSelectState::getCurrentSelectionName(std::string currentSelection) {
    if(currentSelection == "Random Select"){
        int randomIndex = GetRandomValue(0, selectOptions.size() - 2); // Exclude "Random Select"
        if(randomIndex >= std::find(selectOptions.begin(), selectOptions.end(), currentSelection) - selectOptions.begin()) randomIndex++;
        return selectOptions[randomIndex];
    }
    return currentSelection;
}

void CharSelectState::startGame(){
    interpreters = worldBuilder.getInterpreters();
    gameStateManager.changeCurrentState(std::make_unique<VersusModeState>(gameStateManager, worldBuilder.getWorld(), interpreters));
}

void CharSelectState::exit() {
}