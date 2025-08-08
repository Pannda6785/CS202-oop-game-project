#ifndef STORMBEAST_HPP
#define STORMBEAST_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Stormbeast : public HandlerCharacter {
public:
    Stormbeast();
    void neutralize() override;
};

#endif // STORMBEAST_HPP
