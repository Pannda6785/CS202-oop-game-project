#ifndef HERO_OF_FROST_PREVIEW_HPP
#define HERO_OF_FROST_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class HeroOfFrostPreview : public CharSelectPreview {
public:
    HeroOfFrostPreview();
    HeroOfFrostPreview(bool isLeft);
    ~HeroOfFrostPreview();
    void setSide(bool isLeft);
};

#endif // HERO_OF_FROST_PREVIEW_HPP