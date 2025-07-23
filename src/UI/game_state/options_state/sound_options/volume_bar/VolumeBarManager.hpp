#ifndef VOLUME_BAR_MANAGER_HPP
#define VOLUME_BAR_MANAGER_HPP

#include <vector>
#include <memory>
#include <raylib.h>
#include "VolumeBar.hpp"

class VolumeBarManager {
public:
    VolumeBarManager();
    ~VolumeBarManager();

    void addVolumeBar(std::unique_ptr<VolumeBar> bar);
    void update(float dt);
    void reset();
    void setHoveredIndex(int index);
    int getHoveredIndex() const;
    int getBarCount() const;
    VolumeBar* getBar(int idx);

private:
    std::vector<std::unique_ptr<VolumeBar>> bars;
    int hoveredIndex = -1;

    void updateHoveredByMouse();
    void updateHoveredByKeyboard();
    void adjustCurrentBar(float delta);
};

#endif // VOLUME_BAR_MANAGER_HPP