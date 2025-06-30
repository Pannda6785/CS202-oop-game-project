#include "Button.hpp"
#include "ButtonGraphicsComponent.hpp"
#include <raylib.h>

Button::Button(int x, int y, int width, int height, const std::string& text)
    : x(x), y(y), width(width), height(height), text(text),
      isIdle(true), isHovered(false), isPressed(false), isDisabled(false),
      onClick(nullptr), onHoverEnter(nullptr)
{
    bounds = { (float)x, (float)y, (float)width, (float)height };
    graphic = std::make_unique<ButtonGraphicsComponent>(this);
}

Button::~Button() = default;

// --- IButtonControl methods ---
void Button::enable() { isDisabled = false; }
void Button::disable() { isDisabled = true; }
void Button::setText(const std::string& newText) { text = newText; }
void Button::setPosition(int newX, int newY) { 
    x = newX; 
    y = newY; 
    bounds.x = (float)newX;
    bounds.y = (float)newY;
}
void Button::setOnClickListener(std::function<void()> callback) { onClick = callback; }
void Button::setOnHoverEnterListener(std::function<void()> callback) { onHoverEnter = callback; }

// --- IButtonView methods ---
bool Button::isIdle() const { return isIdle; }
bool Button::isHovered() const { return isHovered; }
bool Button::isPressed() const { return isPressed; }
bool Button::isEnabled() const { return !isDisabled; }
const std::string& Button::getText() const { return text; }
int Button::getX() const { return x; }
int Button::getY() const { return y; }
int Button::getWidth() const { return width; }
int Button::getHeight() const { return height; }

// --- Logic update ---
void Button::update(float dt) {
    if (isDisabled) {
        isIdle = true;
        isHovered = false;
        isPressed = false;
        return;
    }

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    bool mouseOver = contains(mouseX, mouseY);

    if (mouseOver) {
        if (!isHovered && onHoverEnter) {
            onHoverEnter();
        }
        isHovered = true;
        isIdle = false;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isPressed = true;
            if (onClick) onClick();
        } else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            isPressed = false;
        }
    } else {
        isHovered = false;
        isPressed = false;
        isIdle = true;
    }
}

// --- Helper ---
bool Button::contains(int mouseX, int mouseY) const {
    return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, bounds);
}

ButtonGraphicsComponent* Button::getGraphicsComponent() const {
    return graphic.get();
}