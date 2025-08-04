#include "CharSelectorGraphicsComponent.hpp"
#include "CharSelector.hpp"
#include <iostream>

CharSelectorGraphicsComponent::CharSelectorGraphicsComponent(CharSelector& charSelector)
    : GraphicsComponent(), charSelector(charSelector), startPosition({0.0f, 0.0f}), direction({0.0f, 0.0f}) {
        setLayer(100);
    }

void CharSelectorGraphicsComponent::loadTexture(const std::string& texturePath) {
    selectionCursorTexture = LoadTexture(texturePath.c_str());
}

void CharSelectorGraphicsComponent::unloadTextures() {
    if (selectionCursorTexture.id != 0) {
        UnloadTexture(selectionCursorTexture);
        selectionCursorTexture = {0};
    }
}

void CharSelectorGraphicsComponent::setStartPosition(Vector2 position) {
    startPosition = position;
}

void CharSelectorGraphicsComponent::setDirection(Vector2 dir) {
    direction = dir;
}

void CharSelectorGraphicsComponent::setAngleRotate(float angle) {
    angleRotate = angle;
}

void CharSelectorGraphicsComponent::setOriginRotate(bool upper, bool left) {
    originRotate.x = left ? 0 : selectionCursorTexture.width;
    originRotate.y = upper ? 0 : selectionCursorTexture.height;
}

void CharSelectorGraphicsComponent::render() const {
    Vector2 positionToDraw = {
        startPosition.x + direction.x * charSelector.getCurrentSelection(),
        startPosition.y + direction.y * charSelector.getCurrentSelection()
    };
    float t = GetTime();
    float brightness = 0.85f + 0.15f * sin(t * 5.0f);
    Color tint = {
        (unsigned char)(255 * brightness),
        (unsigned char)(255 * brightness),
        (unsigned char)(255 * brightness),
        255
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
