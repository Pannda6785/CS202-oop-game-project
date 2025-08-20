#include "RoyalArcanistHotBar.hpp"
#include <iostream>

RoyalArcanistHotBar::RoyalArcanistHotBar(bool isLeftSide) {
    // Set the side of the hot bar (left or right)
    setSide(isLeftSide);
    
    // Load textures for all abilities
    loadTexture(abilityTexturePaths);
    init();
}