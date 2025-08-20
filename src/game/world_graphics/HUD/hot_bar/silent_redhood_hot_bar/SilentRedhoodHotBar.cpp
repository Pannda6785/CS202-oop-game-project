#include "SilentRedhoodHotBar.hpp"
#include <iostream>

SilentRedhoodHotBar::SilentRedhoodHotBar(bool isLeftSide) {
    // Set the side of the hot bar (left or right)
    setSide(isLeftSide);

    // Load textures for Silent Redhood abilities
    loadTexture(abilityTexturePaths);
    init();
}