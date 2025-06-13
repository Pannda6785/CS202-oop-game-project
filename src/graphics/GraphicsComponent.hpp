#ifndef GRAPHICS_COMPONENT_HPP
#define GRAPHICS_COMPONENT_HPP

#include <vector>
#include <string>

class GraphicsComponent {
public:
    GraphicsComponent();
    virtual ~GraphicsComponent();

    virtual void render() const = 0;

    bool isVisible() const;
    void setVisible(bool visibility);

    int getLayer() const;
    void setLayer(int newLayer);

    const std::vector<std::string>& getTags() const;
    bool hasTag(const std::string& tag) const;
    bool addTag(const std::string& tag);
    bool removeTag(const std::string& tag);

protected:
    bool visible = true;
    int layer = 0;
    std::vector<std::string> tags;

};

#endif // GRAPHICS_COMPONENT_HPP
