#include "Button.hpp"
#include "ButtonGraphicsComponent.hpp"
#include <raylib.h>
#include <iostream>

Button::Button(int x, int y, int width, int height, const std::string& text, int fontSize, int offset, int side, const std::string &fontPath, bool labelShift)
    : x(x), y(y), width(width), height(height), text(text),
      idleState(true), hoveredState(false), pressedState(false), disabledState(false),
      onClick(nullptr), onHoverEnter(nullptr), enterHovered(false), exitHovered(false)
{
    bounds = { (float)x, (float)y, (float)width, (float)height };
    graphic = std::make_unique<ButtonGraphicsComponent>(this);
    graphic->init(fontSize, offset, side);
    graphic->loadFont(fontPath);
    graphic->setLabelShift(labelShift);
}

Button::~Button(){
    if (graphic) {
        graphic->unload();
    }
}

void Button::enable() { disabledState = false; }
void Button::disable() { disabledState = true; }
void Button::setToState(std::string state) {
    idleState = (state == "idle");
    hoveredState = (state == "hovered");
    pressedState = (state == "pressed");
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
void Button::setOnHoverExitListener(std::function<void()> callback) { onHoverExit = callback; }
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

void Button::setEnterHovered(bool enterHovered) {
    this->enterHovered = enterHovered;
}

void Button::setExitHovered(bool exitHovered) {
    this->exitHovered = exitHovered;
}

void Button::setLayer(int layer) {
    graphic->setLayer(layer);
}

void Button::update(float dt) {
    if (disabledState) {
        idleState = true;
        hoveredState = false;
        pressedState = false;
        return;
    }

    if(enterHovered) {
        if (onHoverEnter) onHoverEnter();
        idleState = false;
        hoveredState = true;
        enterHovered = false;
    }

    if(exitHovered){
        if (onHoverExit) onHoverExit();
        hoveredState = false;
        idleState = true;
        exitHovered = false;
    }
    graphic->update(dt);
}

void Button::triggerHoverEnter() {
    if (onHoverEnter) onHoverEnter();
}

void Button::triggerOnClick() {
    if (onClick) onClick();
}

// --- Helper ---
bool Button::contains(int mouseX, int mouseY) const {
    return CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, bounds);
}

ButtonGraphicsComponent* Button::getGraphicsComponent(){
    return graphic.get();
}