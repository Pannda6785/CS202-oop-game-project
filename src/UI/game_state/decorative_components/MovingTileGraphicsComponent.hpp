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
    void setExpandingTime(float time);
    void setStartExpand(bool startExpand);
    bool getStartExpand() const;
    float getTileWidth() const;
    float getRatio() const;
    Vector2 getStartPositionToDraw() const;
    Vector2 getStartPosition() const;
    Vector2 getMiddlePostion() const;
    Vector2 getPositionToDraw(Vector2 pos, float textureHeight, float ratio) const;
private:
    Vector2 startPosition;
    float speed;
    float angle;
    float scale = 1.0f; // Scale factor for rendering
    std::vector<Vector2> positions;
    std::vector<Texture2D> textures;
    bool upward = true; // Direction of movement
    Rectangle restrictArea = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}; // Default restrict area to screen size
    int initialNumTiles = 10; // Number of tiles to generate
    Color color = WHITE; // Default color for rendering
    float expandingTime = 0.0f; // Time for expanding effect
    float expandingTimer = 0.0f; // Timer for expanding effect
    bool startExpand = false; // Whether the tiles can expand
};

#endif // MOVING_TILE_GRAPHICS_COMPONENT_HPP