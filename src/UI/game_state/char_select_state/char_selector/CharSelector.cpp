#include "CharSelector.hpp"
#include "../../../../audio/AudioManager.hpp"

CharSelector::CharSelector() : graphic(*this), currentSelection(0), changeSelection(false) {}

CharSelector::~CharSelector(){
    unloadTextures();
}

void CharSelector::loadTexture(const std::string& texturePath) {
    graphic.loadTexture(texturePath);
}

void CharSelector::unloadTextures() {
    graphic.unloadTextures();
}

void CharSelector::setOptions(const std::vector<std::string>& options) {
    characterOptions = options;
}

void CharSelector::setSide(bool isLeft) {
    isLeftSide = isLeft;
    graphic.setOriginRotate(!isLeft, !isLeft);
}

void CharSelector::setInputInterpreter(std::shared_ptr<InputInterpreter> interpreter) {
    this->interpreter = interpreter;
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

std::shared_ptr<InputInterpreter> CharSelector::getInputInterpreter() const {
    return interpreter;
}

bool CharSelector::isLocked() const {
    return lockSelect;
}

void CharSelector::update(float dt) {
    bool change = false;
    if (interpreter && interpreter->isInputPressed(Unit::Input::MoveUp) && !lockSelect) {
        currentSelection = std::max(0, currentSelection - 1);
        change = true;
    }
    if (interpreter && interpreter->isInputPressed(Unit::Input::MoveDown) && !lockSelect) {
        currentSelection = std::min(static_cast<int>(characterOptions.size()) - 1, currentSelection + 1);
        change = true;
    }
    if (interpreter && interpreter->isInputPressed(Unit::Input::Confirm) && !lockSelect) {
        lockSelect = true;
        AudioManager::getInstance().playSound("ConfirmSelectChar");
    }
    if (interpreter && interpreter->isInputPressed(Unit::Input::Back)) {
        if(lockSelect){
            lockSelect = false;
            AudioManager::getInstance().playSound("CancelSelectChar");
        }
    }
    changeSelection = change;
    if(change){
        AudioManager::getInstance().playSound("MenuCursor");
    }
}