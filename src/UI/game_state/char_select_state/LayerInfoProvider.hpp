// LayerInfoProvider.hpp
#ifndef LAYER_INFO_PROVIDER_HPP
#define LAYER_INFO_PROVIDER_HPP

#include <vector>
#include <string>

class LayerInfoProvider {
public:
    // Static method to get the single instance
    static LayerInfoProvider& getInstance();
    
    // Delete copy constructor and assignment operator
    LayerInfoProvider(const LayerInfoProvider&) = delete;
    LayerInfoProvider& operator=(const LayerInfoProvider&) = delete;

    void init();
    int getLayer(const std::string& layerName) const;

private:
    // Private constructor and destructor
    LayerInfoProvider();
    ~LayerInfoProvider();

    std::vector<std::string> layers;
};

#endif // LAYER_INFO_PROVIDER_HPP