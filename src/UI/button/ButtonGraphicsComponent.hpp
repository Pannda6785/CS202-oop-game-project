#ifndef BUTTON_GRAPHICS_COMPONENT_HPP
#define BUTTON_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include "IButtonView.hpp"

#include <string>
#include <raylib.h>

class ButtonGraphicsComponent : public GraphicsComponent {
public:
    ButtonGraphicsComponent(int x, int y, int width, int height,
                            const std::string& text, const IButtonView* buttonView);
    virtual ~ButtonGraphicsComponent();

    void render() const override;

    void setBackgroundColor(Color color);
    void setHoverColor(Color color);
    void setPressedColor(Color color);
    void setTextColor(Color color);
    void setText(const std::string& newText);
    void setPosition(int x, int y);

    void setTexture(const Texture* texture); // Sử dụng const Texture*
    bool hasTexture() const override {
        return m_texture && m_texture->isValid(); // Kiểm tra Texture wrapper hợp lệ
    }

protected:
    const IButtonView* m_buttonView;

    int m_x, m_y;
    int m_width, m_height;
    std::string m_text;

    Color m_backgroundColor;
    Color m_hoverColor;
    Color m_pressedColor;
    Color m_textColor;
    
    const Texture* m_texture; // Thay đổi từ Texture2D sang const Texture*
};

#endif // BUTTON_GRAPHICS_COMPONENT_HPP