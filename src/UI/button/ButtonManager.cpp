#include "ButtonManager.hpp"
#include "../../input/InputInterpreterManager.hpp"
#include <raylib.h>
#include <iostream>

ButtonManager::ButtonManager() : hoveredIndex(-1), isTriggerCurrentButton(false) {
}

ButtonManager::~ButtonManager() {
}

void ButtonManager::addButton(std::unique_ptr<Button> button) {
    buttons.push_back(std::move(button));
    if (hoveredIndex == -1 && buttons.back()->isEnabled()) {
        hoveredIndex = 0;
        buttons[hoveredIndex]->setToState("hovered");
    }
}

void ButtonManager::update(float dt) {
    for(size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i]->isEnabled()) {
            buttons[i]->update(dt);
        }
    }

    updateHoveredByMouse();

    updateHoveredByKeyboard();

    if (hoveredIndex != -1 && isTriggerCurrentButton) {
        triggerCurrentButton();
        isTriggerCurrentButton = false;
    }
}

void ButtonManager::updateHoveredByMouse() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    bool found = false;
    int prevHovered = hoveredIndex;
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i]->isEnabled() &&
            CheckCollisionPointRec({(float)mouseX, (float)mouseY}, buttons[i]->getBounds())) {
            hoveredIndex = static_cast<int>(i);
            found = true;
            isTriggerCurrentButton = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            break;
        }
    }
    if(found){
        if (hoveredIndex != prevHovered) {
            if (prevHovered != -1 && prevHovered < (int)buttons.size()) {
                buttons[prevHovered]->setExitHovered(true);
            }
            buttons[hoveredIndex]->setEnterHovered(true);
        }
    }
}

void ButtonManager::updateHoveredByKeyboard() {
    if (buttons.empty()) return;

    int prevHovered = hoveredIndex;
    bool isMoveUp = false;
    bool isMoveDown = false;
    bool isConfirm = false;
    for(const auto &interpreter : InputInterpreterManager::getInstance().getInterpreters()){
        isMoveUp |= interpreter->isInputPressed(Unit::Input::MoveUp);
        isMoveDown |= interpreter->isInputPressed(Unit::Input::MoveDown);
        isConfirm |= interpreter->isInputPressed(Unit::Input::Confirm);
    }
    if (isMoveUp) {
        int idx = hoveredIndex;
        int next = findNextEnabled(idx, -1);
        if (next != -1) hoveredIndex = next;
    }
    if (isMoveDown) {
        int idx = hoveredIndex;
        int next = findNextEnabled(idx, 1);
        if (next != -1) hoveredIndex = next;
    }
    if(prevHovered != hoveredIndex){
        buttons[hoveredIndex]->setEnterHovered(true);
        buttons[prevHovered]->setExitHovered(true);
    }
    if (hoveredIndex != -1 && isConfirm) {
        isTriggerCurrentButton = true;
    }
}

int ButtonManager::findNextEnabled(int start, int dir) const {
    if (buttons.empty()) return -1;
    int n = static_cast<int>(buttons.size());
    int idx = start;
    for (int i = 1; i <= n; ++i) {
        int next = (idx + dir * i + n) % n;
        if (buttons[next]->isEnabled()) return next;
    }
    return -1;
}

void ButtonManager::triggerCurrentButton() {
    if (hoveredIndex >= 0 && hoveredIndex < (int)buttons.size()) {
        if (buttons[hoveredIndex]->isEnabled()) {
            buttons[hoveredIndex]->triggerOnClick();
        }
    }
}

void ButtonManager::reset() {
    for(auto& button : buttons) {
        button->getGraphicsComponent()->unload();
    }
    buttons.clear();
    hoveredIndex = -1;
}

int ButtonManager::getHoveredIndex() const {
    return hoveredIndex;
}

int ButtonManager::getButtonCount() const {
    return static_cast<int>(buttons.size());
}

Button* ButtonManager::getButton(int idx) {
    if (idx < 0 || idx >= (int)buttons.size()) return nullptr;
    return buttons[idx].get();
}

void ButtonManager::setVisible(bool visible){
    for(auto &button : buttons){
        button->getGraphicsComponent()->setVisible(visible);
    }
}