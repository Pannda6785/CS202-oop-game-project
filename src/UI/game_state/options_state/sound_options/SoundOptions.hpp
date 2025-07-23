#ifndef SOUND_OPTIONS_HPP
#define SOUND_OPTIONS_HPP

#include "../../GameState.hpp"
#include "../../../button/ButtonManager.hpp"
#include "../../main_menu_state/BehindDots.hpp"
#include "../../state_heading/StateHeading.hpp"
#include "./volume_bar/VolumeBarManager.hpp"

class GameStateManager;

class SoundOptions : public GameState{
public:
    SoundOptions(GameStateManager &gameStateManager, BehindDots &behindDots);
    ~SoundOptions();

    void enter();
    void update(float dt);
    void exit();

private:
    GameStateManager &gameStateManager;
    ButtonManager buttonManager;
    BehindDots &behindDots;
    StateHeading heading;
    VolumeBarManager volumeBarManager;
    Font font;
};

#endif // SOUND_OPTIONS_HPP