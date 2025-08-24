#ifndef CHAR_SELECTOR_HPP
#define CHAR_SELECTOR_HPP

#include <vector>
#include <string>
#include <memory>
#include "../../../../input/InputInterpreter.hpp"
#include "CharSelectorGraphicsComponent.hpp"

class CharSelector {
public:
    CharSelector();
    ~CharSelector();

    void loadTexture(const std::string& texturePath);
    void unloadTextures();

    void setOptions(const std::vector<std::string>& options);
    void setSide(bool isLeft);
    void setInputInterpreter(std::shared_ptr<InputInterpreter> interpreter);
    void setPosition(Vector2 position);
    void setDirection(Vector2 dir);
    void setAngleRotate(float angle);
    void setLayer(int layer);

    int getCurrentSelection() const;
    bool getChangeSelection() const;
    std::shared_ptr<InputInterpreter> getInputInterpreter() const;

    bool isLocked() const;

    void update(float dt);

private:
    std::vector<std::string> characterOptions;
    CharSelectorGraphicsComponent graphic;

    int currentSelection = 0;
    bool lockSelect = false;
    std::shared_ptr<InputInterpreter> interpreter = nullptr;
    bool isLeftSide = true;
    bool changeSelection = false;

};

#endif // CHAR_SELECTOR_HPP