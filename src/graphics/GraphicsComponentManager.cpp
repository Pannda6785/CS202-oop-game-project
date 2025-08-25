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
    
    drawLetterbox();
}

void GraphicsComponentManager::setResolution(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    SetWindowSize(width, height);

    // Uniform zoom (scale to fit inside window)
    float zoomX = (float)width / (float)NATIVE_WIDTH;
    float zoomY = (float)height / (float)NATIVE_HEIGHT;
    resolutionCamera.zoom = std::min(zoomX, zoomY);

    // Calculate the size of the scaled game world
    float viewportWidth  = NATIVE_WIDTH  * resolutionCamera.zoom;
    float viewportHeight = NATIVE_HEIGHT * resolutionCamera.zoom;

    // Center the viewport inside the window (letterbox/pillarbox)
    float offsetX = ((float)width  - viewportWidth)  / 2.0f;
    float offsetY = ((float)height - viewportHeight) / 2.0f;

    // Camera offset is where (0,0) in world space maps in screen space
    resolutionCamera.offset = { offsetX + viewportWidth  / 2.0f,
                                offsetY + viewportHeight / 2.0f };

    // Target = center of the virtual game world
    resolutionCamera.target = { NATIVE_WIDTH / 2.0f, NATIVE_HEIGHT / 2.0f };
    resolutionCamera.rotation = 0.0f;
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

void GraphicsComponentManager::drawLetterbox() const {
    // Compute scaled viewport size
    float zoomX = (float)windowWidth / (float)NATIVE_WIDTH;
    float zoomY = (float)windowHeight / (float)NATIVE_HEIGHT;
    float zoom = std::min(zoomX, zoomY);

    float viewportWidth  = NATIVE_WIDTH  * zoom;
    float viewportHeight = NATIVE_HEIGHT * zoom;

    float offsetX = (windowWidth  - viewportWidth)  / 2.0f;
    float offsetY = (windowHeight - viewportHeight) / 2.0f;

    // Left bar
    if (offsetX > 0) {
        DrawRectangle(0, 0, (int)offsetX, windowHeight, BLACK);
        DrawRectangle((int)(offsetX + viewportWidth), 0,
                      (int)offsetX + 10, windowHeight, BLACK);
    }

    // Top/bottom bars
    if (offsetY > 0) {
        DrawRectangle(0, 0, windowWidth, (int)offsetY, BLACK);
        DrawRectangle(0, (int)(offsetY + viewportHeight),
                      windowWidth, (int)offsetY, BLACK);
    }
}
