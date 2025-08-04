#include "CharSelector.hpp"
#include "../../../audio/AudioManager.hpp"

CharSelector::CharSelector() : graphic(*this), currentSelection(0), changeSelection(false) {}
CharSelector::~CharSelector() = default;

void CharSelector::loadTexture(const std::string& texturePath) {
    graphic.loadTexture(texturePath);
}

void CharSelector::unloadTextures() {
    graphic.unloadTextures();
}

void CharSelector::setOptions(const std::vector<std::string>& options) {
    characterOptions = options;
}

void CharSelector::setKeyUp(int raylibKey) {
    inputInterpreter.setKeyMapping(Unit::Input::MoveUp, raylibKey);
}

void CharSelector::setKeyDown(int raylibKey) {
    inputInterpreter.setKeyMapping(Unit::Input::MoveDown, raylibKey);
}

void CharSelector::setKeyConfirm(int raylibKey) {
    inputInterpreter.setKeyMapping(Unit::Input::Confirm, raylibKey);
}

void CharSelector::setSide(bool isLeft) {
    isLeftSide = isLeft;
    inputInterpreter.setKeyMapping(Unit::Input::MoveUp, isLeft ? KEY_UP : KEY_W);
    inputInterpreter.setKeyMapping(Unit::Input::MoveDown, isLeft ? KEY_DOWN : KEY_S);
    inputInterpreter.setKeyMapping(Unit::Input::Confirm, isLeft ? KEY_ENTER : KEY_J);
    graphic.setOriginRotate(!isLeft, !isLeft);
}

void CharSelector::setPosition(Vector2 position) {
    graphic.setStartPosition(position);
}

void CharSelector::setDirection(Vector2 dir) {
    graphic.setDirection(dir);
}

void CharSelector::setAngleRotate(float angle) {
    graphic.setAngleRotate(angle);
}

void CharSelector::setLayer(int layer) {
    graphic.setLayer(layer);
}

int CharSelector::getCurrentSelection() const {
    return currentSelection;
}

bool CharSelector::getChangeSelection() const {
    return changeSelection;
}

bool CharSelector::isLocked() const {
    return lockSelect;
}

void CharSelector::update(float dt) {
    inputInterpreter.update(dt);
    bool change = false;
    if (inputInterpreter.isInputPressed(Unit::Input::MoveUp) && !lockSelect) {
        currentSelection = std::max(0, currentSelection - 1);
        change = true;
    }
    if (inputInterpreter.isInputPressed(Unit::Input::MoveDown) && !lockSelect) {
        currentSelection = std::min(static_cast<int>(characterOptions.size()) - 1, currentSelection + 1);
        change = true;
    }
    if (inputInterpreter.isInputPressed(Unit::Input::Confirm) && !lockSelect) {
        lockSelect = true;
        AudioManager::getInstance().playSound("ConfirmSelectChar");
    }
    changeSelection = change;
    if(change){
        AudioManager::getInstance().playSound("MenuCursor");
    }
}