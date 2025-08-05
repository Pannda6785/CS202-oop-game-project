#ifndef MOVING_TILE_GRAPHICS_COMPONENT_HPP
#define MOVING_TILE_GRAPHICS_COMPONENT_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <vector>
#include <raylib.h>

class MovingTileGraphicsComponent : public GraphicsComponent {
public:
    MovingTileGraphicsComponent();
    virtual ~MovingTileGraphicsComponent();

    void addTexture(const std::string& texturePath);
    void unloadTextures();
    void init(Vector2 _startPosition, float _angle, float _speed, int layer);
    void update(float dt);
    void render() const override;
    void setUpward(bool upward);
    void setRestrictArea(Rectangle area);
    void setScale(float scale);
    void setInitialNumTiles(int numTiles);
    void setColor(Color color);
private:
    Vector2 startPosition;
    float speed;
    float angle;
    float scale = 1.0f; // Scale factor for rendering
    std::vector<Vector2> positions;
    std::vector<Texture2D> textures;
    bool upward = true; // Direction of movement
    Rectangle restrictArea = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}; // Default restrict area to screen size
    int initialNumTiles = 15; // Number of tiles to generate
    Color color = WHITE; // Default color for rendering
};

#endif // MOVING_TILE_GRAPHICS_COMPONENT_HPP