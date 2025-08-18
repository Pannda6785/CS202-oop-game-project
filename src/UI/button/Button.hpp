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
    Button(int x, int y, int width, int height, const std::string& text, int fontSize, int offset, int side, const std::string &fontPath, bool lableShift);
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
    void setEnterHovered(bool enterHovered);
    void setExitHovered(bool exitHovered);
    void setLayer(int layer);
    void triggerOnClick();
    void triggerHoverEnter();
    
    ButtonGraphicsComponent* getGraphicsComponent();

private:
    int x, y;
    int width, height;
    Rectangle bounds;
    std::string text;
    bool idleState;
    bool hoveredState;
    bool pressedState;
    bool disabledState = false;
    bool enterHovered = false;
    bool exitHovered = false;
    std::function<void()> onClick;
    std::function<void()> onHoverEnter;

    std::unique_ptr<ButtonGraphicsComponent> graphic;

    bool contains(int mouseX, int mouseY) const;
};

#endif // BUTTON_HPP