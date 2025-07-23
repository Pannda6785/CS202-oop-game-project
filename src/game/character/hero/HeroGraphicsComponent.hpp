#ifndef HERO_GRAPHICS_COMPONENT_HPP
#define HERO_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class HeroGraphicsComponent : public CharacterGraphicsComponent {
public:
    HeroGraphicsComponent();
    ~HeroGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override {};

private:

};

#endif // HERO_GRAPHICS_COMPONENT_HPP
