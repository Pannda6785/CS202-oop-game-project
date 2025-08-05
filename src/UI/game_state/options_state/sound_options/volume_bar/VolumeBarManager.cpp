#include "VolumeBarManager.hpp"

VolumeBarManager::VolumeBarManager() : hoveredIndex(-1) {}

VolumeBarManager::~VolumeBarManager() {}

void VolumeBarManager::addVolumeBar(std::unique_ptr<VolumeBar> bar) {
    bars.push_back(std::move(bar));
    if (hoveredIndex == -1 && !bars.empty()) {
        hoveredIndex = 0;
    }
}

void VolumeBarManager::setHoveredIndex(int index) {
    if (index < 0 || index >= static_cast<int>(bars.size())) {
        hoveredIndex = -1;
    } else {
        hoveredIndex = index;
    }
}

void VolumeBarManager::update(float dt) {
    updateHoveredByMouse();
    updateHoveredByKeyboard();
}

void VolumeBarManager::updateHoveredByMouse() {
    if (hoveredIndex != -1 && hoveredIndex < (int)bars.size()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            Rectangle buttonRect = {bars[hoveredIndex]->getButtonView()->getX(),
                                    bars[hoveredIndex]->getButtonView()->getY(),
                                    bars[hoveredIndex]->getButtonView()->getWidth(),
                                    bars[hoveredIndex]->getButtonView()->getHeight()};
            if(buttonRect.x <= mouse.x && mouse.x <= buttonRect.x + buttonRect.width &&
               buttonRect.y <= mouse.y && mouse.y <= buttonRect.y + buttonRect.height) {
                bars[hoveredIndex]->setVolume((mouse.x - bars[hoveredIndex]->getBarRect().x) / bars[hoveredIndex]->getBarRect().width);
            }
        }
        // Mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f) {
            adjustCurrentBar(wheel * 0.05f);
        }
    }
}

void VolumeBarManager::updateHoveredByKeyboard() {
    if (bars.empty()) return;
    int prevHovered = hoveredIndex;

    // Adjust volume with LEFT/RIGHT
    if (hoveredIndex != -1) {
        if (IsKeyDown(KEY_LEFT)) {
            adjustCurrentBar(-0.01f);
        }
        if (IsKeyDown(KEY_RIGHT)) {
            adjustCurrentBar(0.01f);
        }
    }
}

void VolumeBarManager::adjustCurrentBar(float delta) {
    if (hoveredIndex >= 0 && hoveredIndex < (int)bars.size()) {
        float v = bars[hoveredIndex]->getVolume();
        bars[hoveredIndex]->setVolume(v + delta);
    }
}

void VolumeBarManager::reset() {
    bars.clear();
    hoveredIndex = -1;
}

int VolumeBarManager::getHoveredIndex() const {
    return hoveredIndex;
}

int VolumeBarManager::getBarCount() const {
    return static_cast<int>(bars.size());
}

VolumeBar* VolumeBarManager::getBar(int idx) {
    if (idx < 0 || idx >= (int)bars.size()) return nullptr;
    return bars[idx].get();
}