#ifndef CHAR_SELECT_PREVIEW_HPP
#define CHAR_SELECT_PREVIEW_HPP

#include "../../decorative_components/MovingTileGraphicsComponent.hpp"
#include "../../decorative_components/GameText.hpp"
#include "../../decorative_components/Artwork.hpp"
#include "../../decorative_components/Background.hpp"


class CharSelectPreview {
public:
    CharSelectPreview();
    ~CharSelectPreview();

    void enter();
    void exit();

    void setSide(bool isLeft);
    void addTextureMainPortrait(const std::string & texturePath);
    void addTextureIdleAnimPreview(const std::string & texturePath);
    void addTextureBackgroundTiles(int id, const std::string & texturePath);
    void addTextureFrontTile(const std::string & texturePath);
    void setBackgroundColor(Color color);
    void setRibbonBackgroundColor(Color color);
    void setCharName(const std::string& text);
    void setFrontTileColor(Color color);
    void setMovingTileBackgroundColor(Color color);

    void update(float dt);
private:
    Artwork mainPortrait;
    Artwork idleAnimPreview;
    MovingTileGraphicsComponent backgroundTiles[3];
    MovingTileGraphicsComponent frontTile;
    GameText charName;
    Background background = Background();
    Background belowBackground = Background();
    Background ribbonBackground = Background();
    Background movingTileBackground[3] = { Background(), Background(), Background() };
    bool isLeft = true;
    Vector2 mainPortraitPosition = {10.0f, 60.0f};
    Vector2 idleAnimPreviewPosition = {40.0f, 520.0f};
    Vector2 backgroundTilesPosition[3] = {
        {GetScreenWidth() / 2.0f, 430.0f},
        {GetScreenWidth() / 2.0f, 200.0f},
        {GetScreenWidth() / 2.0f, 750.0f}
    };
    float backgroundTilesAngle[3] = {75.0f, 125.0f, 75.0f};
    float backgroundTilesSpeed[3] = {30.0f, 30.0f, 30.0f};
    int backgroundTilesLayer[3] = {5, 6, 7};
    Vector2 frontTilePosition = {0.0f, 0.0f};
    float frontTileAngle = 0.0f;
    float frontTileSpeed = 0.0f;
    int frontTileLayer = 0;
    Vector2 charNamePosition = {30.0f, 790.0f};
    float belowBackgroundHeight = 50.0f;
    float ribbonBackgroundHeight = 100.0f;
    Rectangle ribbonBackgroundRect = {0, (float)GetScreenHeight() - belowBackgroundHeight - ribbonBackgroundHeight, (float)GetScreenWidth() / 2.0f, ribbonBackgroundHeight};
    std::vector<std::string> layers;
    float portraitFadeInTime = 0.4f;
    float expandingTilesTime = 0.3f;
    Color MovingTileBackgroundColor = {255, 255, 255, 100};
    int getLayer(std::string);
};

#endif // CHAR_SELECT_PREVIEW_HPP