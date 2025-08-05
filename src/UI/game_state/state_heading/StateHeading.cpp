#include "StateHeading.hpp"

StateHeading::StateHeading() = default;

StateHeading::~StateHeading() = default;

void StateHeading::setHasHeading(bool hasHeading) {
    this->hasHeading = hasHeading;
}

void StateHeading::init(const std::string &fontPath, const std::string &title, int posY, int fontSize, const Rectangle &dividerLine){
    this->font = LoadFontEx(fontPath.c_str(), 255, nullptr, 0);
    this->title = title;
    this->position = {GetScreenWidth() / 2 - MeasureText(title.c_str(), fontSize) / 2, posY};
    this->fontSize = fontSize;
    this->dividerLine = dividerLine;
}

void StateHeading::render() const {
    if (hasHeading) {
        DrawTextEx(font, title.c_str(), position, fontSize, 10, WHITE);
        DrawRectangle(dividerLine.x, dividerLine.y, dividerLine.width, dividerLine.height, WHITE);
    }
}

void StateHeading::unload() {
    if(font.texture.id != 0) UnloadFont(font);
}
