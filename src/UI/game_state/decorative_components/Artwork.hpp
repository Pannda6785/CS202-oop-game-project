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

    bool addTexture(const std::string& filePath);
    void update(float dt);
    void render() const override;
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setPeriod(float period);
    void unloadTextures();
    int getWidth() const;
    void setScale(float scale);
    void setFadeInTime(float time);
    bool finishedFadeIn() const;
    void setFlip(bool flip);
    void setMiddle(bool mid);

private:
    std::vector<Texture2D> textures;
    std::vector<std::string> texturePaths;
    Vector2 origin = {0.0f, 0.0f};
    float period = 0.1f; // seconds per frame
    int posX = 0, posY = 0;
    int drawWidth = 0, drawHeight = 0;
    float scale = 1.0f; // Scale factor for rendering
    float fadeInTime = 0.0f; // Time for fade-in effect
    float fadeInTimer = 0.0f;
    bool middle = false;
    bool flip = false;
};

#endif // ARTWORK_HPP