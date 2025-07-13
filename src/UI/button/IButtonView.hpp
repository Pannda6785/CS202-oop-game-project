#ifndef I_BUTTON_VIEW_HPP
#define I_BUTTON_VIEW_HPP

#include <string>
#include "../../Unit.hpp"

class IButtonView {
public:
    virtual ~IButtonView() = default;

    virtual bool isIdle() const = 0;
    virtual bool isHovered() const = 0;
    virtual bool isPressed() const = 0;
    virtual bool isEnabled() const = 0;

    virtual const std::string& getText() const = 0;

    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual Unit::GameEvent getEventToPublish() const = 0;
};

#endif // I_BUTTON_VIEW_HPP