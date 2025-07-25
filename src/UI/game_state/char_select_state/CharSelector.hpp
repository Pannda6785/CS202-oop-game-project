#ifndef CHAR_SELECTOR_HPP
#define CHAR_SELECTOR_HPP

#include <vector>
#include <string>
#include <memory>
#include "../../../input/KeyboardInputInterpreter.hpp"
#include "CharSelectorGraphicsComponent.hpp"

class CharSelector {
public:
    CharSelector();
    ~CharSelector();

    void init(std::vector<std::string> options);
    void setKeyUp(int raylibKey);
    void setKeyDown(int raylibKey);
    void setKeyConfirm(int raylibKey);
    void setSide(bool isLeft);
    void setPosition(Vector2 position);
    void setDirection(Vector2 dir);
    void setAngleRotate(float angle);
    void loadSelectionCursorTexture(const std::string& texturePath);
    void unloadTextures();
    int getCurrentSelection() const;

    void update(float dt);

private:
    std::vector<std::string> characterOptions;
    CharSelectorGraphicsComponent graphic;

    int currentSelection;
    bool lockSelect;
    KeyboardInputInterpreter inputInterpreter;
    bool isLeftSide;

};

#endif // CHAR_SELECTOR_HPP