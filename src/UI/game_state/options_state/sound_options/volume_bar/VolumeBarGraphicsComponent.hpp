#ifndef VOLUME_BAR_GRAPHICS_COMPONENT_HPP
#define VOLUME_BAR_GRAPHICS_COMPONENT_HPP

#include "../../../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>

class VolumeBar;

class VolumeBarGraphicsComponent : public GraphicsComponent {
public:
    VolumeBarGraphicsComponent(const VolumeBar* volumeBar);
    ~VolumeBarGraphicsComponent() override;
    void setFont(Font *font);
    void render() const override;

private:
    const VolumeBar* volumeBar;
    Font *font;
};

#endif // VOLUME_BAR_GRAPHICS_COMPONENT_HPP
