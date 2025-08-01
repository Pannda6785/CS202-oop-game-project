#include "Background.hpp"
#include <iostream>

Background::Background() : GraphicsComponent(), backgroundRect({0, 0, 0, 0}), backgroundColor(BLACK) {
    setLayer(0);
}

Background::~Background() = default;

void Background::render() const {
    float rotation = angle;
    // std::cout << "offset " << origin.y << std::endl;
    DrawRectanglePro({backgroundRect.x, backgroundRect.y, backgroundRect.width, backgroundRect.height}, origin, rotation, backgroundColor);
}

void Background::setBackgroundColor(Color color) {
    backgroundColor = color;
}

void Background::setOriginMiddle() {
    origin.y = backgroundRect.height / 2.0f;
}

void Background::setBackgroundRect(Rectangle rect) {
    backgroundRect = rect;
}

void Background::setAngle(float angle) {
    this->angle = angle;
}

float Background::getWidth() const {
    return backgroundRect.width;
}