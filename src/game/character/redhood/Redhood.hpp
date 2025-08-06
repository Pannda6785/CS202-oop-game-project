#ifndef REDHOOD_HPP
#define REDHOOD_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Redhood : public HandlerCharacter {
public:
    Redhood();
    void neutralize() override;
};

#endif // REDHOOD_HPP
