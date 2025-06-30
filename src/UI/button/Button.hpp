#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "IButtonControl.hpp"
#include "IButtonView.hpp"
#include <memory>    // Cho std::unique_ptr
#include <string>
#include <functional> // Cho std::function
#include <raylib.h>  // Bao gồm raylib để dùng GetMouseX, GetMouseY, IsMouseButtonDown, etc.

// Forward declaration của ButtonGraphicsComponent
class ButtonGraphicsComponent; 

class Button : public IButtonControl, public IButtonView {
public:
    Button(int x, int y, int width, int height, const std::string& text);
    ~Button();

    // --- Phương thức từ IButtonControl ---
    void enable() override;
    void disable() override;
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

    // --- Phương thức riêng của Button logic ---
    // Phương thức cập nhật trạng thái dựa trên input của raylib
    void update(float dt); 
    
    // Cung cấp quyền truy cập tới GraphicsComponent
    ButtonGraphicsComponent* getGraphicsComponent() const {
        return graphics.get();
    }

private:
    int x, y;
    int width, height;
    Rectangle bounds;
    std::string text;
    bool isIdle;
    bool isHovered;
    bool isPressed;
    bool isDisabled;
    std::function<void()> onClick;
    std::function<void()> onHoverEnter;

    std::unique_ptr<ButtonGraphicsComponent> graphic;

    // Hàm trợ giúp nội bộ
    bool contains(int mouseX, int mouseY) const;
};

#endif // BUTTON_HPP