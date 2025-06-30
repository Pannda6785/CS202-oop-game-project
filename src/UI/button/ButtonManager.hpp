#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include "Button.hpp"
// Đảm bảo đường dẫn đến GraphicsComponentManager.hpp là chính xác trong dự án của bạn
#include "../../graphics/GraphicsComponentManager.hpp" 

#include <vector>
#include <memory> // Cho std::unique_ptr

class ButtonManager {
public:
    // Singleton pattern
    static ButtonManager& getInstance();

    // Ngăn chặn sao chép
    ButtonManager(const ButtonManager&) = delete;
    ButtonManager& operator=(const ButtonManager&) = delete;

    // Phương thức để thêm nút mới
    IButtonControl* createButton(int x, int y, int width, int height, const std::string& text);

    // Phương thức cập nhật tất cả các nút, có dt
    void updateButtons(float dt);

    // Phương thức để xóa nút
    void removeButton(IButtonControl* button);

    // Xóa tất cả các nút
    void clearAllButtons();

private:
    ButtonManager(); // Constructor private cho Singleton
    ~ButtonManager(); // Destructor private cho Singleton

    std::vector<std::unique_ptr<Button>> m_buttons;
};

#endif // BUTTON_MANAGER_HPP