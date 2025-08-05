#ifndef HERO_HPP
#define HERO_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Hero : public HandlerCharacter {
public:
    Hero();
    void neutralize() override;
};

#endif // HERO_HPP
