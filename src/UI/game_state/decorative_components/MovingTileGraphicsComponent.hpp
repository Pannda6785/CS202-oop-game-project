#ifndef MOVING_TILE_GRAPHICS_COMPONENT_HPP
#define MOVING_TILE_GRAPHICS_COMPONENT_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <vector>
#include <raylib.h>

class MovingTileGraphicsComponent : public GraphicsComponent {
public:
    MovingTileGraphicsComponent();
    virtual ~MovingTileGraphicsComponent();

    void update(float dt);
    void render() const override;

    void addTexture(const std::string& texturePath);
    void unloadTextures();
    void setStartPosition(Vector2 startPosition);
    void setSpeed(float speed);
    void setAngle(float angle);
    void setUpward(bool upward);
    void setRestrictArea(Rectangle area);
    void setScale(float scale);
    void setInitialNumTiles(int numTiles);
    void setColor(Color color);
    void setExpandingTime(float time);
    void setStartExpand(bool startExpand);
    void init();

    bool getStartExpand() const;
    float getTileWidth() const;
    float getRatio() const;
    Vector2 getStartPositionToDraw() const;
    Vector2 getStartPosition() const;
    Vector2 getMiddlePostion() const;
    Vector2 getPositionToDraw(Vector2 pos, float textureHeight, float ratio) const;
private:
    Vector2 startPosition = {0.0f, 0.0f};
    float speed = 0.0f;
    float angle = 0.0f;
    float scale = 1.0f;
    std::vector<Vector2> positions;
    std::vector<Texture2D> textures;
    bool upward = true;
    Rectangle restrictArea = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    int initialNumTiles = 200;
    Color color = WHITE;
    float expandingTime = 0.0f;
    float expandingTimer = 0.0f;
    bool startExpand = false;
};

#endif // MOVING_TILE_GRAPHICS_COMPONENT_HPP