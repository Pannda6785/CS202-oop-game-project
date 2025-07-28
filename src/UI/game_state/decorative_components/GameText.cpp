#include "GameText.hpp"
#include <raylib.h>

GameText::GameText() : GraphicsComponent(), font(GetFontDefault()), fontLoaded(false), x(0), y(0), fontSize(32), color(WHITE) {}

GameText::~GameText() {
    if (fontLoaded) {
        UnloadFont(font);
    }
}

void GameText::setText(const std::string& t) {
    text = t;
}

void GameText::loadFont(const std::string& fontPath) {
    if (fontLoaded) {
        UnloadFont(font);
        fontLoaded = false;
    }
    font = LoadFontEx(fontPath.c_str(), fontSize, nullptr, 0);
    fontLoaded = font.texture.id != 0;
}

void GameText::unloadFont() {
    if (fontLoaded) {
        UnloadFont(font);
        fontLoaded = false;
    }
}

void GameText::setPosition(int px, int py) {
    x = px;
    y = py;
}

void GameText::setColor(Color c) {
    color = c;
}

void GameText::setFontSize(int size) {
    fontSize = size;
}

const std::string& GameText::getText() const {
    return text;
}

int GameText::getX() const {
    return x;
}

int GameText::getY() const {
    return y;
}

int GameText::getFontSize() const {
    return fontSize;
}

Color GameText::getColor() const {
    return color;
}

void GameText::render() const {
    if (text.empty()) return;
    if (fontLoaded) {
        DrawTextEx(font, text.c_str(), {(float)x, (float)y}, (float)fontSize, 1, color);
    } else {
        DrawText(text.c_str(), x, y, fontSize, color);
    }
}