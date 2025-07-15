#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "IButtonControl.hpp"
#include "IButtonView.hpp"
#include <memory>
#include <string>
#include <functional>
#include <raylib.h>
#include "ButtonGraphicsComponent.hpp"

class Button : public IButtonControl, public IButtonView {
public:
    Button(int x, int y, int width, int height, const std::string& text);
    ~Button();

    void enable() override;
    void disable() override;
    void setToState(std::string state) override;
    void setText(const std::string& newText) override;
    void setPosition(int x, int y) override;
    void setOnClickListener(std::function<void()> callback) override;
    void setOnHoverEnterListener(std::function<void()> callback) override;
    void setHoverSound(Sound* sfx);

    bool isIdle() const override;
    bool isHovered() const override;
    bool isPressed() const override;
    bool isEnabled() const override;
    const std::string& getText() const override;
    int getX() const override;
    int getY() const override;
    int getWidth() const override;
    int getHeight() const override;
    Rectangle getBounds() const;

    void update(float dt); 
    void triggerOnClick();
    void triggerHoverEnter();
    
    ButtonGraphicsComponent* getGraphicsComponent() const;

private:
    int x, y;
    int width, height;
    Rectangle bounds;
    std::string text;
    bool idleState;
    bool hoveredState;
    bool pressedState;
    bool disabledState = false;
    std::function<void()> onClick;
    std::function<void()> onHoverEnter;

    std::unique_ptr<ButtonGraphicsComponent> graphic;

    bool contains(int mouseX, int mouseY) const;
};

#endif // BUTTON_HPP