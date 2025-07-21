#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

class GameState {
public:
    virtual ~GameState() = default;

    virtual void enter() = 0;
    virtual void update(float dt) = 0;
    virtual void exit() = 0;
};

#endif // GAME_STATE_HPP