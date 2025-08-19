#ifndef STATE_HEADING_HPP
#define STATE_HEADING_HPP

#include <raylib.h>
#include <string>
#include "../../../graphics/GraphicsComponent.hpp"

class StateHeading : public GraphicsComponent {
public:
    // Alignment options enum
    enum class Alignment {
        LEFT,
        MIDDLE,
        RIGHT
    };
    
    StateHeading();
    ~StateHeading();

    void setHasHeading(bool hasHeading);
    
    // Original init method (defaults to middle alignment)
    void init(const std::string &fontPath, const std::string &title, int posY, 
              int fontSize, const Rectangle &dividerLine);
    
    // New init method with alignment options
    void init(const std::string &fontPath, const std::string &title, int posY, 
              int fontSize, const Rectangle &dividerLine, 
              Alignment alignment, int offset = 0);
    
    // Setter for alignment and offset after initialization
    void setAlignment(Alignment alignment, int offset = 0);
    
    void unload();
    void render() const override;

private:
    std::string title;
    Font font;
    int fontSize;
    Vector2 position;
    Rectangle dividerLine;
    bool hasHeading;
    Alignment alignment;
    int offset;
    
    // Helper method to calculate position based on alignment
    void updatePosition();
};

#endif // STATE_HEADING_HPP