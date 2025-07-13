#include "ButtonManager.hpp"
#include <raylib.h>

ButtonManager::ButtonManager() : hoveredIndex(-1) {}

ButtonManager::~ButtonManager() {
    reset();
}

void ButtonManager::addButton(std::unique_ptr<Button> button) {
    buttons.push_back(std::move(button));
    // If this is the first enabled button, set hoveredIndex
    if (hoveredIndex == -1 && buttons.back()->isEnabled()) {
        hoveredIndex = static_cast<int>(buttons.size()) - 1;
    }
}

void ButtonManager::update(float dt) {
    // 1. Update all buttons (logic, mouse state)
    for(size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i]->isEnabled()) {
            buttons[i]->update(dt);
        }
    }

    // 2. Mouse hover: update hoveredIndex if mouse is over any button
    updateHoveredByMouse();

    // 3. Keyboard navigation
    updateHoveredByKeyboard();
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
            break;
        }
    }
    if(found){
        if (hoveredIndex != prevHovered) {
            // If hoveredIndex changed, update states
            if (prevHovered != -1 && prevHovered < (int)buttons.size()) {
                buttons[prevHovered]->setToState("idle");
            }
            buttons[hoveredIndex]->setToState("hovered");
        }
    }

    // If mouse leaves all buttons, hoveredIndex is preserved (do nothing)
}

void ButtonManager::updateHoveredByKeyboard() {
    if (buttons.empty()) return;

    int prevHovered = hoveredIndex;

    // Navigation: UP/DOWN
    if (IsKeyPressed(KEY_UP)) {
        int idx = hoveredIndex;
        int next = findNextEnabled(idx, -1);
        if (next != -1) hoveredIndex = next;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        int idx = hoveredIndex;
        int next = findNextEnabled(idx, 1);
        if (next != -1) hoveredIndex = next;
    }
    buttons[prevHovered]->setToState("idle");
    buttons[hoveredIndex]->setToState("hovered");
    if(prevHovered != hoveredIndex) buttons[hoveredIndex]->triggerHoverEnter();
    // ENTER triggers the current button
    if (hoveredIndex != -1 && IsKeyPressed(KEY_ENTER)) {
        triggerCurrentButton();
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