#ifndef KEYBIND_DISPLAY_HPP
#define KEYBIND_DISPLAY_HPP

#include "../decorative_components/GameText.hpp"
#include "../decorative_components/background/Background.hpp"
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <memory>

class KeybindDisplay {
public:
    // Constructors
    KeybindDisplay();
    KeybindDisplay(int raylibKey);
    ~KeybindDisplay();

    // Main methods
    void setPosition(int x, int y);
    void setKey(int raylibKey);
    void update(float dt);

    // Styling methods
    void setFont(const std::string& fontPath);
    void setFontSize(int fontSize);
    void setTextColor(Color color);
    void setBackgroundColor(Color color);
    void setPadding(float horizontalPadding, float verticalPadding);
    void setLayer(int layer); // Set layer for both text and background

    void setHover(bool hover);

    // Getters
    int getKey() const;
    float getWidth() const;
    float getHeight() const;
    std::string getKeyName() const;

private:
    int currentKey;
    std::unique_ptr<GameText> keyText;
    std::unique_ptr<Background> background;
    
    // Styling properties
    float horizontalPadding;
    float verticalPadding;
    std::string fontPath;
    int fontSize;
    Color textColor = BLACK;
    Color backgroundColor = WHITE;
    
    // Position
    int posX;
    int posY;
    
    // Key name mapping
    static std::unordered_map<int, std::string> keyNameMap;
    static void initializeKeyNameMap();
    
    // Helper methods
    void updateBackground();
    std::string getKeyNameFromMap(int keyCode) const;
};

#endif // KEYBIND_DISPLAY_HPP