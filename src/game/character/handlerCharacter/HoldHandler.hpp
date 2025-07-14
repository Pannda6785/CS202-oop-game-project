#ifndef HOLD_HANDLER_HPP
#define HOLD_HANDLER_HPP

#include "MoveHandler.hpp"

class HoldHandler : public MoveHandler {
public:
    HoldHandler(Unit::Move move, float minHoldingTime = 0.017f);
    virtual ~HoldHandler() = default;

    bool tryRegister(InputBufferer* input) override final;
    void update(float dt, const InputBufferer* input) override;

protected:
    virtual void onHoldStart() = 0;
    virtual void onHoldRelease() = 0;

protected:
    Unit::Move move;
    float minHoldingTime;

    bool isHolding = false;
    float holdingTime = 0.0f;
};

#endif // HOLD_HANDLER_HPP
