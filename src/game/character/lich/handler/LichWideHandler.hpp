#ifndef LICH_WIDE_HANDLER_HPP
#define LICH_WIDE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class LichGraphicsComponent;

class LichWideHandler : public TapHandler {
public:
    LichWideHandler(LichGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    LichGraphicsComponent* graphics;
};

#endif // LICH_WIDE_HANDLER_HPP