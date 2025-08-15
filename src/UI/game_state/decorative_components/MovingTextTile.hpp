#ifndef MOVING_TEXT_TILE_HPP
#define MOVING_TEXT_TILE_HPP

#include "MovingTileGraphicsComponent.hpp"
#include "MovingText.hpp"
#include "Background.hpp"
#include "../../../graphics/GraphicsComponent.hpp"
#include <memory>
#include <string>
#include <raylib.h>

class MovingTextTile{
public:
    MovingTextTile();
    virtual ~MovingTextTile();

    void update(float dt);
    
    // Moving Tile setup methods
    void setTileTexture(const std::string& texturePath);
    void setTileStartPosition(Vector2 startPosition);
    void setTileSpeed(float speed);
    void setTileAngle(float angle);
    void setTileUpward(bool upward);
    void setTileRestrictArea(Rectangle area);
    void setTileScale(float scale);
    void setTileInitialNum(int numTiles);
    void setTileColor(Color color);
    void setTileExpandingTime(float time);
    void setTileStartExpand(bool startExpand);
    
    // Text setup methods
    void setText(const std::string& text);
    void setTextFont(const std::string& fontPath);
    void setTextFontSize(int size);
    void setTextColor(Color color);
    void setTextSpacing(float spacing);
    void setTextSpeed(float speed);
    
    // Background setup methods
    void setBackgroundColor(Color color);
    void setBackgroundWidthRatio(float ratio);
    
    // Common settings
    void setLayer(int layer);
    void init();
    
    // Status getters
    bool isExpanded() const;
    Vector2 getMiddlePosition() const;

private:
    MovingTileGraphicsComponent movingTile;
    Background background;
    MovingText movingText;
    
    float backgroundWidthRatio = 1.0f;
    float backgroundHeightRatio = 0.6f;
    
    int baseLayer = 0;
    
    bool initialized = false;
};

#endif // MOVING_TEXT_TILE_HPP