#include "SunPriestessHotBar.hpp"
#include <iostream>

SunPriestessHotBar::SunPriestessHotBar(bool isLeftSide) {
    // Set the side of the hot bar (left or right)
    setSide(isLeftSide);
    
    // Load textures for all abilities
    loadTexture(abilityTexturePaths);
    init();
}