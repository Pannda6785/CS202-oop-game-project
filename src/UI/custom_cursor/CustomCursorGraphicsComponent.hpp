#ifndef CUSTOM_CURSOR_GRAPHICS_COMPONENT_HPP
#define CUSTOM_CURSOR_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <vector>

class CustomCursorGraphicsComponent : public GraphicsComponent {
public:
    CustomCursorGraphicsComponent();
    virtual ~CustomCursorGraphicsComponent();

    void loadNormalTexture(const std::string& texturePath);
    void loadClickTexture(const std::string& texturePath);
    void loadArroundDotTexture(const std::string& texturePath);
    void render() const override;
    void update(float dt);
private:
    Texture2D normalCursorTexture;
    Texture2D clickCursorTexture;
    Texture2D arroundDotTexture;
    float arroundDotTime = 0.8f;
    int maxArroundDots = 10;
    float spawnTime = 0.1f;
    float spawnTimer = 0.0f;
    std::vector<std::pair<std::pair<Vector2, Vector2>, float>> arroundDots; // Store positions and times of focus dots

    bool isNormalLoaded = false;
    bool isClickLoaded = false;
    bool isArroundDotLoaded = false;
};

#endif // CUSTOM_CURSOR_GRAPHICS_COMPONENT_HPP