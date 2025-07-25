#ifndef ARTWORK_HPP
#define ARTWORK_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <vector>
#include <string>

class Artwork : public GraphicsComponent {
public:
    Artwork(float period = 1.0f);
    ~Artwork() override;

    // Add a texture by file path
    bool addTexture(const std::string& filePath);

    // Render the current frame
    void render() const override;

    // Set the position to draw the artwork
    void setPosition(int x, int y);

    // Set the size to draw the artwork (if <=0, use texture size)
    void setSize(int width, int height);

    // Set the animation period (seconds per frame)
    void setPeriod(float period);
    
    void unloadTextures();

    int getWidth() const;

private:
    std::vector<Texture2D> textures;
    std::vector<std::string> texturePaths;
    float period; // seconds per frame
    int posX = 0, posY = 0;
    int drawWidth = 0, drawHeight = 0;
};

#endif // ARTWORK_HPP