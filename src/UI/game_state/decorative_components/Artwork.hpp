#ifndef ARTWORK_HPP
#define ARTWORK_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <vector>
#include <string>

class Artwork : public GraphicsComponent {
public:
    Artwork();
    ~Artwork() override;

    void update(float dt);
    void render() const override;

    bool addTexture(const std::string& filePath);
    void unloadTextures();

    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setPeriod(float period);
    void setScale(float scale);
    void setFadeInTime(float time);
    void setFlip(bool flip);
    void setMiddle(bool mid);
    void setOriginRatio(Vector2 originRatio);

    void setFlipVertical(bool flipVertical);
    void setFlipHorizontal(bool flipHorizontal);

    bool getFlipVertical() const { return flipVertical; }
    bool getFlipHorizontal() const { return flipHorizontal; }

    bool finishedFadeIn() const;
    int getWidth() const;
    float getFadeInTime() const;
    float getFadeInTimer() const;

private:
    std::vector<const Texture2D*> textures;
    std::vector<std::string> texturePaths;
    Vector2 origin = {0.0f, 0.0f};
    Vector2 originRatio = {0.0f, 0.0f};
    float period = 0.1f;
    int posX = 0, posY = 0;
    int drawWidth = 0, drawHeight = 0;
    float scale = 1.0f;
    mutable float timer = -1.0f;
    float fadeInTime = 0.0f;
    float fadeInTimer = 0.0f;
    bool middle = false;
    bool flip = false;
    bool flipVertical = false;
    bool flipHorizontal = false;
};

#endif // ARTWORK_HPP