#ifndef MOVING_TEXT_TILE_BUILDER_HPP
#define MOVING_TEXT_TILE_BUILDER_HPP

#include "../../decorative_components/MovingTextTile.hpp"
#include <memory>
#include <string>
#include <raylib.h>

class MovingTextTileBuilder {
public:
    MovingTextTileBuilder();
    ~MovingTextTileBuilder() = default;

    // Tile configuration
    MovingTextTileBuilder& withTileTexture(const std::string& texturePath);
    MovingTextTileBuilder& withTileStartPosition(Vector2 startPosition);
    MovingTextTileBuilder& withTileSpeed(float speed);
    MovingTextTileBuilder& withTileAngle(float angle);
    MovingTextTileBuilder& withTileUpward(bool upward);
    MovingTextTileBuilder& withTileRestrictArea(Rectangle area);
    MovingTextTileBuilder& withTileScale(float scale);
    MovingTextTileBuilder& withTileInitialNum(int numTiles);
    MovingTextTileBuilder& withTileColor(Color color);
    MovingTextTileBuilder& withTileExpandingTime(float time);
    MovingTextTileBuilder& withTileStartExpand(bool startExpand);
    
    // Text configuration
    MovingTextTileBuilder& withText(const std::string& text);
    MovingTextTileBuilder& withTextFont(const std::string& fontPath);
    MovingTextTileBuilder& withTextFontSize(int size);
    MovingTextTileBuilder& withTextColor(Color color);
    MovingTextTileBuilder& withTextSpacing(float spacing);
    MovingTextTileBuilder& withTextSpeed(float speed);

    // Background configuration
    MovingTextTileBuilder& withBackgroundColor(Color color);
    MovingTextTileBuilder& withBackgroundWidthRatio(float ratio);
    
    // Common settings
    MovingTextTileBuilder& withLayer(int layer);
    
    // Presets
    MovingTextTileBuilder& withCharacterNamePreset(const std::string& characterName);
    MovingTextTileBuilder& withGameTitlePreset();
    MovingTextTileBuilder& withVersusPreset();
    
    // Build method
    std::unique_ptr<MovingTextTile> build();
    
    // Reset builder for reuse
    void reset();

private:
    std::unique_ptr<MovingTextTile> textTile;
};

#endif // MOVING_TEXT_TILE_BUILDER_HPP