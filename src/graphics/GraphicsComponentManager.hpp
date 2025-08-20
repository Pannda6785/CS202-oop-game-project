#ifndef GRAPHICS_COMPONENTS_MANAGER_HPP
#define GRAPHICS_COMPONENTS_MANAGER_HPP

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include "raylib.h"

class GraphicsComponent;

class GraphicsComponentManager {    
public:
    static constexpr float NATIVE_WIDTH = 1440;
    static constexpr float NATIVE_HEIGHT = 900;

    static GraphicsComponentManager& instance();

    void registerComponent(const GraphicsComponent* component);
    void unregisterComponent(const GraphicsComponent* component);

    void render() const;
    void renderIf(const std::function<bool(const GraphicsComponent&)>& predicate) const;

    void setResolution(int width, int height);
    void toggleFullscreen();

    void addTaggedCamera(const Camera2D& camera, const std::string& tag);
    void removeTaggedCamera(const std::string& tag);

    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }

private:
    GraphicsComponentManager();
    ~GraphicsComponentManager();

    GraphicsComponentManager(const GraphicsComponentManager&) = delete;
    GraphicsComponentManager& operator=(const GraphicsComponentManager&) = delete;

    std::vector<const GraphicsComponent*> components;

    Camera2D resolutionCamera{};
    int windowWidth;
    int windowHeight;
    bool isFullscreen;

    std::unordered_map<std::string, Camera2D> taggedCameras;
};

#endif // GRAPHICS_COMPONENTS_MANAGER_HPP
