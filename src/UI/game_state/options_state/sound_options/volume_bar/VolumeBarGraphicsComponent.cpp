#include "VolumeBarGraphicsComponent.hpp"
#include "VolumeBar.hpp"
#include <raylib.h>

VolumeBarGraphicsComponent::VolumeBarGraphicsComponent(const VolumeBar* volumeBar) : 
GraphicsComponent(), volumeBar(volumeBar) {}

VolumeBarGraphicsComponent::~VolumeBarGraphicsComponent() {
    volumeBar = nullptr;
}

void VolumeBarGraphicsComponent::setFont(Font *font) {
    this->font = font;
}

void VolumeBarGraphicsComponent::render() const {
    if (!volumeBar) return;
    Color color = volumeBar->isHovered() ? BLACK : WHITE;
    DrawRectangleRec(volumeBar->getBarRect(), color);
    DrawRectangleRec(volumeBar->getKnobRect(), color);
    if (font) {
        std::string volumeText = std::to_string(static_cast<int>(volumeBar->getVolume() * 100));
        Vector2 textSize = MeasureTextEx(*font, volumeText.c_str(), font->baseSize, 0);
        Vector2 textPosition = {
            volumeBar->getBarRect().x + volumeBar->getBarRect().width + 40.0f,
            volumeBar->getBarRect().y - 25
        };
        DrawTextEx(*font, volumeText.c_str(), textPosition, 50, 3, color);
    }
}