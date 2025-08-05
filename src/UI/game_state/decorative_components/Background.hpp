#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>

class Background : public GraphicsComponent {
public:
    Background();
    ~Background();

    void render() const override;
    void setBackgroundColor(Color color);
    void setBackgroundRect(Rectangle rect);

private:
    Rectangle backgroundRect = {0, 0, 0, 0};
    Color backgroundColor = BLACK;
};

#endif // BACKGROUND_HPP