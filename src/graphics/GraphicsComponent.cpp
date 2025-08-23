#include "GraphicsComponent.hpp"
#include "GraphicsComponentManager.hpp"

#include <algorithm>
#include <iostream>

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
        GraphicsComponentManager::instance().unregisterComponent(this);
        layer = newLayer;
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
        GraphicsComponentManager::instance().unregisterComponent(this);
        tags.push_back(tag);
        GraphicsComponentManager::instance().registerComponent(this);
        return true;
    }
    return false;
}

bool GraphicsComponent::removeTag(const std::string& tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it != tags.end()) {
        GraphicsComponentManager::instance().unregisterComponent(this);
        tags.erase(it);
        GraphicsComponentManager::instance().registerComponent(this);
        return true;
    }
    return false;
}
