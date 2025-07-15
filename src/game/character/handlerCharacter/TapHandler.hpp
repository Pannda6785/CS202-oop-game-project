#ifndef TAP_HANDLER_HPP
#define TAP_HANDLER_HPP

#include "MoveHandler.hpp"

class TapHandler : public MoveHandler {
public:
    TapHandler(Unit::Move move);
    virtual ~TapHandler() = default;

    bool tryRegister(InputBufferer* input) override final;
    void update(float) override {}

protected:
    virtual void tap() = 0;

protected:
    Unit::Move move;

};

#endif // TAP_HANDLER_HPP
