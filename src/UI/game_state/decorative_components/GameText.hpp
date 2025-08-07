#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>

class GameText : public GraphicsComponent {
public:
    GameText();
    ~GameText() override;

    void setText(const std::string& text);
    void loadFont(const std::string& fontPath);
    void unloadFont();
    void setPosition(int x, int y);
    void setColor(Color color);
    void setFontSize(int size);

    const std::string& getText() const;
    int getX() const;
    int getY() const;
    int getFontSize() const;
    float getWidth() const;
    float getHeight() const;
    Color getColor() const;

    void render() const override;

private:
    std::string text;
    Font font;
    bool fontLoaded = false;
    int x = 0, y = 0;
    int fontSize = 32;
    Color color = WHITE;
};

#endif // GAME_TEXT_HPP