#ifndef PRIESTESS_WIDE_HANDLER_HPP
#define PRIESTESS_WIDE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"

class PriestessGraphicsComponent;

class PriestessWideHandler : public CastHandler {
public:
    PriestessWideHandler(PriestessGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;

protected:
    void onCastStart() override;
    void onCastRelease() override;

private:
    PriestessGraphicsComponent* graphics;
};

#endif // PRIESTESS_WIDE_HANDLER_HPP
