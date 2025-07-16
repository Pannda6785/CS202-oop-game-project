#ifndef MAIN_MENU_BACKGROUND_HPP
#define MAIN_MENU_BACKGROUND_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>

class MainMenuBackground : public GraphicsComponent {
public:
    MainMenuBackground();
    void loadTexture(const std::string& texturePath);
    ~MainMenuBackground();

    void render() const override;

private:
    Texture2D backgroundTexture;
    bool loaded = false;
};

#endif // MAIN_MENU_BACKGROUND_HPP