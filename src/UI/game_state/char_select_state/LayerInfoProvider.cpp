// LayerInfoProvider.cpp
#include "LayerInfoProvider.hpp"
#include <algorithm>

LayerInfoProvider::LayerInfoProvider() = default;
LayerInfoProvider::~LayerInfoProvider() = default;

LayerInfoProvider& LayerInfoProvider::getInstance() {
    static LayerInfoProvider instance;
    return instance;
}

void LayerInfoProvider::init() {
    layers = {"background",
              "background_tile_0", 
              "tile_rect_0",
              "background_tile_1", 
              "tile_rect_1",
              "background_tile_2", 
              "tile_rect_2",
              "main_portrait", 
              "ribbon_background",
              "front_tile",
              "middle_tile_0",
              "middle_tile_1",
              "below_background",
              "idle_anim_preview",
              "char_name",
              "char_select_artwork",
              "selector"
            };
}

int LayerInfoProvider::getLayer(const std::string& layerName) const {
    auto it = std::find(layers.begin(), layers.end(), layerName);
    if (it != layers.end()) {
        return std::distance(layers.begin(), it);
    }
    return 0; // Layer not found
}