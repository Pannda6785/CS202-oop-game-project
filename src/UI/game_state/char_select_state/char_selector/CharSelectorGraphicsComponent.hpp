#ifndef CHAR_SELECTOR_GRAPHICS_COMPONENT_HPP
#define CHAR_SELECTOR_GRAPHICS_COMPONENT_HPP

#include "../../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>

class CharSelector;

class CharSelectorGraphicsComponent : public GraphicsComponent {
public:
    CharSelectorGraphicsComponent(CharSelector& charSelector);

    void loadTexture(const std::string& texturePath);
    void unloadTextures();

    void setStartPosition(Vector2 position);
    void setDirection(Vector2 dir);
    void setAngleRotate(float angle);
    void setOriginRotate(bool upper, bool left);

    void render() const override;

private:
    CharSelector& charSelector;
    Vector2 startPosition = {0.0f, 0.0f};
    Vector2 direction = {0.0f, 0.0f};
    const Texture* selectionCursorTexture = nullptr;
    float angleRotate = 0.0f;
    Vector2 originRotate = {0.0f, 0.0f};

};

#endif // CHAR_SELECTOR_GRAPHICS_COMPONENT_HPP