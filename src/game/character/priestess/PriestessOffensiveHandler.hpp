#ifndef PRIESTESS_OFFENSIVE_HANDLER_HPP
#define PRIESTESS_OFFENSIVE_HANDLER_HPP

#include "../handlerCharacter/CastHandler.hpp"

class PriestessGraphicsComponent;

class PriestessOffensiveHandler : public CastHandler {
public:
    PriestessOffensiveHandler(PriestessGraphicsComponent* graphics);

protected:
    void onCastStart() override;
    void onCastRelease() override;

private:
    PriestessGraphicsComponent* graphics;
};

#endif // PRIESTESS_OFFENSIVE_HANDLER_HPP
