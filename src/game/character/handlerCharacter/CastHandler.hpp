#ifndef CAST_HANDLER_HPP
#define CAST_HANDLER_HPP

#include "MoveHandler.hpp"

class CastHandler : public MoveHandler {
public:
    CastHandler(Unit::Move move, float minCastingTime = 0.017f, float maxCastingTime = 1e9);
    virtual ~CastHandler() = default;

    bool tryRegister(InputBufferer* input) override final;
    void update(float dt, const InputBufferer* input) override;

protected:
    virtual void onCastStart() = 0;
    virtual void onCastRelease(bool isInterupted = false) = 0;
    
protected:
    Unit::Move move;
    const float minCastingTime;
    const float maxCastingTime;

    float castingTime = 0.0f;
    bool isCasting = false;

};

#endif // CAST_HANDLER_HPP
