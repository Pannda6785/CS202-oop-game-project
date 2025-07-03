#ifndef HANDLER_CHARACTER_HPP
#define HANDLER_CHARACTER_HPP

#include "../Character.hpp"
#include "MoveHandler.hpp"

#include <vector>
#include <array>

class HandlerCharacter : public Character {
public:
    HandlerCharacter(std::string name, float moveSpeed, float focusedSpeed, std::unique_ptr<CharacterGraphicsComponent> graphics);

    void registerPlayer(IPlayerControl* playerRef) override final;
    void update(float dt, InputBufferer* input) override final;

    void setOrder(std::vector<Unit::Move> newOrder); // set new priority order 
    virtual void neutralize() = 0; // go back to default priority order

protected:
    std::array<std::unique_ptr<MoveHandler>, Unit::NUM_MOVES> moveHandlers;
    std::vector<Unit::Move> order;

};

#endif // HANDLER_CHARACTER_HPP
