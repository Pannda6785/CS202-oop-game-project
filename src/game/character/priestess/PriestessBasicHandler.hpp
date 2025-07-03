#ifndef PRIESTESS_BASIC_HANDLER_HPP
#define PRIESTESS_BASIC_HANDLER_HPP

#include "../handlerCharacter/TapHandler.hpp"

class PriestessGraphicsComponent;

class PriestessBasicHandler : public TapHandler {
public:
    PriestessBasicHandler(PriestessGraphicsComponent* graphics);

protected:
    void tap() override;

private:
    PriestessGraphicsComponent* graphics;
};

#endif // PRIESTESS_BASIC_HANDLER_HPP
