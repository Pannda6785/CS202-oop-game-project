#include "ButtonGraphicsComponent.hpp"
#include "IButtonView.hpp"
#include <raylib.h>

ButtonGraphicsComponent::ButtonGraphicsComponent(const IButtonView* buttonView)
    : buttonView(buttonView) {}

void ButtonGraphicsComponent::render() const {
    if (!buttonView || !isVisible()) return;

    // Determine color based on state
    Color currentColor = backgroundColor;
    if (buttonView->isEnabled()) {
        if (buttonView->isPressed()) {
            currentColor = pressedColor;
        } else if (buttonView->isHovered()) {
            currentColor = hoverColor;
        }
    } else {
        currentColor = { currentColor.r / 2, currentColor.g / 2, currentColor.b / 2, currentColor.a };
    }

    Rectangle bounds = {
        (float)buttonView->getX(),
        (float)buttonView->getY(),
        (float)buttonView->getWidth(),
        (float)buttonView->getHeight()
    };

    DrawRectangleRec(bounds, currentColor);
    DrawRectangleLinesEx(bounds, 2, BLACK);

    // Draw button label centered
    int fontSize = 20;
    const std::string& label = buttonView->getText();
    int textWidth = MeasureText(label.c_str(), fontSize);
    int textX = bounds.x + (bounds.width - textWidth) / 2;
    int textY = bounds.y + (bounds.height - fontSize) / 2;
    DrawText(label.c_str(), textX, textY, fontSize, textColor);
}

void ButtonGraphicsComponent::setBackgroundColor(Color color) { backgroundColor = color; }
void ButtonGraphicsComponent::setHoverColor(Color color) { hoverColor = color; }
void ButtonGraphicsComponent::setPressedColor(Color color) { pressedColor = color; }
void ButtonGraphicsComponent::setTextColor(Color color) { textColor = color; }