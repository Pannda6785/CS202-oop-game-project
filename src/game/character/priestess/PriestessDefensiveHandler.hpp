#ifndef PRIESTESS_DEFENSIVE_HANDLER_HPP
#define PRIESTESS_DEFENSIVE_HANDLER_HPP

#include "../handlerCharacter/TapHandler.hpp"

class PriestessGraphicsComponent;

class PriestessDefensiveHandler : public TapHandler {
public:
    PriestessDefensiveHandler(PriestessGraphicsComponent* graphics);

protected:
    void tap() override;

private:
    PriestessGraphicsComponent* graphics;    

};

#endif // PRIESTESS_DEFENSIVE_HANDLER_HPP
