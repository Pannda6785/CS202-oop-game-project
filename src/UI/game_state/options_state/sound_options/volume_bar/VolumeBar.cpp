#include "VolumeBar.hpp"

VolumeBar::VolumeBar(Rectangle barRect, float initialVolume, IButtonView* buttonView)
    : barRect(barRect), volume(initialVolume), buttonView(buttonView) {
    if (buttonView) {
        graphic = std::make_unique<VolumeBarGraphicsComponent>(this);
        graphic->setLayer(10); // Set a layer for rendering
    }
    knobWidth = barRect.height; // Default knob width to match bar height
}

void VolumeBar::setVolume(float v) {
    if (v < 0.0f) v = 0.0f;
    if (v > 1.0f) v = 1.0f;
    volume = v;
}

float VolumeBar::getVolume() const {
    return volume;
}

Rectangle VolumeBar::getBarRect() const {
    return barRect;
}

Rectangle VolumeBar::getKnobRect() const {
    float knobX = barRect.x + volume * (barRect.width - knobWidth);
    float knobHeight = 20;
    return Rectangle{ knobX, barRect.y - knobHeight / 2.0f, knobWidth, barRect.height + knobHeight };
}

IButtonView* VolumeBar::getButtonView() const {
    return buttonView;
}

bool VolumeBar::isHovered() const {
    return buttonView && buttonView->isHovered();
}

void VolumeBar::setKnobWidth(float w) {
    knobWidth = w;
}

void VolumeBar::setFont(Font *font) {
    if (graphic) {
        graphic->setFont(font);
    }
}