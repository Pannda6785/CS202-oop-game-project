#ifndef I_BUTTON_CONTROL_HPP
#define I_BUTTON_CONTROL_HPP

#include <string>
#include <functional>
#include "../../Unit.hpp"

class IButtonControl {
public:
    virtual ~IButtonControl() = default;

    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void setToState(std:: string state) = 0;
    virtual void setText(const std::string& newText) = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void setOnClickListener(std::function<void()> callback) = 0;
    virtual void setOnHoverEnterListener(std::function<void()> callback) = 0;
};

#endif // I_BUTTON_CONTROL_HPP