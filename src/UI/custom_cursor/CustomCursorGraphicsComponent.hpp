#ifndef CUSTOM_CURSOR_GRAPHICS_COMPONENT_HPP
#define CUSTOM_CURSOR_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include <raylib.h>

class CustomCursorGraphicsComponent : public GraphicsComponent {
public:
    CustomCursorGraphicsComponent();
    virtual ~CustomCursorGraphicsComponent();

    void loadNormalTexture(const std::string& texturePath);
    void loadClickTexture(const std::string& texturePath);
    void render() const override;
private:
    Texture2D normalCursorTexture;
    Texture2D clickCursorTexture;

    bool isNormalLoaded = false;
    bool isClickLoaded = false;
};

#endif // CUSTOM_CURSOR_GRAPHICS_COMPONENT_HPP