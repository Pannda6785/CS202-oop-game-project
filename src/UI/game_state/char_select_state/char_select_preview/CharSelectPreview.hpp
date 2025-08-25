#ifndef CHAR_SELECT_PREVIEW_HPP
#define CHAR_SELECT_PREVIEW_HPP

#include "../../decorative_components/MovingTileGraphicsComponent.hpp"
#include "../../decorative_components/GameText.hpp"
#include "../../decorative_components/artwork/Artwork.hpp"
#include "../../decorative_components/background/Background.hpp"
#include "../LayerInfoProvider.hpp"


class CharSelectPreview {
public:
    CharSelectPreview();
    ~CharSelectPreview();

    void enter();
    void exit();

    void addTextureMainPortrait(const std::string & texturePath);
    void addTextureIdleAnimPreview(const std::string & texturePath);
    void addTextureBackgroundTiles(int id, const std::string & texturePath);
    void addTextureFrontTile(const std::string & texturePath);

    void setSide(bool isLeft);
    void setBackgroundColor(Color color);
    void setRibbonBackgroundColor(Color color);
    void setCharName(const std::string& text);
    void setFrontTileColor(Color color);
    void setMovingTileBackgroundColor(Color color);

    void update(float dt);

private:
    // Main portrait of the character
    Artwork mainPortrait = Artwork();
    Vector2 mainPortraitPosition = {-10.0f, 60.0f};
    float mainPortraitScale = 0.37f;
    float portraitFadeInTime = 0.45f;

    // Idle animation preview
    Artwork idleAnimPreview = Artwork();
    Vector2 idleAnimPreviewPosition = {40.0f, 520.0f};

    // Background tiles
    MovingTileGraphicsComponent backgroundTiles[3] = { MovingTileGraphicsComponent(), MovingTileGraphicsComponent(), MovingTileGraphicsComponent() };
    Vector2 backgroundTilesPosition[3] = {
        {GraphicsComponentManager::NATIVE_WIDTH / 2.0f, 430.0f},
        {GraphicsComponentManager::NATIVE_WIDTH / 2.0f, 200.0f},
        {GraphicsComponentManager::NATIVE_WIDTH / 2.0f, 750.0f}
    };
    float backgroundTilesAngle[3] = {75.0f, 125.0f, 75.0f};
    float backgroundTilesSpeed[3] = {30.0f, 30.0f, 30.0f};
    int backgroundTilesLayer[3] = {5, 6, 7};
    float expandingTilesTime = 0.3f;
    
    // Front tile
    MovingTileGraphicsComponent frontTile = MovingTileGraphicsComponent();
    Vector2 frontTilePosition = {0.0f, 0.0f};
    float frontTileAngle = 0.0f;
    float frontTileSpeed = 0.0f;
    int frontTileLayer = 0;
    
    // Char name
    GameText charName = GameText();
    Vector2 charNamePosition = {30.0f, 790.0f};
    
    // Background
    Background background = Background();
    Rectangle backgroundRect = {0, 0, GraphicsComponentManager::NATIVE_WIDTH / 2.0f, GraphicsComponentManager::NATIVE_HEIGHT * 1.0f};

    // Below background
    Background belowBackground = Background();
    float belowBackgroundHeight = 50.0f;
    
    // Background ribbon
    Background ribbonBackground = Background();
    float ribbonBackgroundHeight = 100.0f;
    Rectangle ribbonBackgroundRect = {0, (float)GraphicsComponentManager::NATIVE_HEIGHT - belowBackgroundHeight - ribbonBackgroundHeight, (float)GraphicsComponentManager::NATIVE_WIDTH / 2.0f, ribbonBackgroundHeight};

    // Moving tile backgrounds
    Background movingTileBackground[3] = { Background(), Background(), Background() };
    Color movingTileBackgroundColor = {255, 255, 255, 100};
    
    bool isLeft = true;
    Vector2 getSymetricPos(Vector2 pos);

    bool debugFlag = true;
    bool out = false;
    bool checkFadeIn = false;
};

#endif // CHAR_SELECT_PREVIEW_HPP