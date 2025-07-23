#ifndef STATE_HEADING_HPP
#define STATE_HEADING_HPP

#include <raylib.h>
#include <string>
#include "../../../graphics/GraphicsComponent.hpp"

class StateHeading : public GraphicsComponent {
public:
    StateHeading();
    ~StateHeading();

    void setHasHeading(bool hasHeading);
    void init(const std::string &fontPath, const std::string &title, int posY, int fontSize, const Rectangle &dividerLine);
    void unload();
    void render() const override;

private:
    std::string title;
    Font font;
    int fontSize;
    Vector2 position;
    Rectangle dividerLine;
    bool hasHeading;
};

#endif // STATE_HEADING_HPP