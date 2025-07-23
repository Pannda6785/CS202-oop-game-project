#ifndef ARCANIST_HPP
#define ARCANIST_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Arcanist : public HandlerCharacter {
public:
    Arcanist();
    void neutralize() override;
};

#endif // ARCANIST_HPP
