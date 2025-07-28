#ifndef CHAR_SELECT_STATE_HPP
#define CHAR_SELECT_STATE_HPP

#include "../GameState.hpp"
#include "CharSelector.hpp"
// #include "../../button/ButtonManager.hpp"
// #include "../../button/Button.hpp"
// #include "../state_heading/StateHeading.hpp"
// #include "../decorative_components/BehindDots.hpp"
#include "../decorative_components/MovingTileGraphicsComponent.hpp"
#include "../../../input/KeyboardInputInterpreter.hpp"
#include "./char_select_preview/CharSelectPreviewManager.hpp"
#include <vector>
#include <memory>
#include "../decorative_components/Artwork.hpp"

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
    Artwork characterSelectArtwork;
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
    CharSelector charSelectorLeft;
    CharSelector charSelectorRight;

    CharSelectPreviewManager charSelectPreviewManager;

};

#endif // CHAR_SELECT_STATE_HPP