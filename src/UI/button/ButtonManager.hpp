#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <vector>
#include <memory>
#include <string>
#include "Button.hpp"

class ButtonManager {
public:
    ButtonManager();
    ~ButtonManager();

    // Add a button to the manager (takes ownership)
    void addButton(std::unique_ptr<Button> button);

    // Update all buttons (handles mouse & keyboard navigation)
    void update(float dt);

    // Draw all buttons (optional, if not handled by GraphicsComponentManager)
    // void render() const;

    // Reset: clear all buttons and reset hovered/focused index
    void reset();

    // Get current hovered/focused index
    int getHoveredIndex() const;

    // Get button count
    int getButtonCount() const;

    // Get pointer to a button by index
    Button* getButton(int idx);

protected:
    std::vector<std::unique_ptr<Button>> buttons;
    int hoveredIndex = -1;

    // Internal helpers
    void updateHoveredByMouse();
    void updateHoveredByKeyboard();
    void triggerCurrentButton();
    int findNextEnabled(int start, int dir) const;
};

#endif // BUTTON_MANAGER_HPP