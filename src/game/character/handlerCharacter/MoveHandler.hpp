#ifndef MOVE_HANDLER_HPP
#define MOVE_HANDLER_HPP

#include "../../Unit.hpp"

class InputBufferer;
class HandlerCharacter;
class IPlayerControl;

class MoveHandler {
public:
    virtual ~MoveHandler() = default;

    void registerCharacter(HandlerCharacter* characterRef);
    void registerPlayer(IPlayerControl* playerRef);

    virtual bool tryRegister(InputBufferer* input) = 0;
    virtual void update(float dt) = 0;
    virtual void listen(Unit::Move move) {} // listen to which move the character registered, used for disrupting combos/holds

protected:
    HandlerCharacter* character;
    IPlayerControl* player;

};

#endif // MOVE_HANDLER_HPP
