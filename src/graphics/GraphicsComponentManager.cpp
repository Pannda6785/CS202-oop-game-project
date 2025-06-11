#include "GraphicsComponentManager.hpp"
#include "GraphicsComponent.hpp"
#include "Renderer.hpp"

#include <algorithm>

GraphicsComponentManager& GraphicsComponentManager::instance() {
    static GraphicsComponentManager instance;
    return instance;
}

void GraphicsComponentManager::registerComponent(const GraphicsComponent* component) {
    if (!component) return;

    if (std::find(components.begin(), components.end(), component) != components.end())
        return;

    auto it = std::find_if(components.begin(), components.end(),
        [component](const GraphicsComponent* existing) {
            return component->getLayer() < existing->getLayer();
        });

    components.insert(it, component);
}

void GraphicsComponentManager::unregisterComponent(const GraphicsComponent* component) {
    auto it = std::find(components.begin(), components.end(), component);
    if (it != components.end()) {
        components.erase(it);
    }
}

void GraphicsComponentManager::render(Renderer& renderer) const {
    for (const auto* component : components) {
        if (component->isVisible()) {
            component->render(renderer);
        }
    }
}

void GraphicsComponentManager::renderIf(Renderer& renderer, const std::function<bool(const GraphicsComponent&)>& predicate) const {
    for (const auto* component : components) {
        if (component->isVisible() && predicate(*component)) {
            component->render(renderer);
        }
    }
}