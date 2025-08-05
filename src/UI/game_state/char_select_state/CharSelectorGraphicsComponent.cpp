#include "CharSelectorGraphicsComponent.hpp"
#include "CharSelector.hpp"
#include <iostream>

CharSelectorGraphicsComponent::CharSelectorGraphicsComponent(CharSelector& charSelector)
    : GraphicsComponent(), charSelector(charSelector), startPosition({0, 0}), direction({1, 0}) {
        setLayer(100);
    }

void CharSelectorGraphicsComponent::setStartPosition(Vector2 position) {
    startPosition = position;
}

void CharSelectorGraphicsComponent::setDirection(Vector2 dir) {
    direction = dir;
}

void CharSelectorGraphicsComponent::loadSelectionCursorTexture(const std::string& texturePath) {
    selectionCursorTexture = LoadTexture(texturePath.c_str());
}

void CharSelectorGraphicsComponent::setAngleRotate(float angle) {
    angleRotate = angle;
}

void CharSelectorGraphicsComponent::setOriginRotate(bool upper, bool left) {
    originRotate.x = left ? 0 : selectionCursorTexture.width;
    originRotate.y = upper ? 0 : selectionCursorTexture.height;
}

void CharSelectorGraphicsComponent::unloadTextures() {
    if (selectionCursorTexture.id != 0) {
        UnloadTexture(selectionCursorTexture);
        selectionCursorTexture = {0};
    }
}

void CharSelectorGraphicsComponent::render() const {
    // Render the character selector graphics here
    Vector2 positionToDraw = {
        startPosition.x + direction.x * charSelector.getCurrentSelection(),
        startPosition.y + direction.y * charSelector.getCurrentSelection()
    };
    float t = GetTime();
    float brightness = 0.85f + 0.15f * sin(t * 5.0f); // dao động giữa 0.0 ↔ 1.0
    Color tint = {
        (unsigned char)(255 * brightness), // Red
        (unsigned char)(255 * brightness), // Green
        (unsigned char)(255 * brightness), // Blue
        255 // Alpha
    };

    DrawTexturePro(
        selectionCursorTexture,
        {0, 0, (float)selectionCursorTexture.width, (float)selectionCursorTexture.height},
        {positionToDraw.x, positionToDraw.y, (float)selectionCursorTexture.width / 2.0f, (float)selectionCursorTexture.height / 2.0f},
        originRotate,
        angleRotate,
        tint
    );

}
