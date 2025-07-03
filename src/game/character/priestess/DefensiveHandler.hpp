#ifndef DEFENSIVE_HANDLER_HPP
#define DEFENSIVE_HANDLER_HPP

#include "../handlerCharacter/TapHandler.hpp"

class DefensiveHandler : public TapHandler {
public:
    DefensiveHandler();

protected:
    void tap() override;
};

#endif // PRIESTESS_DEFENSIVE_HANDLER_HPP
