#ifndef LICH_GRAPHICS_COMPONENT_HPP
#define LICH_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class LichGraphicsComponent : public CharacterGraphicsComponent {
public:
    LichGraphicsComponent();
    ~LichGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override {};

private:

};

#endif // LICH_GRAPHICS_COMPONENT_HPP
