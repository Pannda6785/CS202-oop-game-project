#include "ButtonGraphicsComponent.hpp"
#include <raylib.h>

// Constructor
ButtonGraphicsComponent::ButtonGraphicsComponent(int x, int y, int width, int height,
                                                 const std::string& text, const IButtonView* buttonView)
    : m_buttonView(buttonView),
      m_x(x), m_y(y), m_width(width), m_height(height),
      m_text(text),
      m_texture(nullptr) // Khởi tạo con trỏ texture là nullptr
{
    m_backgroundColor = LIGHTGRAY;
    m_hoverColor = GRAY;
    m_pressedColor = DARKGRAY;
    m_textColor = BLACK;
    setDebugColor(BLUE); // Màu debug mặc định cho Button nếu không có texture
}

ButtonGraphicsComponent::~ButtonGraphicsComponent() {
    // Không cần giải phóng m_buttonView hoặc m_texture ở đây
    // vì chúng chỉ là con trỏ quan sát. Lifetime của Texture được quản lý bên ngoài.
}

// Phương thức render
void ButtonGraphicsComponent::render() const {
    if (!m_buttonView || !isVisible()) {
        return;
    }

    Color currentColor = m_backgroundColor;
    if (m_buttonView->isEnabled()) {
        if (m_buttonView->isPressed()) {
            currentColor = m_pressedColor;
        } else if (m_buttonView->isHovered()) {
            currentColor = m_hoverColor;
        }
    } else {
        currentColor = { currentColor.r / 2, currentColor.g / 2, currentColor.b / 2, currentColor.a };
    }

    int currentX = m_buttonView->getX();
    int currentY = m_buttonView->getY();
    int currentWidth = m_buttonView->getWidth();
    int currentHeight = m_buttonView->getHeight();
    std::string currentText = m_buttonView->getText();

    Rectangle bounds = { (float)currentX, (float)currentY, (float)currentWidth, (float)currentHeight };

    if (hasTexture()) { // Kiểm tra thông qua phương thức đã override
        DrawTexturePro(m_texture->data, // Sử dụng data từ Texture wrapper
                       (Rectangle){ 0.0f, 0.0f, (float)m_texture->data.width, (float)m_texture->data.height },
                       bounds,
                       (Vector2){ 0.0f, 0.0f },
                       0.0f,
                       currentColor);
    } else {
        DrawRectangleRec(bounds, getDebugColor());
        DrawRectangleLinesEx(bounds, 2, BLACK);
        
        int fontSize = 10;
        const char* debugText = "NO TEXTURE";
        Vector2 textSize = MeasureTextEx(GetFontDefault(), debugText, (float)fontSize, 1);
        DrawText(debugText,
                 currentX + currentWidth / 2 - textSize.x / 2,
                 currentY + currentHeight / 2 - textSize.y / 2,
                 fontSize,
                 BLACK);
    }

    int fontSize = 20;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), currentText.c_str(), (float)fontSize, 1);
    
    DrawText(currentText.c_str(),
             currentX + currentWidth / 2 - textSize.x / 2,
             currentY + currentHeight / 2 - textSize.y / 2,
             fontSize,
             m_textColor);
}

void ButtonGraphicsComponent::setBackgroundColor(Color color) { m_backgroundColor = color; }
void ButtonGraphicsComponent::setHoverColor(Color color) { m_hoverColor = color; }
void ButtonGraphicsComponent::setPressedColor(Color color) { m_pressedColor = color; }
void ButtonGraphicsComponent::setTextColor(Color color) { m_textColor = color; }
void ButtonGraphicsComponent::setText(const std::string& newText) { m_text = newText; }
void ButtonGraphicsComponent::setPosition(int x, int y) { m_x = x; m_y = y; }

void ButtonGraphicsComponent::setTexture(const Texture* texture) { // Nhận const Texture*
    m_texture = texture;
}