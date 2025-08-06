#ifndef LICH_HPP
#define LICH_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Lich : public HandlerCharacter {
public:
    Lich();
    void neutralize() override;
};

#endif // LICH_HPP
