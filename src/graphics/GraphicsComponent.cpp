#include "GraphicsComponent.hpp"
#include "GraphicsComponentManager.hpp"

#include <algorithm>

GraphicsComponent::GraphicsComponent() {
    GraphicsComponentManager::instance().registerComponent(this);
}

GraphicsComponent::~GraphicsComponent() {
    GraphicsComponentManager::instance().unregisterComponent(this);
}

bool GraphicsComponent::isVisible() const {
    return visible;
}

void GraphicsComponent::setVisible(bool visibility) {
    visible = visibility;
}

int GraphicsComponent::getLayer() const {
    return layer;
}

void GraphicsComponent::setLayer(int newLayer) {
    if (layer != newLayer) {
        layer = newLayer;
        GraphicsComponentManager::instance().unregisterComponent(this);
        GraphicsComponentManager::instance().registerComponent(this);
    }
}

const std::vector<std::string>& GraphicsComponent::getTags() const {
    return tags;
}

bool GraphicsComponent::hasTag(const std::string& tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

bool GraphicsComponent::addTag(const std::string& tag) {
    if (!hasTag(tag)) {
        tags.push_back(tag);
        return true;
    }
    return false;
}

bool GraphicsComponent::removeTag(const std::string& tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it != tags.end()) {
        tags.erase(it);
        return true;
    }
    return false;
}
