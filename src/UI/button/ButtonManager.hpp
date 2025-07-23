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

    void addButton(std::unique_ptr<Button> button);
    void update(float dt);
    void reset();
    int getHoveredIndex() const;
    int getButtonCount() const;
    Button* getButton(int idx);
    void setVisible(bool visible);

private:
    std::vector<std::unique_ptr<Button>> buttons;
    int hoveredIndex = -1;
    bool isTriggerCurrentButton = false;

    void updateHoveredByMouse();
    void updateHoveredByKeyboard();
    void triggerCurrentButton();
    int findNextEnabled(int start, int dir) const;
};

#endif // BUTTON_MANAGER_HPP