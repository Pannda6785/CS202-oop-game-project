#ifndef DEPTH_HPP
#define DEPTH_HPP

#include "../handlerCharacter/HandlerCharacter.hpp"

class Depth : public HandlerCharacter {
public:
    Depth();
    void neutralize() override;
};

#endif // DEPTH_HPP
