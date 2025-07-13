#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "IButtonControl.hpp"
#include "IButtonView.hpp"
#include <memory>    // Cho std::unique_ptr
#include <string>
#include <functional> // Cho std::function
#include <raylib.h>  // Bao gồm raylib để dùng GetMouseX, GetMouseY, IsMouseButtonDown, etc.
#include "ButtonGraphicsComponent.hpp" // Bao gồm ButtonGraphicsComponent để sử dụng trong Button
#include "../../Unit.hpp"
#include "../game_state/EventManager.hpp"

class Button : public IButtonControl, public IButtonView {
public:
    Button(int x, int y, int width, int height, const std::string& text, const Unit::GameEvent& eventToPublish);
    ~Button();

    // --- Phương thức từ IButtonControl ---
    void enable() override;
    void disable() override;
    void setToState(std::string state) override; // Optional: set to a specific state like "idle", "hovered", etc.
    void setText(const std::string& newText) override;
    void setPosition(int x, int y) override;
    void setOnClickListener(std::function<void()> callback) override;
    void setOnHoverEnterListener(std::function<void()> callback) override;

    // --- Phương thức từ IButtonView ---
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
    Unit::GameEvent getEventToPublish() const override;

    // --- Phương thức riêng của Button logic ---
    // Phương thức cập nhật trạng thái dựa trên input của raylib
    void update(float dt); 
    void triggerOnClick();
    void triggerHoverEnter();
    
    // Cung cấp quyền truy cập tới GraphicsComponent
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
    Unit::GameEvent eventToPublish;

    std::unique_ptr<ButtonGraphicsComponent> graphic;

    // Hàm trợ giúp nội bộ
    bool contains(int mouseX, int mouseY) const;
};

#endif // BUTTON_HPP