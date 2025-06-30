#include "ButtonManager.hpp"
#include <algorithm>
#include <iostream>

ButtonManager& ButtonManager::getInstance() {
    static ButtonManager instance;
    return instance;
}

ButtonManager::ButtonManager() {
    // Không cần lưu GraphicsComponentManager, dùng singleton trực tiếp
    std::cout << "ButtonManager created." << std::endl;
}

ButtonManager::~ButtonManager() {
    clearAllButtons();
    std::cout << "ButtonManager destroyed." << std::endl;
}

IButtonControl* ButtonManager::createButton(int x, int y, int width, int height, const std::string& text) {
    auto newButton = std::make_unique<Button>(x, y, width, height, text);
    IButtonControl* controlPtr = newButton.get();

    // Đăng ký GraphicsComponent của nút với GraphicsComponentManager
    if (newButton->getGraphicsComponent()) {
        GraphicsComponentManager::instance().registerComponent(
            static_cast<const GraphicsComponent*>(newButton->getGraphicsComponent())
        );
    }

    m_buttons.push_back(std::move(newButton));
    return controlPtr;
}

void ButtonManager::updateButtons(float dt) {
    for (const auto& button : m_buttons) {
        if (button->isEnabled()) {
            button->update(dt);
        }
    }
}

void ButtonManager::removeButton(IButtonControl* buttonToRemove) {
    for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it) {
        if (it->get() == buttonToRemove) {
            // Hủy đăng ký GraphicsComponent trước khi xóa nút
            if ((*it)->getGraphicsComponent()) {
                GraphicsComponentManager::instance().unregisterComponent(
                    static_cast<const GraphicsComponent*>((*it)->getGraphicsComponent())
                );
            }
            m_buttons.erase(it);
            return;
        }
    }
}

void ButtonManager::clearAllButtons() {
    for (const auto& button : m_buttons) {
        if (button->getGraphicsComponent()) {
            GraphicsComponentManager::instance().unregisterComponent(
                static_cast<const GraphicsComponent*>(button->getGraphicsComponent())
            );
        }
    }
    m_buttons.clear();
}