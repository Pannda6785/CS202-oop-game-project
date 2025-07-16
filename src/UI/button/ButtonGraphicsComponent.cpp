#include "ButtonGraphicsComponent.hpp"
#include "IButtonView.hpp"
#include <raylib.h>
#include <iostream>

ButtonGraphicsComponent::ButtonGraphicsComponent(const IButtonView* buttonView) : buttonView(buttonView) {
    font = LoadFontEx("../assets/fonts/Redressed.ttf", 150, 0, 0);
    isLoaded = true;
    effectRectHeight = 0.0f;
    period = 0.3f;
}

ButtonGraphicsComponent::~ButtonGraphicsComponent() {
}

void ButtonGraphicsComponent::loadFont(const std::string& fontPath) {
    font = LoadFont(fontPath.c_str());
    isLoaded = true;
}

void ButtonGraphicsComponent::unload() {
    if (isLoaded) {
        UnloadFont(font);
        isLoaded = false;
    }
    // std::cout << "ButtonGraphicsComponent unloaded." << std::endl;
}

void ButtonGraphicsComponent::update(float dt){
    // Determine color based on state
    Color currentColor = backgroundColor;
    if (buttonView->isEnabled()) {
        if (buttonView->isPressed()) {
            currentColor = pressedColor;
        } else if (buttonView->isHovered()) {
            currentColor = hoverColor;
            // s = buttonView->getHeight / 2;
            // period
            // -> v = s / period
            // _v = v * (GetFrameTime() / period)
            float delta = buttonView->getHeight() / 2.0f / period * dt / period;
            effectRectHeight = std::min(effectRectHeight + delta, buttonView->getHeight() / 2.0f);
        } else{
            float delta = buttonView->getHeight() / 2.0f / period * dt / period;
            effectRectHeight = std::max(effectRectHeight - delta, 0.0f);
        }
    } else {
        currentColor = { currentColor.r / 2, currentColor.g / 2, currentColor.b / 2, currentColor.a };
    }
}

void ButtonGraphicsComponent::render() const {
    if (!buttonView || !isVisible()) return;

    Rectangle bounds = {
        (float)buttonView->getX(),
        (float)buttonView->getY() + buttonView->getHeight() / 2.0f - effectRectHeight,
        (float)buttonView->getWidth(),
        effectRectHeight * 2.0f
    };
    DrawRectangleRec(bounds, WHITE);
    // DrawRectangleLinesEx(bounds, 2, BLACK);

    // Draw button label centered
    if (isLoaded) {
        int fontSize = 75;
        const std::string& label = buttonView->getText();
        Vector2 textSize = MeasureTextEx(font, label.c_str(), fontSize, 2);
        int textX = bounds.x + (bounds.width - textSize.x) / 2;
        int textY = bounds.y + (bounds.height - textSize.y) / 2;
        if(buttonView->isHovered()){
            textX -= 10.0f;
            textY -= 10.0f;
        }
        DrawTextEx(font, label.c_str(), { (float)textX, (float)textY }, fontSize, 1.0f, buttonView->isHovered() ? BLACK : WHITE);
    } else {
        int fontSize = 20;
        const std::string& label = buttonView->getText();
        int textWidth = MeasureText(label.c_str(), fontSize);
        int textX = bounds.x + (bounds.width - textWidth) / 2;
        int textY = bounds.y + (bounds.height - fontSize) / 2;
        DrawText(label.c_str(), textX, textY, fontSize, textColor);
    }
}

void ButtonGraphicsComponent::setBackgroundColor(Color color) { backgroundColor = color; }
void ButtonGraphicsComponent::setHoverColor(Color color) { hoverColor = color; }
void ButtonGraphicsComponent::setPressedColor(Color color) { pressedColor = color; }
void ButtonGraphicsComponent::setTextColor(Color color) { textColor = color; }