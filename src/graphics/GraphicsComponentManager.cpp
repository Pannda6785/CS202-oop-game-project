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

bool GraphicsComponentManager::CompareComponent::operator()(const GraphicsComponent* a, const GraphicsComponent* b) const {
    if (a->getLayer() != b->getLayer()) return a->getLayer() < b->getLayer();
    if (a->getTags()  != b->getTags())  return a->getTags()  < b->getTags();
    return a < b;
}

void GraphicsComponentManager::registerComponent(const GraphicsComponent* component) {
    if (!component) return;
    auto it = std::lower_bound(components.begin(), components.end(), component, CompareComponent{});
    components.insert(it, component);
}

void GraphicsComponentManager::unregisterComponent(const GraphicsComponent* component) {
    if (!component) return;
    auto it = std::lower_bound(components.begin(), components.end(), component, CompareComponent{});
    if (it != components.end()) components.erase(it);
}

void GraphicsComponentManager::render() const {
    renderIf([](const GraphicsComponent& component) { return true; });
}

void GraphicsComponentManager::renderIf(const std::function<bool(const GraphicsComponent&)>& predicate) const {
    // Render all components first with resolutionCamera as the "base"
    BeginMode2D(resolutionCamera);
    const Camera2D* currentCamera = nullptr;
    for (const auto* component : components) {
        if (!component->isVisible() || !predicate(*component)) {
            continue;
        }
        // Find which camera this component should use
        const Camera2D* targetCamera = nullptr;
        for (const auto& [tag, camera] : taggedCameras) {
            if (component->hasTag(tag)) {
                targetCamera = &camera;
                break;
            }
        }
        // Switch camera batch if needed
        if (targetCamera != currentCamera) {
            if (currentCamera != nullptr) {
                EndMode2D(); // close previous batch
            }
            if (targetCamera != nullptr) {
                BeginMode2D(*targetCamera);
            }
            currentCamera = targetCamera;
        }
        // Draw component inside current camera batch
        component->render();
    }
    // Close last camera batch if we opened one
    if (currentCamera != nullptr) {
        EndMode2D();
    }
    EndMode2D(); // close resolutionCamera
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

bool GraphicsComponentManager::isToggleFullScreen() const {
    return isFullscreen;
}