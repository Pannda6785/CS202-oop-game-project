#include "Background.hpp"

Background::Background() : GraphicsComponent(), backgroundRect({0, 0, 0, 0}), backgroundColor(BLACK) {
    setLayer(0);
}

Background::~Background() = default;

void Background::render() const {
    DrawRectangleRec(backgroundRect, backgroundColor);
}

void Background::setBackgroundColor(Color color) {
    backgroundColor = color;
}

void Background::setBackgroundRect(Rectangle rect) {
    backgroundRect = rect;
}