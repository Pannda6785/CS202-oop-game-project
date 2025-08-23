#ifndef CHAR_SELECT_STATE_HPP
#define CHAR_SELECT_STATE_HPP

#include <vector>
#include <memory>

#include "./char_selector/CharSelector.hpp"
#include "LayerInfoProvider.hpp"
#include "../GameState.hpp"
#include "../decorative_components/Artwork.hpp"
#include "../decorative_components/MovingTileGraphicsComponent.hpp"
#include "../../../input/InputInterpreter.hpp"
#include "./char_select_preview/CharSelectPreviewManager.hpp"
#include "../../../game/WorldBuilder.hpp"


class GameStateManager;

class CharSelectState : public GameState {
public:
    CharSelectState(GameStateManager& gsm);
    ~CharSelectState();

    void enter() override;
    void update(float dt) override;
    void exit() override;

private:
    GameStateManager& gameStateManager;
    MovingTileGraphicsComponent movingTileEffect[2];
    Artwork characterSelectArtwork = Artwork();
    float charSelectFrameHeight = 80.0f;
    float distanceBetweenFrames = 10.0f;
    float firstFrameY = 100.0f;
    std::vector<std::string> selectOptions = std::vector<std::string>{
            "Sun Priestess",
            "Silent Redhood",
            "Royal Arcanist",
            "Hero of Frost",
            "Random Select",
            "Dreadwyrm Heir",
            "Lich of Flowers",
            "Depth's Secret",
            "Stormbeast"
        };

    std::vector<const InputInterpreter*> interpreters;
    CharSelector charSelectorLeft;
    CharSelector charSelectorRight;

    CharSelectPreviewManager charSelectPreviewManagerLeft;
    CharSelectPreviewManager charSelectPreviewManagerRight;

    WorldBuilder worldBuilder;

    std::string getCurrentSelectionName(std::string currentSelection);

    void registerInputInterpreter();
    void startGame();
};

#endif // CHAR_SELECT_STATE_HPP