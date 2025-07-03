#include "HandlerCharacter.hpp"

#include "MoveHandler.hpp"
#include "../../player/IPlayerControl.hpp"
#include "../../player/InputBufferer.hpp"

void HandlerCharacter::registerPlayer(IPlayerControl* playerRef) {
    Character::registerPlayer(playerRef);
    for (auto& handler : moveHandlers) {
        handler->registerPlayer(playerRef);
    }
}

void HandlerCharacter::update(float dt, InputBufferer* input) {
    Unit::Move registeredMove = Unit::Move::MoveCount;

    for (Unit::Move move : order) {
        if (moveHandlers[static_cast<int>(move)] && moveHandlers[static_cast<int>(move)]->tryRegister(input)) {
            registeredMove = move;
            break;
        }
    }

    for (auto& handler : moveHandlers) {
        if (handler) {
            if (registeredMove != Unit::Move::MoveCount) {
                handler->listen(registeredMove);
            }
            handler->update(dt);
        }
    }
}

void HandlerCharacter::setOrder(std::vector<Unit::Move> newOrder) {
    order = std::move(newOrder);
}