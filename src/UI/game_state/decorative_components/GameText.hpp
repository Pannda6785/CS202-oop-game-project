#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include <unordered_map>

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
    void setOriginRatio(Vector2 originRatio);
    void setAlphaColor(float alpha);
    void setAngle(float angle);
    
    // New shader-related methods
    void loadShader(const std::string& fragmentShaderPath);
    void enableShader(bool enable);
    void setShaderValue(const std::string& uniformName, const void* value, int uniformType);
    bool hasShader() const;
    void unloadShader();
    
    // New update method for animations and shader effects
    void update(float dt);

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
    Vector2 originRatio = {0.0f, 0.0f};
    int fontSize = 32;
    Color color = WHITE;
    float angle = 0.0f;
    
    // New shader-related members
    Shader shader = {0, nullptr};
    bool shaderEnabled = false;
    bool shaderLoaded = false;
    std::string shaderPath;
    mutable std::unordered_map<std::string, int> uniformLocations;
    float time = 0.0f;  // For tracking time-based effects
};

#endif // GAME_TEXT_HPP