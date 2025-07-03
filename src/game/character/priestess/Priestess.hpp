#ifndef PRIESTESS_HPP
#define PRIESTESS_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Priestess : public HandlerCharacter {
public:
    Priestess();

    void neutralize() override;
};

#endif // PRIESTESS_HPP
