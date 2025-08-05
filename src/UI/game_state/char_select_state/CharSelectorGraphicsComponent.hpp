#ifndef CHAR_SELECTOR_GRAPHICS_COMPONENT_HPP
#define CHAR_SELECTOR_GRAPHICS_COMPONENT_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>

class CharSelector;

class CharSelectorGraphicsComponent : public GraphicsComponent {
public:
    CharSelectorGraphicsComponent(CharSelector& charSelector);
    void render() const override;
    void setStartPosition(Vector2 position);
    void setDirection(Vector2 dir);
    void setAngleRotate(float angle);
    void setOriginRotate(bool upper, bool left);
    void loadSelectionCursorTexture(const std::string& texturePath);
    void unloadTextures();

private:
    CharSelector& charSelector;
    Vector2 startPosition;
    Vector2 direction;
    Texture selectionCursorTexture = {0};
    float angleRotate;
    Vector2 originRotate;

};

#endif // CHAR_SELECTOR_GRAPHICS_COMPONENT_HPP