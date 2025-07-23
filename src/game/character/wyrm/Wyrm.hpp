#ifndef WYRM_HPP
#define WYRM_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Wyrm : public HandlerCharacter {
public:
    Wyrm();

    void neutralize() override;
};

#endif // WYRM_HPP
