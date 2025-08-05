#ifndef MOVE_HANDLER_HPP
#define MOVE_HANDLER_HPP

#include "../../../Unit.hpp"

class InputBufferer;
class HandlerCharacter;
class Player;

class MoveHandler {
public:
    virtual ~MoveHandler() = default;

    void registerCharacter(HandlerCharacter* characterRef);
    void registerPlayer(Player* playerRef);

    virtual bool tryRegister(InputBufferer* input) = 0;
    virtual void update(float dt, const InputBufferer* input) = 0;
    virtual void listen(Unit::Move move) {} // listen to which move the character registered, used for disrupting combos/holds

protected:
    HandlerCharacter* character;
    Player* player;

};

#endif // MOVE_HANDLER_HPP
