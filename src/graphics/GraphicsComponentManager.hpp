#ifndef GRAPHICS_COMPONENTS_MANAGER_HPP
#define GRAPHICS_COMPONENTS_MANAGER_HPP

#include <vector>
#include <functional>

class GraphicsComponent;

class GraphicsComponentManager {
public:
    static GraphicsComponentManager& instance();

    void registerComponent(const GraphicsComponent* component);
    void unregisterComponent(const GraphicsComponent* component);

    void render() const;
    void renderIf(const std::function<bool(const GraphicsComponent&)>& predicate) const;

private:
    GraphicsComponentManager() = default;
    ~GraphicsComponentManager() = default;

    GraphicsComponentManager(const GraphicsComponentManager&) = delete;
    GraphicsComponentManager& operator=(const GraphicsComponentManager&) = delete;

    std::vector<const GraphicsComponent*> components;
};

#endif // GRAPHICS_COMPONENTS_MANAGER_HPP
