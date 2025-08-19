#include "StateHeading.hpp"

StateHeading::StateHeading() 
    : hasHeading(false), 
      alignment(Alignment::MIDDLE), 
      offset(0) {
}

StateHeading::~StateHeading() = default;

void StateHeading::setHasHeading(bool hasHeading) {
    this->hasHeading = hasHeading;
}

// Original init method (defaults to middle alignment)
void StateHeading::init(const std::string &fontPath, const std::string &title, 
                        int posY, int fontSize, const Rectangle &dividerLine) {
    init(fontPath, title, posY, fontSize, dividerLine, Alignment::MIDDLE, 0);
}

// New init method with alignment options
void StateHeading::init(const std::string &fontPath, const std::string &title, 
                        int posY, int fontSize, const Rectangle &dividerLine, 
                        Alignment alignment, int offset) {
    this->font = LoadFontEx(fontPath.c_str(), 255, nullptr, 0);
    this->title = title;
    this->fontSize = fontSize;
    this->dividerLine = dividerLine;
    this->alignment = alignment;
    this->offset = offset;
    
    // Initial position calculation
    this->position.y = posY;
    updatePosition();
}

void StateHeading::setAlignment(Alignment alignment, int offset) {
    this->alignment = alignment;
    this->offset = offset;
    updatePosition();
}

void StateHeading::updatePosition() {
    float textWidth = MeasureTextEx(font, title.c_str(), fontSize, 10).x;
    
    switch (alignment) {
        case Alignment::LEFT:
            position.x = offset;
            break;
            
        case Alignment::MIDDLE:
            position.x = GetScreenWidth() / 2 - textWidth / 2 + offset;
            break;
            
        case Alignment::RIGHT:
            position.x = GetScreenWidth() - textWidth - offset;
            break;
    }
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
