#ifndef MOVING_TILE_GRAPHICS_COMPONENT_HPP
#define MOVING_TILE_GRAPHICS_COMPONENT_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <vector>
#include <raylib.h>

class MovingTileGraphicsComponent : public GraphicsComponent {
public:
    MovingTileGraphicsComponent();
    virtual ~MovingTileGraphicsComponent();

    void loadTexture(const std::string& texturePath);
    void loadSideLines(const std::string& sideLinesPath);
    void unloadTextures();
    void init(Vector2 _startPosition, float _angle, float _speed, int layer);
    void update(float dt);
    void render() const override;
private:
    Vector2 startPosition;
    float speed;
    float angle;
    std::vector<Vector2> positions;
    Texture2D tilePattern;
    Texture2D sideLines;
    bool loadedTilePattern = false;
    bool loadedSideLines = false;

};

#endif // MOVING_TILE_GRAPHICS_COMPONENT_HPP