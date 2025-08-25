#ifndef MOVING_TEXT_HPP
#define MOVING_TEXT_HPP

#include "GameText.hpp"
#include "../../../graphics/GraphicsComponent.hpp"
#include "../../../graphics/GraphicsComponentManager.hpp"
#include <vector>
#include <string>
#include <memory>
#include <raylib.h>

class MovingText : public GraphicsComponent {
public:
    MovingText();
    virtual ~MovingText();

    void update(float dt);
    void render() const override;

    // Setup methods
    void setText(const std::string& text);
    void loadFont(const std::string& fontPath);
    void setFontSize(int size);
    void setTextColor(Color color);

    // Position and movement methods
    void setStartPosition(Vector2 startPosition);
    void setSpeed(float speed);
    void setAngle(float angle);
    void setUpward(bool upward);
    void setRestrictArea(Rectangle area);
    void setScale(float scale);
    void setInitialNumTexts(int numTexts);
    void setTextSpacing(float spacing);
    void setOriginRatio(Vector2 originRatio);
    void init();

    // Getters
    float getTextWidth() const;
    float getTextHeight() const;
    float getRatio() const;
    Vector2 getStartPositionToDraw() const;
    Vector2 getStartPosition() const;
    Vector2 getMiddlePosition() const;

private:
    Vector2 getPositionToDraw(Vector2 pos, float textHeight, float ratio) const;

    std::string textContent;
    std::unique_ptr<GameText> sampleText;  // Single text instance for rendering
    std::vector<Vector2> positions;        // Positions to render at
    
    Vector2 startPosition = {0.0f, 0.0f};
    float speed = 0.0f;
    float angle = 0.0f;
    float scale = 1.0f;
    float textSpacing = 10.0f; // Spacing between consecutive texts
    bool upward = true;
    Rectangle restrictArea = {0, 0, (float)GraphicsComponentManager::NATIVE_WIDTH, (float)GraphicsComponentManager::NATIVE_HEIGHT};
    int initialNumTexts = 10;
    Vector2 originRatio = {0.5f, 0.5f};
    
    // Font properties
    std::string fontPath;
    int fontSize = 32;
    Color textColor = WHITE;
    bool fontLoaded = false;
};

#endif // MOVING_TEXT_HPP