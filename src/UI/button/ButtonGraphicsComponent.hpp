#ifndef BUTTON_GRAPHICS_COMPONENT_HPP
#define BUTTON_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>

// Forward declaration
class IButtonView;

class ButtonGraphicsComponent : public GraphicsComponent {
public:
    // ButtonGraphicsComponent needs a pointer to the logic/view interface
    ButtonGraphicsComponent(const IButtonView* buttonView);
    ~ButtonGraphicsComponent() override;

    void update(float df);
    void render() const override;

    // Optionally, allow changing colors/textures
    void setBackgroundColor(Color color);
    void setHoverColor(Color color);
    void setPressedColor(Color color);
    void setTextColor(Color color);
    void loadFont(const std::string& fontPath);
    void unload();

private:
    const IButtonView* buttonView;

    // Simple color scheme for demonstration
    Color backgroundColor = LIGHTGRAY;
    Color hoverColor = GRAY;
    Color pressedColor = DARKGRAY;
    Color textColor = WHITE;
    Font font;
    bool isLoaded = false;
    float effectRectHeight;
    float period;
};

#endif // BUTTON_GRAPHICS_COMPONENT_HPP