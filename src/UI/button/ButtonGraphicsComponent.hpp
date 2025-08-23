#ifndef BUTTON_GRAPHICS_COMPONENT_HPP
#define BUTTON_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>

// Forward declaration
class IButtonView;

class ButtonGraphicsComponent : public GraphicsComponent {
public:
    ButtonGraphicsComponent(const IButtonView* buttonView);
    ~ButtonGraphicsComponent() override;

    void update(float dt);
    void render() const override;

    void init(int _fontSize, int _offset, int side);
    void setBackgroundColor(Color color);
    void setHoverColor(Color color);
    void setPressedColor(Color color);
    void setTextColor(Color color);
    void setRectangle(Rectangle rec);
    void setLabelShift(bool labelShift);
    void loadFont(const std::string& fontPath);
    void unload();

private:
    const IButtonView* buttonView;

    Color backgroundColor = LIGHTGRAY;
    Color hoverColor = GRAY;
    Color pressedColor = DARKGRAY;
    Color textColor = WHITE;
    Font font;
    bool isLoaded = false;
    float effectRectHeight;
    float period;
    int fontSize;
    int offset;
    int side;
    bool labelShift;
};

#endif // BUTTON_GRAPHICS_COMPONENT_HPP