#include "CharSelector.hpp"

CharSelector::CharSelector() : graphic(*this), currentSelection(0), changeSelection(false) {}
CharSelector::~CharSelector() = default;

int CharSelector::getCurrentSelection() const {
    return currentSelection;
}

bool CharSelector::getChangeSelection() const {
    return changeSelection;
}

void CharSelector::init(std::vector<std::string> options) {
    characterOptions = options;
    currentSelection = 0;
    lockSelect = false;
    isLeftSide = true; // Default to left side
    graphic.setStartPosition({0, 0});
    graphic.setDirection({1, 0});
    graphic.setAngleRotate(0.0f);
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

void CharSelector::loadSelectionCursorTexture(const std::string& texturePath) {
    graphic.loadSelectionCursorTexture(texturePath);
}

void CharSelector::unloadTextures() {
    graphic.unloadTextures();
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
        lockSelect = true; // Lock selection to prevent multiple confirmations
    }
    changeSelection = change;
}