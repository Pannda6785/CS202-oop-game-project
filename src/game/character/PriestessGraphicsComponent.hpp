#ifndef PRIESTESS_GRAPHICS_COMPONENT_HPP
#define PRIESTESS_GRAPHICS_COMPONENT_HPP

#include "CharacterGraphicsComponent.hpp"

class PriestessGraphicsComponent : public CharacterGraphicsComponent {
public:
    PriestessGraphicsComponent(const IPlayerView* playerView);
    ~PriestessGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override;
};

#endif // PRIESTESS_GRAPHICS_COMPONENT_HPP
