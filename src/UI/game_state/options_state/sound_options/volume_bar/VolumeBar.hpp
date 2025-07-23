#ifndef VOLUME_BAR_HPP
#define VOLUME_BAR_HPP

#include "VolumeBarGraphicsComponent.hpp"
#include "../../../../button/IButtonView.hpp"
#include <raylib.h>
#include <memory>

class VolumeBar {
public:
    VolumeBar(Rectangle barRect, float initialVolume, IButtonView* buttonView);
    ~VolumeBar() = default;

    void setVolume(float v); // 0.0f - 1.0f
    float getVolume() const;

    Rectangle getBarRect() const;
    Rectangle getKnobRect() const;
    IButtonView* getButtonView() const;
    bool isHovered() const;

    void setKnobWidth(float w);
    void setFont(Font *font);

private:
    Rectangle barRect;
    float volume; // 0.0f - 1.0f
    float knobWidth = 13.0f;
    IButtonView* buttonView;
    std::unique_ptr<VolumeBarGraphicsComponent> graphic;
};

#endif // VOLUME_BAR_HPP