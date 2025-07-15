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

    void render() const override;

    // Optionally, allow changing colors/textures
    void setBackgroundColor(Color color);
    void setHoverColor(Color color);
    void setPressedColor(Color color);
    void setTextColor(Color color);

private:
    const IButtonView* buttonView;

    // Simple color scheme for demonstration
    Color backgroundColor = LIGHTGRAY;
    Color hoverColor = GRAY;
    Color pressedColor = DARKGRAY;
    Color textColor = BLACK;
};

#endif // BUTTON_GRAPHICS_COMPONENT_HPP