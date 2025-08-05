#ifndef ARTWORK_TITLE_HPP
#define ARTWORK_TITLE_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>

class ArtworkTitle : public GraphicsComponent {
public:
    ArtworkTitle();
    virtual ~ArtworkTitle();

    void loadCharTexture(const std::string& texturePath);
    void loadTitleTexture(const std::string& texturePath);
    void loadDecorationTexture(const std::string& texturePath);
    void unloadTextures();
    void render() const override;

private:
    Texture2D charTexture;
    Texture2D titleTexture;
    Texture2D decorationTexture;
    bool loadedChar = false;
    bool loadedTitle = false;
    bool loadedDecoration = false;
};

#endif // ARTWORK_TITLE_HPP