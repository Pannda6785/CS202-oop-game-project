#ifndef BEHIND_DOTS_HPP
#define BEHIND_DOTS_HPP

#include "BehindDotsGraphicsComponent.hpp"
#include <vector>
#include <memory>

class BehindDots{
public:
    BehindDots();
    ~BehindDots();

    void loadDotTexture(const std::string& texturePath);
    void unloadTexture();
    void init();
    void update(float dt);
    void setVisible(bool visible);
private:
    const Texture2D *dotTexture;
    bool loadedDotTexture = false;
    std::vector<std::unique_ptr<BehindDotsGraphicsComponent>> dots;
    std::vector<Color> palette = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
    Color ColorLerp(Color from, Color to, float t);
    Color getCurrentColor();
    const int numberOfDots = 50; // Number of dots to render
    void addNewDot();
};


#endif // BEHIND_DOTS_HPP
