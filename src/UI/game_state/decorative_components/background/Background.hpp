#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "../../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>

class Background : public GraphicsComponent {
public:
    Background();
    ~Background();

    void render() const override;
    void setBackgroundColor(Color color);
    void setBackgroundRect(Rectangle rect);
    void setOriginMiddle();
    void setAngle(float angle);
    float getWidth() const;

private:
    Rectangle backgroundRect = {0, 0, 0, 0};
    Color backgroundColor = BLACK;
    Vector2 origin = {0.0f, 0.0f}; // Origin for rotation, if needed
    float angle = 0.0f; // Angle for rotation, if needed
};

#endif // BACKGROUND_HPP