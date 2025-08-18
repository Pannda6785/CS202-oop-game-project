#include "GraphicsComponentManager.hpp"
#include "GraphicsComponent.hpp"

#include <algorithm>
#include <raylib.h>

GraphicsComponentManager& GraphicsComponentManager::instance() {
    static GraphicsComponentManager instance;
    return instance;
}

GraphicsComponentManager::GraphicsComponentManager() {
    windowWidth = NATIVE_WIDTH;
    windowHeight = NATIVE_HEIGHT;
    isFullscreen = false;
    resolutionCamera = {0};
    resolutionCamera.zoom = 1.0f;
}

GraphicsComponentManager::~GraphicsComponentManager() = default;

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

void GraphicsComponentManager::render() const {
    renderIf([](const GraphicsComponent& component) { return true; });
}

void GraphicsComponentManager::renderIf(const std::function<bool(const GraphicsComponent&)>& predicate) const {
    for (const auto* component : components) {
        if (component->isVisible() && predicate(*component)) {
            bool handled = false;
            for (const auto& [tag, camera] : taggedCameras) {
                if (component->hasTag(tag)) {
                    Camera2D combined = combineCameras(resolutionCamera, camera);
                    BeginMode2D(combined);
                    component->render();
                    EndMode2D();
                    handled = true;
                    break;
                }
            }
            if (!handled) {
                BeginMode2D(resolutionCamera);
                component->render();
                EndMode2D();
            }
        }
    }
}

void GraphicsComponentManager::setResolution(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    SetWindowSize(width, height);

    // Offset = center of window
    resolutionCamera.offset = { (float)width / 2.0f, (float)height / 2.0f };
    resolutionCamera.rotation = 0.0f;

    // Target = center of virtual resolution
    resolutionCamera.target = { NATIVE_WIDTH / 2.0f, NATIVE_HEIGHT / 2.0f };

    // Uniform zoom based on window size vs native resolution
    float zoomX = (float)width / (float)NATIVE_WIDTH;
    float zoomY = (float)height / (float)NATIVE_HEIGHT;
    resolutionCamera.zoom = std::min(zoomX, zoomY);
}

void GraphicsComponentManager::toggleFullscreen() {
    isFullscreen = !isFullscreen;
    ToggleFullscreen();

    if (isFullscreen) {
        // Get monitor resolution
        int monitor = GetCurrentMonitor();
        int screenWidth  = GetMonitorWidth(monitor);
        int screenHeight = GetMonitorHeight(monitor);

        setResolution(screenWidth, screenHeight);
    } else {
        // Restore to native resolution
        setResolution(NATIVE_WIDTH, NATIVE_HEIGHT);
    }
}

void GraphicsComponentManager::addTaggedCamera(const Camera2D& camera, const std::string& tag) {
    taggedCameras[tag] = camera;
}

void GraphicsComponentManager::removeTaggedCamera(const std::string& tag) {
    taggedCameras.erase(tag);
}

Camera2D GraphicsComponentManager::combineCameras(const Camera2D& a, const Camera2D& b) const {
    Camera2D out = {0};
    out.target = { a.target.x + b.target.x, a.target.y + b.target.y };
    out.offset = { a.offset.x + b.offset.x, a.offset.y + b.offset.y };
    out.rotation = a.rotation + b.rotation;
    out.zoom = a.zoom * b.zoom;
    return out;
}