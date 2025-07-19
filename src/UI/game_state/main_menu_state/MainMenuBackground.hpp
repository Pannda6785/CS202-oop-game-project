#ifndef MAIN_MENU_BACKGROUND_HPP
#define MAIN_MENU_BACKGROUND_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>

class MainMenuBackground : public GraphicsComponent {
public:
    MainMenuBackground();
    void loadCharTexture(const std::string& texturePath);
    void loadTitleTexture(const std::string& texturePath);
    void loadDecorationTexture(const std::string& texturePath);
    void unloadTextures();
    ~MainMenuBackground();

    void render() const override;

private:
    Texture2D charTexture;
    Texture2D titleTexture;
    Texture2D decorationTexture;
    bool loadedChar = false;
    bool loadedTitle = false;
    bool loadedDecoration = false;
};

#endif // MAIN_MENU_BACKGROUND_HPP