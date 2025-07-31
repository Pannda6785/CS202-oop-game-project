#ifndef LICH_BASIC_HANDLER_HPP
#define LICH_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class LichGraphicsComponent;

class LichBasicHandler : public TapHandler {
public:
    LichBasicHandler(LichGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    LichGraphicsComponent* graphics;
};

#endif // LICH_BASIC_HANDLER_HPP