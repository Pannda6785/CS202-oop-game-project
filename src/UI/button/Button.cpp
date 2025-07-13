#include "Button.hpp"
#include "ButtonGraphicsComponent.hpp"
#include <raylib.h>
#include <iostream>

Button::Button(int x, int y, int width, int height, const std::string& text, const Unit::GameEvent &eventToPublish)
    : x(x), y(y), width(width), height(height), text(text), eventToPublish(eventToPublish),
      idleState(true), hoveredState(false), pressedState(false), disabledState(false),
      onClick(nullptr), onHoverEnter(nullptr)
{
    bounds = { (float)x, (float)y, (float)width, (float)height };
    graphic = std::make_unique<ButtonGraphicsComponent>(this);
}

Button::~Button() = default;

// --- IButtonControl methods ---
void Button::enable() { disabledState = false; }
void Button::disable() { disabledState = true; }
void Button::setToState(std::string state) {
    idleState = state == "idle";
    hoveredState = state == "hovered";
    pressedState = state == "pressed";
}
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
bool Button::isIdle() const { return idleState; }
bool Button::isHovered() const { return hoveredState; }
bool Button::isPressed() const { return pressedState; }
bool Button::isEnabled() const { return !disabledState; }
const std::string& Button::getText() const { return text; }
int Button::getX() const { return x; }
int Button::getY() const { return y; }
int Button::getWidth() const { return width; }
int Button::getHeight() const { return height; }
Rectangle Button::getBounds() const { return bounds; }
Unit::GameEvent Button::getEventToPublish() const { return eventToPublish; }

// --- Logic update ---
void Button::update(float dt) {
    if (disabledState) {
        idleState = true;
        hoveredState = false;
        pressedState = false;
        return;
    }

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    bool mouseOver = contains(mouseX, mouseY);

    if (mouseOver) {
        if (!hoveredState && onHoverEnter) {
            onHoverEnter();
        }
        hoveredState = true;
        idleState = false;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            pressedState = true;
            triggerOnClick();
        } else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            pressedState = false;
        }
    } else {
        hoveredState = false;
        pressedState = false;
        idleState = true;
    }
}

void Button::triggerHoverEnter() {
    if (onHoverEnter) onHoverEnter();
}

void Button::triggerOnClick() {
    if (onClick) onClick();
    //EventManager::GetInstance().publish(eventToPublish);
}

// --- Helper ---
bool Button::contains(int mouseX, int mouseY) const {
    return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, bounds);
}

ButtonGraphicsComponent* Button::getGraphicsComponent() const {
    return graphic.get();
}