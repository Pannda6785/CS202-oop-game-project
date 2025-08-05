#ifndef HOLD_HANDLER_HPP
#define HOLD_HANDLER_HPP

#include "MoveHandler.hpp"

class HoldHandler : public MoveHandler {
public:
    HoldHandler(Unit::Move move);
    virtual ~HoldHandler() = default;

    bool tryRegister(InputBufferer* input) override final;
    void update(float dt, const InputBufferer* input) override {};

protected:
    virtual void tick(bool isFocusing) = 0;

protected:
    Unit::Move move;

};

#endif // HOLD_HANDLER_HPP
