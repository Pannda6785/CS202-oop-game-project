#ifndef CUSTOM_CURSOR_HPP
#define CUSTOM_CURSOR_HPP
#include <raylib.h>
#include "CustomCursorGraphicsComponent.hpp"

class CustomCursor{
public:
    static CustomCursor& getInstance();
    void init();
    void update(float dt);
private:
    CustomCursor() = default;
    ~CustomCursor() = default;

    CustomCursor(const CustomCursor&) = delete;
    CustomCursor& operator=(const CustomCursor&) = delete;

    CustomCursorGraphicsComponent graphic;
};

#endif // CUSTOM_CURSOR_HPP