#ifndef PRIESTESS_DEFENSIVE_HANDLER_HPP
#define PRIESTESS_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class PriestessGraphicsComponent;

class PriestessDefensiveHandler : public TapHandler {
    static constexpr float COOLDOWN = 15.0f;
    static constexpr float MOVEMENT_LOCK = 0.5f;
    
public:
    PriestessDefensiveHandler(PriestessGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    PriestessGraphicsComponent* graphics;    

};

#endif // PRIESTESS_DEFENSIVE_HANDLER_HPP
